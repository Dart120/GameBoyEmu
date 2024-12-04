#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "pixel_fetcher.h"
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
using namespace std;
// void printArray(std::array<unsigned char, 160> a,int n){
// 	for(int i=0;i<n;i++)
//       std::cout<<a[i]<<" ";
//   	std::cout<<std::endl;
// }

#define STAT 0xFF41
#define LCDC 0xFF40
#define SCX 0xFF43
#define SCY 0xFF42
#define WX 0xFF4B
#define LY_ADDR 0xFF44
#define WY 0xFF4A
#define BGP 0xFF47
PixelFetcher::PixelFetcher(Memory& memory): memory(memory){

}
void PixelFetcher::process_2_cycles(uint8_t LY, bool should_push){
    switch (this->mode)
    {
    case GET_TILE:
        {
            // cout<<"gettile"<<endl;

            get_tile(LY);
            mode = GET_TILE_DATA_LOW;
            break;
        }
    case GET_TILE_DATA_LOW:
    
    // PPU access to ram may be blocked for some reason
    // sprites always use 8000 mode
    
        {
            // cout<<"low"<<endl;
            uint8_t rowInTile;
            bool use_8000 = this->memory.get_bit_from_addr(LCDC, 4);
        uint8_t row_in_tile = rendering_window ? (WLC) % 8 : ((LY + this->memory.read_8_bit(SCY)) % 8);
        tile_addr_lower = (use_8000 ? 0x8000 + (this->tile_number * 16): 0x8800 + static_cast<int8_t>(this->tile_number) * 16) + row_in_tile * 2;
        // if (LY == 50) cout << "memloc " <<  tile_addr_lower << endl;
        tile_data_lower = this->memory.read_8_bit(tile_addr_lower);
        mode = GET_TILE_DATA_HIGH;
        break;}
    case GET_TILE_DATA_HIGH:
    
        {
            // cout<<"high"<<endl;
            tile_data_upper = this->memory.read_8_bit(tile_addr_lower + 1);
            mode = PUSH;
            if (first_time_on_line){
                reset(true);
            }
        break;}
    case PUSH:{
        // cout<<"push"<<endl;
        if (BG_FIFO.empty() && should_push){
            for (int i = 7; i >= 0; i--)
            {
                uint8_t low = tile_data_lower>>i  & 1;
                uint8_t upper = tile_data_upper>>i & 1;
                // if (LY == 50) cout<< " For X = "<<(int) X_POS*8 + (7-i)<< " the tile idx is "<<(int) this->tile_number<< " ly is "<<(int)LY<< "with color "<< (int)upper * 2 + low  << endl;
                // cout<< "tile_addr "<<hex<< tile_addr_lower<< endl;
                // cout<< "tile idx "<< tile_data_lower << endl;
                // cout<< upper * 2 + low << endl;
                // cout<< idx_to_color(upper * 2 + low) << endl;
                BG_FIFO.push({idx_to_color(upper * 2 + low), true, true});
                
            }
            X_POS++;
            mode = GET_TILE;
        }
        break;}
    default:
        break;
    }

}

void PixelFetcher::get_tile(uint8_t LY){
    uint16_t addr;
    if (rendering_window){
        uint16_t base_addr = this->memory.get_bit_from_addr(LCDC, 6) ? 0x9C00 : 0x9800;
        uint8_t x_offset = ((X_POS - this->memory.read_8_bit(WX)) / 8) & 0x1F;
        uint8_t y_offset = ((LY - this->memory.read_8_bit(WY) ) / 8) & 0x1F;
        addr = base_addr + x_offset + (y_offset * 32);
    } else {
        uint16_t base_addr = this->memory.get_bit_from_addr(LCDC, 3) ? 0x9C00 : 0x9800;
        uint8_t x_offset = (X_POS + (this->memory.read_8_bit(SCX) / 8)) & 0x1F;
        uint8_t y_offset = ((LY + this->memory.read_8_bit(SCY)) & 0xFF) / 8;
        addr = base_addr + (x_offset + (y_offset * 32) & 0x3ff);
        // if(LY == 50) cout <<(int) base_addr << " " << x_offset<< " " << y_offset << addr<<endl;
    }
    this->tile_number = this->memory.read_8_bit(addr);
}
void PixelFetcher::switch_to_window(){
    while (!BG_FIFO.empty()){
        BG_FIFO.pop();
    }
    rendering_window = true;
    mode = GET_TILE;
    // TODO
    X_POS = max(this->memory.read_8_bit(WX) - 7, 0);

    tile_number = 0;
  
    tile_addr_lower = 0;
    tile_addr_upper = 0;
    tile_data_upper = 0;
    tile_data_lower = 0;
    if (this->memory.read_8_bit(LY_ADDR) == this->memory.read_8_bit(WY)) {
    WLC = 0;  // Reset only if the window starts fresh.
    }
}


void PixelFetcher::reset(bool stall){
    while (!BG_FIFO.empty()){
        BG_FIFO.pop();
    }
    rendering_window = false;
    mode = GET_TILE;
 
    X_POS = 0;
    tile_number = 0;
   
    tile_addr_lower = 0;
    tile_addr_upper = 0;
    tile_data_upper = 0;
    tile_data_lower = 0;
    first_time_on_line = !stall;
    
}
uint8_t PixelFetcher::idx_to_color(uint8_t idx){
    uint8_t palette = this->memory.read_8_bit(BGP);
    return (palette >> (idx * 2)) & 3;
}

