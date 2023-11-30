#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "gpu.h"
#include "tiledata.h"
#include "memory.h"
#include "modes.h"
#include "background.h"
#include "window.h"
#include "objects.h"
#include "display_ctl.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
// void printArray(std::array<unsigned char, 160> a,int n){
// 	for(int i=0;i<n;i++)
//       std::cout<<a[i]<<" ";
//   	std::cout<<std::endl;
// }
GPU::GPU(Memory& memory, MODES& GPU_modes,int scale): memory(memory),tiledata(memory),background(memory,tiledata), window(memory,tiledata), object(memory,tiledata), GPU_modes(GPU_modes), buffer{}, display_ctl(buffer) {

}
void GPU::do_4_dots(){
    
    int STAT = 0xFF41;
    int IF = 0xFF0F;
    int LY = 0xFF44;
    int LYC = 0xFF45;
    if (!this->memory.get_bit_from_addr(0xFF40, 7)) {
        std::cout<<"LCD OFF: " << (int) !this->memory.get_bit_from_addr(0xFF40, 7) << std::endl;
    }
    
    if (!this->memory.get_bit_from_addr(0xFF40, 7)){
        this->clock = 0;
        this->memory.write_8_bit(LY,0);
        this->memory.write_8_bit(STAT,0);
        this->GPU_modes = H_BLANK;
        return;
    }
    this->clock += 4;

    const char* modes[] = {"H_BLANK", "V_BLANK",  "OAM_SCAN", "DRAW"};
    MODES curr_mode = static_cast<MODES>(this->memory.read_8_bit(STAT) & 0x3);
    // std::cout<<"LCD MODE: " << curr_mode << " LCD CLOCK: " << this->clock << " STAT: " <<(int) this->memory.mem[0xFF41] <<" LY: " << (int) this->memory.read_8_bit(LY)<<" LYC: " << (int) this->memory.read_8_bit(LYC) << std::endl;
    // std::cout std::endl;
    MODES next_mode;
    if (this->memory.read_8_bit(LY) >= this->VP_ROWS)
    {
        // std::cout<<"Next mode: " << 1<< std::endl;
        // std::cout<<"LY: " << (int) this->memory.read_8_bit(LY)<<" ROWS: " << this->VP_ROWS << std::endl;
        next_mode = V_BLANK;
        if (next_mode != curr_mode){
            if (this->memory.get_bit_from_addr(STAT,4)){
                this->memory.set_bit_from_addr(IF,1);
            }
        }
    }
    else if (this->clock <= this->mode_3_limit)
    {
        // under 204
        // std::cout<<"NEXT IS DRAW"<< std::endl;
        // std::cout<<"Next mode: " << 3<< std::endl;
        next_mode = DRAW;
        if (next_mode != curr_mode){
            this->get_line(this->memory.read_8_bit(LY));
            for (size_t i = 0; i < 160; i++)
            {
                this->buffer[this->memory.read_8_bit(LY)][i] = this->curr_line[i];
            }
            this->display_ctl.update(this->memory.read_8_bit(LY));
            
        // std::cout <<(int) this->curr_line[0] << std::endl;
        // exit(0);
            
            
        }
    }
    else if (this->clock <= this->mode_2_limit)
    {
        // Under 376
        // std::cout<<"NEXT IS OAM_SCAN"<< std::endl;
        // std::cout<<"Next mode: " << 2<< std::endl;
        next_mode = OAM_SCAN;
        if (next_mode != curr_mode){
            if (this->memory.get_bit_from_addr(STAT,5)){

                this->memory.set_bit_from_addr(IF,1);
            }
           
        }

    }
    else if (this->clock <= 456+32)
    {
        // std::cout<<"Next mode: " << 0<< std::endl;
        // std::cout<<"NEXT IS H_BLANK"<< std::endl;
        next_mode = H_BLANK;
        if (next_mode != curr_mode){
            if (this->memory.get_bit_from_addr(STAT,3)){
                this->memory.set_bit_from_addr(IF,1);
            }
        }
    }
    else
    {
        throw std::runtime_error("Unregisted LCD Mode");
    }

//    std::cout<<" STAT: " <<(int) this->memory.mem[0xFF41] <<" next mode: " <<(int) next_mode << std::endl;
    this->memory.write_8_bit(STAT,(this->memory.read_8_bit(STAT) & 0xFC) | next_mode); 
    // std::cout<< " STAT: " <<(int) this->memory.mem[0xFF41] << std::endl;

    if (this->memory.read_8_bit(LY) == this->memory.read_8_bit(LYC)){
        this->memory.set_bit_from_addr(STAT,2);
        this->memory.set_bit_from_addr(IF,1);

    } else {
        this->memory.clear_bit_from_addr(STAT,2);
    }
    if (this->clock >= this->DOTS_PER_LINE){
        this->clock = 0;
        this->memory.mem[LY]++;
        if (this->memory.read_8_bit(LY) > this->MAX_LY) {
            this->memory.write_8_bit(LY,0);
        } 
        if (this->memory.read_8_bit(LY) == this->VP_ROWS) {
            this->memory.set_bit_from_addr(IF,0);
        } 
        
    }
}
void GPU::get_line(u_int8_t line_n){
    // TODO bg_pixels or win pixels seem to just be zeros, might be a mem issue tbh need to look into it but the value 3 is generated 
    // by roberts for the special at line 128 by the window at an early x so maybe look into window memory figure out whats going on
    std::array<u_int8_t,160> bg_pixels = this->background.read_line(line_n);

    std::array<u_int8_t,160> win_pixels;
    win_pixels.fill(5);
    // bg_pixels.fill(400);
    // std::cout << " Window enabled " <<(int) this->memory.get_bit_from_addr(0xFF40,5) << std::endl;
    if (this->memory.get_bit_from_addr(0xFF40,5)){
        win_pixels = this->window.read_line(line_n);
    }
    
    
    for (size_t i = 0; i < 160; i++)
    {
        this->curr_line[i] = win_pixels[i];
        if (this->curr_line[i] == 5){
            this->curr_line[i] = bg_pixels[i];
        }
        // if (line_n == 128){
        //     std::cout << " line_n " <<(int) line_n << " x "<<(int) i << " value " << (int) this->curr_line[i] << std::endl;
        // }
    }

    this->object.object_pixels_on_line(line_n,this->curr_line);

    //  exit(0);
    


}
void GPU::render(){
    this->display_ctl.render();
}
