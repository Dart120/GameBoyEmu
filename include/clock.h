#ifndef CLOCK_H
#define CLOCK_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"

#include <vector>

class Clock
{
    public:
    Clock(Memory& memory,uint16_t* system_counter);
    void TICK(uint16_t how_many);
    private:
    Memory memory;
    uint16_t* internal_clock;
    uint8_t t_cycles_till_m_cycle;
    uint8_t div_counter;

};
#endif