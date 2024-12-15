
#ifndef Timer_H
#define Timer_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include <vector>
#include <map>


class Timer
{
    
    public:
    Timer(Memory& memory);

    Memory memory;
    uint16_t DIV_counter = 0x0000;
    void process_4t_cycles();
    void reset_timer();
    bool TIMA_overflowed = false;




};
#endif