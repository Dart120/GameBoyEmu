
#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include <functional>
#include "system_status.h"
#include "modes.h"

struct system_status_struct;
class Memory
{
    // Access specifier
    public:
    Memory(std::function<void()> reset_timer, uint16_t& cycles_left_dma, MODES& GPU_mode);
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
    uint8_t* IE;
    uint8_t* IF;
    uint8_t* SP;
    uint8_t* DIV;
    uint8_t* TAC;
    uint8_t* TMA;
    uint8_t* TIMA;
  
    std::function<void()> reset_timer;
    uint16_t& cycles_left_dma;
    bool start_dma;
    MODES& GPU_mode;
    void fill_memory();
    uint8_t get_bit_from_addr(uint16_t address, uint8_t bit);
    uint8_t set_bit_from_addr(uint16_t address, uint8_t bit);
    uint8_t clear_bit_from_addr(uint16_t address, uint8_t bit);
    uint8_t read_8_bit(uint16_t address);
    int write_8_bit(uint16_t address, uint8_t data);
    uint16_t read_16_bit(uint16_t address);
    int write_16_bit(uint16_t address, uint16_t data);
    bool read_rom(char* name);
    bool read_boot_rom(char* name);
    bool is_inaccessible(uint16_t address);
    bool is_write_inaccessible(uint16_t address);
    
    // Member Functions()
 
};
#endif