
#include <stdio.h>
#include <iostream>
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include "gb.h"
#include "modes.h"
// pass a pointer to the gpu field
// TODO Deal with DMA Transfer
    Memory::Memory(std::function<void()> reset_timer, MODES& GPU_mode): reset_timer(reset_timer), GPU_mode(GPU_mode) {
        std::cout<<"Memory has been created"<< "\n";
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
        // this->system = system;
        this->fill_memory();
    
        
       
     
    };
   void Memory::fill_memory(){
       this->mem[0xFF40] = 0x91;
       this->mem[0xFF46] = 0xFF;
       this->mem[0xFF47] = 0xFC;
       this->mem[0xFF48] = 0xFF;
       this->mem[0xFF49] = 0xFF;
       this->mem[0xFF0F] = 0xE1;
       this->mem[0xFF00] = 0x0F;
       this->mem[0xFF02] = 0x7E;
       this->mem[0xFF04] = 0xAC;
       this->mem[0xFF00] = 0xFF;
   }
   bool Memory::is_inaccessible(uint16_t address){
    // need to check 
    // u_int16_t OAM[2] = {0xFE00, 0xFE9F};
    // u_int16_t VRAM[2] = {0x8000, 0x97FF};
    // u_int16_t PALETTES[2] = {0xFF47, 0xFF49};
    // auto between = [](u_int16_t* range, uint16_t address) {return address >= range[0] and address <= range[1]; };
    // switch (this->GPU_mode)
    // {
    // case OAM_SCAN:
    //     return between(OAM,address);
    //     break;
    // case DRAW:
    //     return between(OAM,address) || between(VRAM,address) || between(PALETTES,address);
    //     break;
    // default:
    //     return false;
    //     break;
    // }
    return false;
     
   }
   uint8_t Memory::get_bit_from_addr(uint16_t address, uint8_t bit){
        if (this->is_inaccessible(address)){
            return 0xFF;
        }
       return (this->mem[address] >> bit) & 1;
   }
  
   uint8_t Memory::clear_bit_from_addr(uint16_t address, uint8_t bit){
        if (this->is_inaccessible(address)){
            return 0xFF;
        }
        (this->mem[address]) &= (~(1 << bit));
        return 0;
   }
   uint8_t Memory::set_bit_from_addr(uint16_t address, uint8_t bit){
        if (this->is_inaccessible(address)){
            return 0xFF;
        }
        (this->mem[address]) |= (1 << bit);
        return 0;
   }

uint8_t Memory::read_8_bit(uint16_t address){
    if (this->is_inaccessible(address)){
            return 0xFF;
        }
 
    // if (address == 0xFF44){
    //     return 0x90;
    // }
       return this->mem[address];
   }
int Memory::write_8_bit(uint16_t address, uint8_t data){
    if (this->is_inaccessible(address)){
            return 0xFF;
        }
    // FIXME TIME
    if (address == 0xFF04){
        reset_timer();
        return 0;
    }
    if (address == 0xFF00){
       return 0;
    }
    if (address >= 0xFF10 && address <= 0xFF3F) {
        // Stub write to sound registers
        // Optionally log for debugging
        // spdlog::info("Stubbed write to sound register 0x{:04X} with value 0x{:02X}", addr, value);
        return 0 ;
    }
    this->mem[address] = data;
    return 0;
   }
uint16_t Memory::read_16_bit(uint16_t address){
    if (this->is_inaccessible(address)){
            return 0xFFFF;
    }
    uint8_t low = this->mem[address];
    uint8_t high = this->mem[address + 1];
    // spdlog::info("low {:X} high {:X} result {:X}",low,high,((high << 8) | low));
    return ((high << 8) + low);
   }
int Memory::write_16_bit(uint16_t address, uint16_t data){
    if (this->is_inaccessible(address)){
        return 0xFFFF;
    }
    uint8_t first = 0x00ff & data;
    uint8_t second = (0xff00 & data) >> 8;
    this->mem[address] = first;
    this->mem[address + 1] = second;
    if (address == 0xFF04){
        reset_timer();
        this->mem[address] = 0;
        return 0;
    }
    if (address + 1 == 0xFF04){
        reset_timer();
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
    // std::cout<<"Cartridge Type: "<<std::hex<<(int)this->mem[0x0147]<< std::endl;
    return 1;
}
bool Memory::read_boot_rom(char* path){
    // FIXME,Seperate bootrom and normal room
    std::ifstream myFile (path, std::ios::in | std::ios::binary);
    if (!myFile.is_open()) {
        std::cout << "Failed to open ROM file" << "\n";
        return false;
    }
    myFile.seekg(0,std::ios::end);
    int size = (int) myFile.tellg();
    myFile.seekg(0,std::ios::beg);
    myFile.read ((char*) this -> mem, size);
    if (!myFile) {
        spdlog::info("Rom not read");
        std::cout<<"Rom not read"<< "\n";
        exit(1);
        return 0;
    }
    // std::cout<<"Cartridge Type: "<<std::hex<<(int)this->mem[0x0147]<< std::endl;
    return 1;
}


 
