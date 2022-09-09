// main.cpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "main.h"
#include "cpu.h"
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
int main()
{
   
    try 
    {
        auto logger = spdlog::basic_logger_mt("basic_logger", "./logs/basic-log.txt");
        spdlog::set_default_logger(logger);
    spdlog::flush_on(spdlog::level::info);
    

    
    
    
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    Memory memory;
    CPU GB_CPU(memory);
    int regTo = 255;
    if(!GB_CPU.set_registers(regTo)){
        spdlog::info("Registers not set");
        
    }
    GB_CPU.FDE();
    

}