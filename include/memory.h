#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
class Memory
{
    // Access specifier
    public:
    Memory();
    // Data Members
    
    u_int8_t* mem;
    u_int8_t* ROM;
    uint8_t* SROMB;
    uint8_t* VRAM;
    uint8_t* SRAMB;
    uint8_t* IRAM;
    uint8_t* SA;
    uint8_t* IO;
    uint8_t* HR;
    uint8_t* IR;
    uint8_t* SP;
    int fill_memory(u_int8_t num);
    
    u_int8_t read_8_bit(u_int16_t address);
    int write_8_bit(u_int16_t address, u_int8_t data);
    u_int16_t read_16_bit(u_int16_t address);
    int write_16_bit(u_int16_t address, u_int16_t data);
    // Member Functions()
 
};
#endif