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
#include "sprite.h"
#include "display_ctl.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

#include <spdlog/sinks/basic_file_sink.h>

#include <spdlog/spdlog.h>
// void printArray(std::array<unsigned char, 160> a,int n){
// 	for(int i=0;i<n;i++)
//       std::cout<<a[i]<<" ";
//   	std::cout<<std::endl;
// }
#define STAT 0xFF41
#define LCDC 0xFF40
#define SCX 0xFF43
#define LYC 0xFF45
#define IF 0xFF0F

#define SCY 0xFF42
#define WX 0xFF4B
#define WY 0xFF4A
using namespace std;
// TODO banning CPU and PPU from memory
// TODO Spirites
// TODO Turning off LCD
// TODO palettes
// TODO DMA Trans
//  
GPU::GPU(Memory& memory, MODES& GPU_modes,int scale): memory(memory),tiledata(memory),background(memory,tiledata), window(memory,tiledata), object(memory,tiledata), GPU_modes(OAM_SCAN), buffer{}, display_ctl(buffer), pixel_fetcher(memory,to_display,this->fetching_sprites, tall_mode) {}

void GPU::do_4_dots(){

    uint8_t LY = this->memory.read_8_bit(0xFF44);
    switch (this->GPU_modes)
    {
        case OAM_SCAN:{
            WYeqLY = false;
            if (this->cycles_left == 80){
                if (this->memory.get_bit_from_addr(STAT, 5)) this->memory.set_bit_from_addr(IF, 1);
                this->OAM_scan();
                this->cycles_left -= 4;
                if (LY == this->memory.read_8_bit(LYC) && this->memory.set_bit_from_addr(STAT, 6)) this->memory.set_bit_from_addr(IF, 1);
                else this->memory.clear_bit_from_addr(STAT, 2);
            }
            else {
                this->cycles_left -= 4;
            }
            if (this->cycles_left == 0){
                this->GPU_modes = DRAW;
                this->memory.set_bit_from_addr(STAT, 1);
                this->memory.set_bit_from_addr(STAT, 0);
                this->cycles_left = 376;
            }
            break;}
    case DRAW:{
        if (cycles_left == 376){
            dump_counter = this->memory.read_8_bit(SCX) % 8;

        }
      
        this->DRAW_2_dots(LY);
       
        if (this->DRAW_2_dots(LY)){
            GPU_modes = H_BLANK;
        
            this->memory.clear_bit_from_addr(STAT, 1);
            this->memory.clear_bit_from_addr(STAT, 0);
            H_BLANK_cycles = cycles_left;
            
        }
        break;}
    case H_BLANK:{
        if (cycles_left == H_BLANK_cycles){ 
            if (this->memory.get_bit_from_addr(STAT, 3)) this->memory.set_bit_from_addr(IF, 1);
        }
        cycles_left -= 4;
        
        if (cycles_left <= 0){
            // cout<<(int)this->memory.read_8_bit(0xFF44)<<endl;
            this->memory.write_8_bit(0xFF44, ++LY);
            // cout<<(int)this->memory.read_8_bit(0xFF44)<<endl;
            if (LY == 144){ 
                GPU_modes = V_BLANK;
                cycles_left = 4560;
                pixel_fetcher.reset(false,false);
                this->memory.set_bit_from_addr(IF,0);
                
                if (this->memory.get_bit_from_addr(STAT, 4)) this->memory.set_bit_from_addr(IF, 1);
                // cout<<(int)this->memory.get_bit_from_addr(0xFFFF,0)<<endl;
                // cout<<(int)this->memory.get_bit_from_addr(IF,0)<<endl;
                if (pixel_fetcher.rendering_window) pixel_fetcher.WLC++;
                display_ctl.render();
                this->memory.clear_bit_from_addr(STAT, 1);
                this->memory.set_bit_from_addr(STAT, 0);
                
            } else { 
                GPU_modes = OAM_SCAN;
                cycles_left = 80;
                pixel_fetcher.reset(false, false);
                this->memory.set_bit_from_addr(STAT, 1);
                this->memory.clear_bit_from_addr(STAT, 0);
            }
        }
        break;}
    case V_BLANK:{

        cycles_left -= 4;
        if (cycles_left != 4560 && cycles_left % 456 == 0){
            this->memory.write_8_bit(0xFF44, ++LY);
            this->memory.set_bit_from_addr(IF, 0);
            if (LY == this->memory.read_8_bit(LYC) && this->memory.get_bit_from_addr(STAT, 6)) this->memory.set_bit_from_addr(IF, 1);
            else { 
                this->memory.clear_bit_from_addr(STAT, 2);
                }
            if (pixel_fetcher.rendering_window) pixel_fetcher.WLC++;
        }
        if (cycles_left == 0){
            this->memory.write_8_bit(0xFF44, 0);
            GPU_modes = OAM_SCAN;
            cycles_left = 80;
            pixel_fetcher.WLC = 0;
          
        }
        break;}

    default:
        break;
    }

}
bool GPU::DRAW_2_dots(u_int8_t LY){
    // must check if fifo is empty!
    bool was_empty = pixel_fetcher.BG_FIFO.empty();
    if (!dump_counter && !pixel_fetcher.BG_FIFO.empty() && to_display.empty()){ 
        display_ctl.update(LY, X_POS, pixel_fetcher.pixel_mixing());
        X_POS++;
        check_sprite_buffer();
      
        
    } else if (dump_counter){
        dump_counter--;
    }

    if(!pixel_fetcher.rendering_window){
        check_window(LY);
    }
    

    if (!dump_counter && !pixel_fetcher.BG_FIFO.empty() && to_display.empty()){ 
        display_ctl.update(LY, X_POS, pixel_fetcher.pixel_mixing());
        X_POS++;
        check_sprite_buffer();
        if (check_EOL()) {
            cycles_left -= 2;
            return true;
        }
      
    } else if (dump_counter){
        dump_counter--;
    }
 
    
    
    if(!pixel_fetcher.rendering_window){
        check_window(LY);
    }
    pixel_fetcher.process_2_cycles(LY, was_empty);
    cycles_left -= 2;
    return false;
}
void GPU::check_window(uint8_t LY){
    if (LY <= this->memory.read_8_bit(WY)){
        WYeqLY = true;
    }
    bool should_switch =  WYeqLY && this->memory.get_bit_from_addr(LCDC, 5) && X_POS >= this->memory.read_8_bit(WX) - 7;
    if (should_switch){
        pixel_fetcher.switch_to_window();
    }
}
bool GPU::check_EOL(){
    if (X_POS == 160){
        X_POS = 0;
        return true;
    }
    return false;
}
void GPU::OAM_scan(){
    uint8_t LY = this->memory.read_8_bit(0xFF44);
    uint16_t addr = 0xFE00;
    tall_mode = ((this->memory.read_8_bit(0xFF40) >> 2 ) & 1);
    for (uint8_t oam_idx = 0; oam_idx < 40; oam_idx++){
        uint8_t y_pos = this->memory.read_8_bit(addr);
        uint8_t x_pos = this->memory.read_8_bit(addr + 1);
        uint8_t tile_number = this->memory.read_8_bit(addr + 2);
        uint8_t sprite_flags = this->memory.read_8_bit(addr + 3);
    //     bool priority = sprite_flags & (1 << 7);  // BG-to-OBJ Priority
    // bool y_flip = sprite_flags & (1 << 6);    // Y flip
    // bool x_flip = sprite_flags & (1 << 5);    // X flip
    // bool use_palette_1 = sprite_flags & (1 << 4); // OBJ-to-Palette Number (DMG only)

    // std::cout << fmt::format(
    //     "Y Position: {}, X Position: {}, Tile Number: {}, "
    //     "Flags: [Priority: {}, Y Flip: {}, X Flip: {}, Palette: {}]\n",
    //     static_cast<int>(y_pos),
    //     static_cast<int>(x_pos),
    //     static_cast<int>(tile_number),
    //     priority ? "On" : "Off",
    //     y_flip ? "Yes" : "No",
    //     x_flip ? "Yes" : "No",
    //     use_palette_1 ? "1" : "0"
    // );
        addr += 4;
        if (LY + 16 >= y_pos && LY + 16 < y_pos + (tall_mode ? 16 : 8)){
            sprite_buffer.push_back({y_pos, x_pos, tile_number, sprite_flags, oam_idx});
            if (sprite_buffer.size() == 10){
                break;
            }
        }
    }
}

void GPU::check_sprite_buffer(){
    uint8_t LY = this->memory.read_8_bit(0xFF44);
    // std::cout << fmt::format(
    //     "At line {}\n",
    //     static_cast<int>(LY)
    // );
    for (auto it = sprite_buffer.begin(); it != sprite_buffer.end(); ) {
        if ((*it).x_pos <= X_POS + 8) {
            to_display.push((*it));
            it = sprite_buffer.erase(it);
            // TODO check again once OAM tranfer is done
            // std::cout << fmt::format(
            //     "We found tile {} at x = {}\n",
            //     static_cast<int>((*it).tile_number), 
            //     static_cast<int>(X_POS)
            // );
           
            fetching_sprites = true;
            pixel_fetcher.reset(false,true);
        } else {
            ++it;
        }
    }
    
}
