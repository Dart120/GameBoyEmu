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
    std::cout <<"Created Tiledata" <<std::endl;
    // std::cout << "Address of map td: " << &this->bg_tile_address_mem_address << std::endl;
    this->bg_tile_address_mem_address_ptr = &this->bg_tile_address_mem_address;
    this->object_tile_address_mem_address_ptr = &this->object_tile_address_mem_address;
}
void TileData::read_block_n(u_int16_t starting_at, u_int16_t ending_at, u_int8_t starting_idx, std::map < uint8_t, uint8_t* >& map_to_populate){
    // modified to always return pointers to 3
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
    // std::cout << reinterpret_cast<uintptr_t>(this->bg_tile_address_mem_address[0]) <<std::endl;
    // std::cout << "Address of map: " << &this->bg_tile_address_mem_address << std::endl;
    // std::cout <<(int) *this->bg_tile_address_mem_address[0] <<std::endl;
    // if (this->bg_tile_address_mem_address.find(0xc3) != this->bg_tile_address_mem_address.end()) {
    //         // Key exists in the map
    //         std::cout << "key exists" <<std::endl;
    //     } else {
    //         // Key does not exist in the map
    //         std::cout << "no key" <<std::endl;
    //     }
    // std::cout << "here" <<std::endl;
}
u_int8_t* TileData::getObjectTile(u_int8_t address){
    return this->object_tile_address_mem_address[address];
}
u_int8_t* TileData::getBGTile(u_int8_t address){
    // std::cout << this->memory.mem[0]<<std::endl;
    // u_int8_t u = 5;
    // exit(0);
    // return &u;
    
    if (this->memory.get_bit_from_addr(0xFF40,4)){
        // std::cout << " tile starts at " << (*(*this->object_tile_address_mem_address_ptr)[address])<<std::endl;
        return (*this->object_tile_address_mem_address_ptr)[address];
    } else {
        // std::cout << "bg"<<std::endl;
        // if ((*this->bg_tile_address_mem_address_ptr).find(address) != (*this->bg_tile_address_mem_address_ptr).end()) {
        //     // Key exists in the map
        //     std::cout << "key exists tile "<<(int)address<< std::hex <<std::endl;
        // } else {
        //     // Key does not exist in the map
        //     std::cout <<(int)address<< std::hex <<std::endl;
        // }
        return (*this->bg_tile_address_mem_address_ptr)[address];
        
    }
    
}