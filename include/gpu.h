
#ifndef GPU_H
#define GPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include <vector>


class GPU
{
    
    public:
    GPU(Memory& memory);

    Memory memory;
    std::vector<uint8_t> bg_1; 
    std::vector<uint8_t> bg_2; 
    void READ_BACKGROUND(uint16_t starting_at);
    void READ_BACKGROUNDS();



};
#endif