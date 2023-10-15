
#ifndef Objects_H
#define Objects_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"

#include "layer.h"
#include "tiledata.h"
#include <vector>
#include <map>


class Objects
{
    public:
    Objects(Memory& memory, TileData& tiledata);

    Memory memory;
    TileData* tiledata;
    u_int8_t* object_n_data_ptr(u_int8_t idx);
    u_int8_t* get_object_tiledata(u_int8_t idx);
    uint8_t* object_map = new uint8_t[65536];
    void ingest_objects();
    void scanline_emulator();
    std::array<std::array<u_int8_t*,4>,40> objects;
    std::array<std::array<u_int8_t,4>,40>* objects_ptr;
};
#endif 