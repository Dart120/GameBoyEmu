#include "cpu.h"


void CPU::RET_COND(uint8_t COND, uint32_t *cycles){
    if (COND){
        uint8_t low = this->memory.read_8_bit(this->registers.registers.SP);
        this->registers.registers.SP++;
        uint8_t high = this->memory.read_8_bit(this->registers.registers.SP);
        uint16_t result = low + uint16_t (high << 8);
        this->registers.registers.PC = result;
        *cycles -= 5;
    } else {
        *cycles -= 2;
    }
}
void CPU::RET_UNCOND(uint32_t *cycles){
    uint8_t low = this->memory.read_8_bit(this->registers.registers.SP);
    this->registers.registers.SP++;
    uint8_t high = this->memory.read_8_bit(this->registers.registers.SP);
    uint16_t result = low + uint16_t (high << 8);
    this->registers.registers.PC = result;
    *cycles -= 4;
}