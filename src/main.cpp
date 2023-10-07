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
    gb.go();
   
    

}