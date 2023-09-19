#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "tiledata.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

TileData::TileData(Memory& memory): memory(memory){
        this->memory = memory;
    }
void TileData::read_block_n(u_int16_t starting_at, u_int16_t ending_at, u_int8_t starting_idx, std::map < uint8_t, uint8_t* >& map_to_populate){
    
    u_int16_t curr = starting_at;
    u_int16_t curr_idx = starting_idx;
    while (curr < ending_at){
        map_to_populate[curr_idx] = &this->memory.mem[curr];
        curr += 16;
        curr_idx++;
    }
}
void TileData::read_tiledata(){
    this->read_block_n(0x8000, 0x87FF, 0, this->object_tile_address_mem_address);
    this->read_block_n(0x8800, 0x8FFF, 128, this->object_tile_address_mem_address);
    this->read_block_n(0x9000, 0x97FF, 0, this->bg_tile_address_mem_address);
    this->read_block_n(0x8800, 0x8FFF, 128, this->bg_tile_address_mem_address);
}
u_int8_t* TileData::getObjectTile(u_int8_t address){
    return this->object_tile_address_mem_address[address];
}
u_int8_t* TileData::getBGTile(u_int8_t address){
    if (this->memory.get_bit_from_addr(0xFF40,4)){
        return this->object_tile_address_mem_address[address];
    } else {
        return this->bg_tile_address_mem_address[address];
    }
    
}