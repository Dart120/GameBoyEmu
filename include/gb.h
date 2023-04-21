#ifndef GB_H
#define GB_H
// #include<iostream>
// #define FMT_HEADER_ONLY

#include "memory.h"
#include "cpu.h"
#include "gpu.h"
#include "clock.h"
#include <spdlog/spdlog.h>
#include <vector>
extern std::shared_ptr<spdlog::logger> doctor;

class GB
{
    
    public:
    GB();
    uint16_t system_counter;
    Memory* memory;
    Clock* clock;
    GPU* gpu;
    CPU* cpu;

    
    // CPU cpu;
    

};
#endif