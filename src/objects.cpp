#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "objects.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
// TODO render objects to virtual screen, work out palettes work out scrolling, combine images sources to one image
Objects::Objects(Memory& memory, TileData& tiledata): memory(memory), tiledata(&tiledata){}

u_int8_t* Objects::object_n_data_ptr(u_int8_t idx){
    if (idx >= 40){
        throw std::runtime_error("No object data idx >= 40");
    }
    return this->memory.mem + 0xFE00 + (idx*3);
}

u_int8_t* Objects::get_object_tiledata(u_int8_t idx){
    if (this->memory.get_bit_from_addr(0xFF40,2)){
        return this->tiledata->getObjectTile(idx & 0xFE);
    } else {
        return this->tiledata->getObjectTile(idx);
    }
}
void Objects::ingest_objects(){
    for (u_int8_t i = 0; i < 40; i++)
    {
        u_int8_t* addr = this->object_n_data_ptr(i);
        this->objects_data[i] = new sprite{addr,addr + 1,addr + 2,addr + 3, i};
    }
    
}
std::vector<sprite*> Objects::object_data_on_line(u_int8_t line){
    this->ingest_objects();
    bool double_height_mode = this->memory.get_bit_from_addr(0xFF40,2);
    u_int8_t range = double_height_mode ? 15 : 7;
    std::vector<sprite*> objects_on_line{};
    u_int8_t count = 0;
    for (auto object_data : this->objects_data) {
        u_int8_t y_coord = *(object_data->y_coord);
        if (count == 10){
            break;
        }
        if ((y_coord >= line - range) && (y_coord <= line)){
            objects_on_line.push_back(object_data);
        }
        count++;
    }
    return objects_on_line;
}
void Objects::populate_palette(u_int16_t address,std::map < uint8_t, uint8_t >& palette){
    u_int8_t palette_data = this->memory.read_8_bit(address);
    for (size_t i = 0; i < 4; i++)
    {
        palette.insert({i,(palette_data >> i) & 0x03});
        
    }
    
}
bool compByX(sprite* a, sprite* b)  
{  
    return a->x_coord < b->x_coord;  
}  
bool compByLoc(sprite* a, sprite* b)  
{  
    return a->OAM_pos < b->OAM_pos;  
}  
void Objects::object_pixels_on_line(u_int8_t line, std::array<u_int8_t,160>& pixels){
    // get the sprite
    std::vector<sprite*> object_data_on_line = this->object_data_on_line(line);
    bool double_height_mode = this->memory.get_bit_from_addr(0xFF40,2);
    u_int8_t range = double_height_mode ? 15 : 7;
    // smaller x have priority, if same x then the first in oam
    std::stable_sort(object_data_on_line.begin(), object_data_on_line.end(), compByX);
    std::stable_sort(object_data_on_line.begin(), object_data_on_line.end(), compByLoc);
    // get the pallets
    std::map < uint8_t, uint8_t > OBP0;
    std::map < uint8_t, uint8_t > OBP1;
    this->populate_palette(0xFF48,OBP0);
    this->populate_palette(0xFF49,OBP1);
    // for all objects on line
    for (auto object_data : object_data_on_line) {
        u_int8_t metadata = *(object_data->metadata);
        u_int8_t y_coord = *(object_data->y_coord);
        u_int8_t x_coord = *(object_data->x_coord);
        u_int8_t tile_idx = *(object_data->tile_idx);
        bool Y_flip  = (metadata >> 6) & 1;
        bool X_flip  = (metadata >> 5) & 1;
        bool use_OBP1  = (metadata >> 4) & 1;
        bool win_bg_priority  = (metadata >> 7) & 1;
        std::map < uint8_t, uint8_t > palette = use_OBP1 ? OBP1 : OBP0;
        std::array<u_int8_t,8> res = {0,0,0,0,0,0,0,0};
     
        u_int8_t offset = line - y_coord;
        offset = X_flip ? range - offset : offset;
        u_int8_t* tile_array = this->tiledata->getObjectTile(tile_idx);
        u_int8_t one =  tile_array[offset * 2];
        u_int8_t two =  tile_array[(offset * 2) + 1];
        // figure out colour id based on tile data filp based on y
        for (size_t i = 0; i < 8; i++)
        {
            u_int8_t low = ((one) >> (i)) & 1;
            u_int8_t high = ((two) >> (i) & 1) << 1;
            if (Y_flip){
                res[i] = high + low;
            } else {
                res[7 - i] = high + low;
            }
        }
        //  
        if (x_coord >= 8 && x_coord < 160){
            x_coord -= 8;
            for (u_int8_t i = x_coord; i < x_coord + 8; i++)
            {
                if (i < 160){
                    if (win_bg_priority){
                        if (pixels[i] == 5 || pixels[i] == 0){
                            pixels[i] = palette[res[i - x_coord]];
                        }
                    } else {
                        pixels[i] = palette[res[i - x_coord]];
                    }
                }
                
                
            }

        }
        

    }



}

