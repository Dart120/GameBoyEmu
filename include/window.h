
#ifndef Window_H
#define Window_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"

#include "layer.h"
#include <vector>
#include <map>


class Window : public Layer
{
    public:
    Window(Memory& memory, TileData& tiledata): Layer(memory, tiledata){}
    u_int8_t* get_tile_data(u_int8_t address) override;
    u_int8_t read_tilemap_n(u_int8_t x, u_int8_t y, u_int8_t line_n) override;
    std::array<u_int8_t,160>  read_line(u_int8_t line);
};
#endif 