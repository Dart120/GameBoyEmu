#include "cpu.h"


void CPU::POP(uint16_t* reg, uint32_t *cycles){
    uint8_t low = this->memory.read_8_bit(this->registers.registers.SP);
    this->registers.registers.SP++;
    uint8_t high = this->memory.read_8_bit(this->registers.registers.SP);
    uint16_t result = low + uint16_t (high << 8);
    *reg = result;
    *cycles -= 3;
    this->registers.registers.PC++;
}
void CPU::PUSH(uint16_t* reg, uint32_t *cycles){
    this->registers.registers.SP--;
    uint8_t high = this->memory.read_8_bit(this->registers.registers.SP);
    this->registers.registers.SP--;
    uint8_t low = this->memory.read_8_bit(this->registers.registers.SP);
    *reg = low + uint16_t (high << 8);
    this->registers.registers.PC++;
    *cycles -= 4;
}