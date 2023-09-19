
#ifndef TileData_H
#define TileData_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include <vector>
#include <map>


class TileData
{
    
    public:
    TileData(Memory& memory);

    Memory memory;
    void read_tiledata();
    u_int8_t* getObjectTile(u_int8_t address);
    u_int8_t* getBGTile(u_int8_t address);
    private:
    // Going to point to the actual memory in my computer coz i want to read more than eight bits of this at a time and using the 16 bit idx of the array might make that a faff
    std::map < uint8_t, uint8_t* > object_tile_address_mem_address;
    std::map < uint8_t, uint8_t* > bg_tile_address_mem_address;
    void read_block_n(u_int16_t starting_at, u_int16_t ending_at, u_int8_t starting_idx, std::map < uint8_t, uint8_t* >& map_to_populate);
    
    



};
#endif