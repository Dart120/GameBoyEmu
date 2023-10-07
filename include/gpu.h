
#ifndef GPU_H
#define GPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "tiledata.h"
#include "background.h"
#include "window.h"
#include "object.h"
#include <vector>
#include <map>


class GPU
{
    
    public:
    GPU(Memory& memory);

    Memory memory;
    TileData tiledata;
    Background background;
    Window window;
    Objects object;
    // Going to point to the actual memory in my computer coz i want to read more than eight bits of this at a time and using the 16 bit idx of the array might make that a faff
    
    void read_tiledata();



};
#endif