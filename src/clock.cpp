#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "Clock.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
// TODO What does internal meean for timeing 
Clock::Clock(Memory& memory,uint16_t* system_counter): memory(memory){
    this->t_cycles_till_m_cycle = 3;
    this->div_counter = 255;
    this->memory.write_8_bit(0xFF04,0xABCC);
    this->internal_clock = system_counter;
}
// TODO figure out how to refactor this
void Clock::TICK(uint16_t how_many){
    for (size_t i = 0; i < how_many; i++)
    {
        if (not this->t_cycles_till_m_cycle){
            this->t_cycles_till_m_cycle = 4;
            (*this->internal_clock)++;
        }
        if (not this->div_counter){
            this->div_counter = 255;
            this->memory.write_8_bit(0xFF04,this->memory.read_8_bit(0xFF04) + 1);
        }
        this->t_cycles_till_m_cycle--;
        this->div_counter--;
    }
    
    
}