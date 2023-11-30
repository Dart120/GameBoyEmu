
#ifndef Layer_H
#define Layer_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "tiledata.h"
#include <vector>
#include <map>


class Layer
{
    
    public:
    Layer(Memory& memory, TileData& tiledata);

    Memory memory;
    // Going to point to the actual memory in my computer coz i want to read more than eight bits of this at a time and using the 16 bit idx of the array might make that a faff
    TileData* tiledata;
    u_int16_t tilemap_starts_at;
    uint8_t* tilemap = new uint8_t[1024];
    uint8_t** colour_map = new uint8_t*[256];



    uint8_t tile_idx_at(uint8_t x, uint8_t y);
    void tile_data_to_colour_map();
    void line_n_to_colours();
   
    virtual u_int8_t* get_tile_data(u_int8_t address) = 0;
    virtual u_int8_t read_tilemap_n(u_int8_t x, u_int8_t y, u_int8_t line_n) = 0;


};
#endif