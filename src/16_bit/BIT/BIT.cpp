#include "cpu.h"


void CPU::BIT_2B_2C(uint8_t bit_n,uint8_t reg, uint32_t *cycles){
    bool bit = (reg >> bit_n) & 1;
    bit ? this->registers.clear_flag(FLAG_Z) : this->registers.set_flag(FLAG_Z);
    this->registers.set_flag(FLAG_H);
    this->registers.registers.PC += 2;
    *cycles -= 2;
}
void CPU::BIT_2B_3C(uint8_t bit_n, uint32_t *cycles){
    bool bit = (this->memory.read_8_bit(this->registers.registers.HL_double) >> bit_n) & 1;
    bit ? this->registers.clear_flag(FLAG_Z) : this->registers.set_flag(FLAG_Z);
    this->registers.set_flag(FLAG_H);
    this->registers.registers.PC += 2;
    *cycles -= 3;
}

