#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "timer.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

Timer::Timer(Memory& memory): memory(memory){
    std::cout <<"Created Timer" <<std::endl;
    
    
}
void Timer::process_4t_cycles(){
    if (TIMA_overflowed){
        TIMA_overflowed = false;
        this->memory.set_bit_from_addr(0xFF0F,2);
    }
    std::vector<uint16_t> TIMA_increment_rate = {1024, 16, 64, 256};
    this->DIV_counter+=4;
    *(this->memory.DIV)= this->DIV_counter >> 8;
    bool tima_enabled = (this->memory.get_bit_from_addr(0xFF07,2));
    uint8_t clock_select = this->memory.read_8_bit(0xFF07) & 0b00000011;
    uint8_t TIMA = this->memory.read_8_bit(0xFF05);
    if (tima_enabled){
        uint16_t t_cycles = TIMA_increment_rate[clock_select];
        if (this->DIV_counter % t_cycles == 0){
            if (this->memory.read_8_bit(0xFF05) == 0xFF){ 
                TIMA_overflowed = true;
                this->memory.write_8_bit(0xFF05, this->memory.read_8_bit(0xFF06));
            } else {
                this->memory.write_8_bit(0xFF05, TIMA+1);
            }
        }
        
    }
}

void Timer::reset_timer(){
    this->DIV_counter = 0;
    *(this->memory.DIV) = 0;
}
