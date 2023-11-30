
#ifndef Objects_H
#define Objects_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"

#include "layer.h"
#include "tiledata.h"
#include <vector>
#include <map>
#include <array>

struct sprite
{
    u_int8_t* y_coord;
    u_int8_t* x_coord;
    u_int8_t* tile_idx;
    u_int8_t* metadata;
    u_int8_t OAM_pos;
};


class Objects
{
    public:
    Objects(Memory& memory, TileData& tiledata);

    Memory memory;
    TileData* tiledata;
    u_int8_t* object_n_data_ptr(u_int8_t idx);
    u_int8_t* get_object_tiledata(u_int8_t idx);
    uint8_t* object_map = new uint8_t[65536];
    void  object_pixels_on_line(u_int8_t line, std::array<u_int8_t,160>& pixels);
    void populate_palette(u_int16_t address,std::map < uint8_t, uint8_t >& palette);
    std::vector<sprite*> object_data_on_line(u_int8_t line);
    void ingest_objects();
    void scanline_emulator();
    std::array<sprite*,40> objects_data;
    std::array<sprite*,40>* objects_data_ptr;
};
#endif 