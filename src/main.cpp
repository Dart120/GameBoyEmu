// main.cpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "main.h"
#include "cpu.h"
#include "Registers.h"
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
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
    Registers registers;
    if (argc == 2){
        if (!memory.read_rom(argv[1])){
            std::cout << "Rom read not working\n";
        }
     
    }else{
        std::cout << "Please supply path to rom\n";
        exit(0);
    }
    
    CPU GB_CPU(memory,registers);
    int regTo = 255;
    if(!GB_CPU.registers.set_registers(regTo)){
        spdlog::info("Registers not set");
        
    }
    

    GB_CPU.FDE();
    

}