#include "cpu.h"


void CPU::RET_COND(uint8_t COND, uint16_t *cycles){
    if (COND){
        uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
        this->registers->registers.SP++;
        uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
        uint16_t result = low + (uint16_t) (high << 8);
        this->registers->registers.PC = result;
        *cycles += 5;
        this->registers->registers.SP++;
    } else {
        this->registers->registers.PC++;
        *cycles += 2;
    }
}
void CPU::RET_UNCOND(uint16_t *cycles){
    
    uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;
    uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
    uint16_t result = low + (uint16_t) (high << 8);
    // spdlog::info("ret high: {:X}, low: {:X}",high,low);
    // spdlog::info("Fool: {:X}",result);
  
    this->registers->registers.PC = result;
    *cycles += 4;
    this->registers->registers.SP++;
}
void CPU::RETI(uint16_t *cycles){
    this->registers->IME = true;
    uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;
    uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
    uint16_t result = low + (uint16_t) (high << 8);
    this->registers->registers.PC = result;
    *cycles += 4;
    this->registers->registers.SP++;
}
