
#include <stdio.h>
#include <iostream>
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include "gb.h"
    Memory::Memory(system_status_struct* system){
        mem = new uint8_t[65536];

        ROM = mem;
        SROMB = mem + 0x4000;
        VRAM = mem + 0x8000;
        SRAMB = mem + 0xA000;
        IRAM = mem + 0xC000;
        SA = mem + 0xFE00;
        IO = mem + 0xFF00;
        IF = mem + 0xFF0F;
        HR = mem + 0xFF80;
        IE = mem + 0xFFFF;
        SP = mem + 0xFFFE;
        DIV = mem + 0xFF04;
        TAC = mem + 0xFF07;
        TMA = mem + 0xFF06;
        TIMA = mem + 0xFF05;
        this->system = system;
        // if(!this->fill_memory(76)){
        //     spdlog::error("Memory not filled");
        // }
        
       
     
    };
   int Memory::fill_memory(uint8_t num){
       memset(this->mem,num,65536);
       return 1;
   }
   uint8_t Memory::get_bit_from_addr(uint16_t address, uint8_t bit){
       return (this->mem[address] >> bit) & 1;
   }
   uint8_t Memory::set_bit_from_addr(uint16_t address, uint8_t bit){
        (this->mem[address]) |= (1 << bit);
        return 0;
   }

uint8_t Memory::read_8_bit(uint16_t address){
    if (address == 0xFF44){
        return 0x90;
    }
       return this->mem[address];
   }
int Memory::write_8_bit(uint16_t address, uint8_t data){
    if (address == 0xFF04){
        this->system->m_cycles = 0;
        this->system->t_cycles = 0;
        this->mem[address] = 0;
        return 0;
    }
    this->mem[address] = data;
    return 0;
   }
uint16_t Memory::read_16_bit(uint16_t address){
    uint8_t low = this->mem[address];
    uint8_t high = this->mem[address + 1];
    // spdlog::info("low {:X} high {:X} result {:X}",low,high,((high << 8) | low));
    return ((high << 8) + low);
   }
int Memory::write_16_bit(uint16_t address, uint16_t data){
    uint8_t first = 0x00ff & data;
    uint8_t second = (0xff00 & data) >> 8;
    this->mem[address] = first;
    this->mem[address + 1] = second;
    if (address == 0xFF04){
        this->system->m_cycles = 0;
        this->system->t_cycles = 0;
        this->mem[address] = 0;
        return 0;
    }
    if (address + 1 == 0xFF04){
        this->system->m_cycles = 0;
        this->system->t_cycles = 0;
        this->mem[address + 1] = 0;
        return 0;
    }
    return 0;
   }

bool Memory::read_rom(char* path){
    
    std::ifstream myFile (path, std::ios::in | std::ios::binary);
    if (!myFile.is_open()) {
        std::cout << "Failed to open ROM file" << "\n";
        return false;
    }
    myFile.seekg(0,std::ios::end);
    int size = (int) myFile.tellg();
    
    if (size > 32769){
        std::cout<<"Rom too big "<< size << "> 32767" "\n";
        return 0;
    }
    myFile.seekg(0,std::ios::beg);
    myFile.read ((char*) this -> mem, size);
    if (!myFile) {
        spdlog::info("Rom not read");
        std::cout<<"Rom not read"<< "\n";
        exit(1);
        return 0;
    }
    std::cout<<"Cartridge Type: "<<std::hex<<(int)this->mem[0x0147]<< std::endl;
    return 1;
}


 
