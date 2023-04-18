
#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>


class Memory
{
    // Access specifier
    public:
    Memory(uint16_t* system_counter);
    // Data Members
    
    uint8_t* mem;
    uint8_t* ROM;
    uint8_t* SROMB;
    uint8_t* VRAM;
    uint8_t* SRAMB;
    uint8_t* IRAM;
    uint8_t* SA;
    uint8_t* IO;
    uint8_t* HR;
    uint8_t* IR;
    uint8_t* SP;
  
  
    int fill_memory(uint8_t num);
    
    uint8_t read_8_bit(uint16_t address);
    int write_8_bit(uint16_t address, uint8_t data);
    uint16_t read_16_bit(uint16_t address);
    int write_16_bit(uint16_t address, uint16_t data);
    bool read_rom(char* name);
    // Member Functions()
 
};
#endif