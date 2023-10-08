#ifndef GB_H
#define GB_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "cpu.h"
#include "gpu.h"
#include "system_status.h"
#include <spdlog/spdlog.h>
#include <vector>
extern std::shared_ptr<spdlog::logger> doctor;

class GB
{
    
    public:
    GB(std::string log_into);
    uint16_t system_counter;
    Memory* memory;
    GPU* gpu;
    CPU* cpu;
    void go();
    void process_t_cycle();

    
    // CPU cpu;
    

};
#endif