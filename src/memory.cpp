
#include <stdio.h>
#include <iostream>
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <fstream>
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
        SP = mem + 0xFFFE;
        if(!this->fill_memory(2)){
            spdlog::error("Memory not filled");
        }
    };
   int Memory::fill_memory(uint8_t num){
       memset(this->mem,num,65536);
       return 1;
   }
uint8_t Memory::read_8_bit(uint16_t address){
       return this->mem[address];
   }
int Memory::write_8_bit(uint16_t address, uint8_t data){
        this->mem[address] = data;
        return 0;
   }
uint16_t Memory::read_16_bit(uint16_t address){
    uint8_t first = this->mem[address];
    uint8_t second = this->mem[address + 1];
    return (second << 8) & first;;
   }
int Memory::write_16_bit(uint16_t address, uint16_t data){
    uint8_t first = 255 & data;
    uint8_t second = (65280 & data) >> 8;
    this->mem[address] = first;
    this->mem[address + 1] = second;
    return 0;
   }
bool Memory::read_rom(char* path){
    
    std::ifstream myFile (path, std::ios::in | std::ios::binary);
    myFile.seekg(0,std::ios::end);
    int size = (int) myFile.tellg();
    // Tetris is bigger than this and I dont know why
    // if (size > 32767){
    //     std::cout<<"Rom too big "<< size << "> 32767" "\n";
    //     return 0;
    // }
    myFile.seekg(0,std::ios::beg);
    myFile.read ((char*) this -> mem, size);
    if (!myFile) {
        spdlog::info("Rom not read");
        std::cout<<"Rom not read"<< "\n";
        return 0;
    }
    return 1;
}


 
