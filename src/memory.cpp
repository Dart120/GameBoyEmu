
#include <stdio.h>
#include <iostream>
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
    Memory::Memory(){
        mem = new uint8_t[65536];
        ROM = mem;
        SROMB = mem + 0x4000;
        VRAM = mem + 0x8000;
        SRAMB = mem + 0xA000;
        IRAM = mem + 0xC000;
        SA = mem + 0xFE00;
        IO = mem + 0xFF00;
        HR = mem + 0xFF80;
        IR = mem + 0xFFFF;
        if(!this->fill_memory(2)){
            spdlog::error("Memory not filled");
        }
    };
   int Memory::fill_memory(u_int8_t num){
       memset(this->mem,num,65536);
       return 1;
   }
u_int8_t Memory::read_8_bit(u_int16_t address){
       return this->mem[address];
   }
int Memory::write_8_bit(u_int16_t address, u_int8_t data){
        this->mem[address] = data;
        return 0;
   }
u_int16_t Memory::read_16_bit(u_int16_t address){
    u_int8_t first = this->mem[address];
    u_int8_t second = this->mem[address + 1];
    return (second << 8) & first;;
   }
int Memory::write_16_bit(u_int16_t address, u_int16_t data){
    u_int8_t first = 255 & data;
    u_int8_t second = (65280 & data) >> 8;
    this->mem[address] = first;
    this->mem[address + 1] = second;
    return 0;
   }

 
