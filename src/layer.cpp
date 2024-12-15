#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
// TODO function to return line of tile
Layer::Layer(Memory& memory, TileData& tiledata): memory(memory), tiledata(&tiledata){
    for(int i = 0; i < 256; ++i){
        // std::cout<<i<<std::endl;
        colour_map[i] = new uint8_t[256];
    }
    
};

uint8_t Layer::tile_idx_at(uint8_t x, uint8_t y){
    uint8_t idx = y * 32 + x;
    return tilemap[idx];
}
void Layer::line_n_to_colours(){
    for (size_t line_n = 0; line_n < 256; line_n++)
    {
        
        for (size_t pixel = 0; pixel < 256; pixel++){
            // figure out tile idx
            u_int8_t tile_y = line_n / 8;
            u_int8_t tile_x = pixel / 8;
            // figure out offset from corner of tile
            u_int8_t tile_pix_y = line_n % 8;
            u_int8_t tile_pix_x = pixel % 8;
    
            u_int8_t tile = this->read_tilemap_n(tile_x,tile_y,line_n);
            u_int8_t* tile_data = this->get_tile_data(tile);

             u_int8_t row = tile_pix_y * 2;
            // which coloumns to use
            u_int8_t f_col = tile_pix_x;
            u_int8_t s_col = tile_pix_x + 8;
         
    
            
        
            u_int8_t low = (tile_data[row] >> (7 - tile_pix_x)) & 1;
            u_int8_t high = ((tile_data[row+1] >> (7 - tile_pix_x)) & 1) << 1;
          
            u_int8_t colour_shift = (high + low);
    
            colour_shift = colour_shift * 2;
      
            
            this->colour_map[line_n][pixel] = colour_shift ;
            // if (line_n == 6) {
			// 	std::cout<<std::dec<<" at x = "<<(int) pixel << " we get tile "<<(int) tile<< std::endl;
			// 	// std::cout<<std::hex<<" tilebyte "<<(int) byte0<< std::endl;
			// 	// std::cout<<std::hex<<" tilebyte "<<(int) byte1<< std::endl;
			// 	std::cout<<std::hex<<" colour shift  "<<(int)colour_shift<< std::endl;
				
			// 	std::cout<<std::dec<<" colour "<<(int) this->colour_map[line_n][pixel]<< std::endl;
			// }
           

        }
    }
    
    
        

    
}
