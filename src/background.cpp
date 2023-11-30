#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "background.h"
#include "memory.h"
#include <array>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

// TODO Translate tiledata to colour map
u_int8_t* Background::get_tile_data(u_int8_t address) {
    // std::cout << this->memory.mem[0]<<std::endl;
        // return this->tiledata->getBGTile(address);
        if (this->memory.get_bit_from_addr(0xFF40,4)) {
            return this->memory.mem + (address * 16) + 0x8000;
        } else {
            if (address > 127){
                return this->memory.mem + ((address - 128) * 16) + 0x8800;
            } else {
                return this->memory.mem + (address * 16) + 0x9000;
            }
        }
    }
u_int8_t Background::read_tilemap_n(u_int8_t x, u_int8_t y,u_int8_t line_n){
    u_int16_t idx = x + (y * 32);
    u_int16_t starting_at = this->memory.get_bit_from_addr(0xFF40,3) ? 0xC800 : 0x9800;
    // if (line_n == 6){
    //     std::cout<<std::hex<<" mem_address "<< starting_at + idx << std::endl;
    //     std::cout<<std::hex<<" offset "<< starting_at << std::endl;
    //     std::cout<<std::hex<<" idx "<< idx << std::endl;
    // }
	

    return this->memory.read_8_bit(starting_at + idx);
}
std::array<u_int8_t,160> Background::read_line(u_int8_t line){
    this->tiledata->read_tiledata();
    this->line_n_to_colours();
    // std::cout<<"here"<<std::endl;
    

    auto between = [](u_int16_t* range, uint16_t address) {return address >= range[0] and address <= range[1]; };
    u_int8_t SCY = this->memory.read_8_bit(0xFF42);
    u_int8_t SCX = this->memory.read_8_bit(0xFF43);
    // std::cout<<" SCY " <<(int)SCY<<std::endl;
    // std::cout<<" SCX " <<(int)SCX<<std::endl;
    u_int8_t line_offset_wrap = (line + SCY) % 256;
    
    

    std::array<u_int8_t,160> pixels;
    // Five is the value that we will use to show that the window was undefined here
    pixels.fill(5);
    // TODO Background is always around
    
  


    for (size_t i = 0; i < 160; i++)
    {
        u_int8_t X_offset_wrap = (i + SCX) % 256;
        pixels[i] = this->colour_map[line_offset_wrap][X_offset_wrap];
        // std::cout<<" PIXELS " << (int) pixels[i] <<std::endl;
     
    }
    // for (size_t lines = 0; lines < 144; lines++)
    // {
    // for (size_t x = 0; x < 160; x++)
    // {
    //     if (this->colour_map[line][x] != 0)
    //     {
    //         std::cout<<(int) this->colour_map[line][x] <<std::endl;
    //         exit(0);
    //     }
        
    // }
    
      
    // }
   
    return pixels;
}
