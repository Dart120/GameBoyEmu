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
    for (size_t i = 0; i < 40; i++)
    {
        u_int8_t* addr = this->object_n_data_ptr(i);
        objects[i][0] = addr;
        objects[i][1] = addr + 1;
        objects[i][2] = addr + 2;
        objects[i][3] = addr + 3;
    }
    
}
void Objects::scanline_emulator(){
    for (size_t LY = 0; LY < 154; LY++)
    {
        u_int8_t objects_drawn = 0;
        while (objects_drawn < 10){
            
        }

    }
    
}

