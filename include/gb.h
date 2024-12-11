#ifndef GB_H
#define GB_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "cpu.h"
#include "gpu.h"
#include "timer.h"
#include "system_status.h"
#include <spdlog/spdlog.h>
#include <vector>
#include <unordered_set>

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
    void reset_timer();
    void start_dma(uint8_t data);
    Timer* timer;
    system_status_struct* system;
    uint16_t cycles_left_DMA = 0;
    std::unordered_set<uint8_t> dir_keys;
    std::unordered_set<uint8_t> but_keys;
    // std::chrono::_V2::system_clock::time_point last_sync;

    
    // CPU cpu;
    

};
#endif