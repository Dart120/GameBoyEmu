#include "cpu.h"


void CPU::BIT_2B_2C(uint8_t bit_n,uint8_t reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    bool bit = (reg >> bit_n) & 1;
    bit ? this->registers->clear_flag(FLAG_Z) : this->registers->set_flag(FLAG_Z);
    this->registers->set_flag(FLAG_H);
    this->registers->clear_flag(FLAG_N);
    this->registers->registers.PC += 2;
    // *cycles += 2;
}
void CPU::BIT_2B_3C(uint8_t bit_n, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    bool bit = (this->memory.read_8_bit(this->registers->registers.HL_double) >> bit_n) & 1;
    this->process_4t_cycles();
    bit ? this->registers->clear_flag(FLAG_Z) : this->registers->set_flag(FLAG_Z);
    this->registers->set_flag(FLAG_H);
    this->registers->clear_flag(FLAG_N);
    this->registers->registers.PC += 2;
    // *cycles += 3;
}
void CPU::RES_2B_2C(uint8_t bit_n,uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t sauce = ~(1 << bit_n);
    *reg = (*reg & sauce);
    this->registers->registers.PC += 2;
    // *cycles += 2;
}
void CPU::RES_2B_4C(uint8_t bit_n, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t sauce = ~(1 << bit_n);
    this->process_4t_cycles();
    this->memory.write_8_bit(this->registers->registers.HL_double,this->memory.read_8_bit(this->registers->registers.HL_double)  & sauce);
    this->process_4t_cycles();
    this->registers->registers.PC += 2;
    // *cycles += 4;
}
void CPU::SET_2B_2C(uint8_t bit_n,uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t sauce = (1 << bit_n);
    *reg = (*reg | sauce);
    this->registers->registers.PC += 2;
    // (*cycles) += 2;
}
void CPU::SET_2B_4C(uint8_t bit_n, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t sauce = (1 << bit_n);
    this->process_4t_cycles();
    this->memory.write_8_bit(this->registers->registers.HL_double,this->memory.read_8_bit(this->registers->registers.HL_double)  | sauce);
    this->process_4t_cycles();
    this->registers->registers.PC += 2;
    // *cycles += 4;
}

