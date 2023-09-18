// main.cpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "gb.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
std::shared_ptr<spdlog::logger> doctor;
int main(int argc, char *argv[])
{
   
    // try 
    // {
    //     auto logger = spdlog::basic_logger_mt("basic_logger", "./logs/basic-log.txt");
    //     spdlog::set_default_logger(logger);
    // spdlog::flush_on(spdlog::level::info);
    

    
    
    
    // }
    // catch (const spdlog::spdlog_ex &ex)
    // {
    //     std::cout << "Log init failed: " << ex.what() << std::endl;
    // }
    // clock = new CLOCK()
    // uint16_t system_counter = 0;
    // Memory memory;
    // Registers registers;
    // if (argc == 2){
    //     if (!memory.read_rom(argv[1])){
    //         std::cout << "Rom read not working\n";
    //     }
     
    // }else{
    //     std::cout << "Please supply path to rom\n";
    //     exit(0);
    // }
    
    // CPU GB_CPU(memory,registers);
    // int regTo = 255;
    // if(!GB_CPU.registers.set_registers(regTo)){
    //     spdlog::info("Registers not set");
        
    // }
    

    // GB_CPU.FDE();
    GB gb(argv[2]);
   
    spdlog::info("arg1 {} arg2 {}", argv[1], argv[2]);
     if (argc == 3){
        spdlog::info("Path to ROM is: {}\n", argv[1]);
        if (!gb.memory->read_rom(argv[1])){
            std::cout << "Rom read not working\n";
        }
     
    }else{
        std::cout << "Please supply path to rom\n";
        exit(0);
    }
    // spdlog::info("First Few Bytes {:X} {:X} {:X} {:X}", gb.memory->mem[0], gb.memory->mem[1], gb.memory->mem[2], gb.memory->mem[3]);
    gb.gpu->read_tilemaps();
    gb.cpu->FDE();
    

}