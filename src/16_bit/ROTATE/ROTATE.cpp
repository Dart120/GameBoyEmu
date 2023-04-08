#include "cpu.h"


void CPU::RLC_2B_2C(uint8_t* reg, uint32_t *cycles){
    uint8_t last_bit = *reg >> 7;
    *reg = (*reg << 1) + last_bit;
    this->registers.check_if_result_zero(*reg);
    last_bit ? this->registers.set_flag(FLAG_C) : this->registers.clear_flag(FLAG_C);
    this->registers.registers.PC += 2;
    *cycles -= 2;
}
void CPU::RLC_2B_4C(uint32_t *cycles){
    uint8_t last_bit = this->memory.read_8_bit(this->registers.registers.HL_double) >> 7;
    uint8_t result = (this->memory.read_8_bit(this->registers.registers.HL_double) << 1)  + last_bit;
    this->registers.check_if_result_zero(result);
    last_bit ? this->registers.set_flag(FLAG_C) : this->registers.clear_flag(FLAG_C);
    this->memory.write_8_bit(this->registers.registers.HL_double, result);
    this->registers.registers.PC += 2;
    *cycles -= 4;
}
void CPU::RRC_2B_2C(uint8_t* reg, uint32_t *cycles){
    uint8_t first_bit = *reg & 1;
    *reg = (*reg >> 1) + (first_bit << 7);
    this->registers.check_if_result_zero(*reg);
    first_bit ? this->registers.set_flag(FLAG_C) : this->registers.clear_flag(FLAG_C);
    this->registers.registers.PC += 2;
    *cycles -= 2;
}
void CPU::RRC_2B_4C(uint32_t *cycles){
    uint8_t first_bit = this->memory.read_8_bit(this->registers.registers.HL_double) & 1;
    uint8_t result = (this->memory.read_8_bit(this->registers.registers.HL_double) << 1)  + (first_bit << 7);
    this->registers.check_if_result_zero(result);
    first_bit ? this->registers.set_flag(FLAG_C) : this->registers.clear_flag(FLAG_C);
    this->memory.write_8_bit(this->registers.registers.HL_double, result);
    this->registers.registers.PC += 2;
    *cycles -= 4;
}
void CPU::RL_2B_2C(uint8_t* reg, uint32_t *cycles){
    uint8_t last_bit = this->registers.get_flag(FLAG_C);
    *reg = (*reg << 1) + last_bit;
    this->registers.check_if_result_zero(*reg);
    this->registers.registers.PC += 2;
    *cycles -= 2;
}
void CPU::RL_2B_4C(uint32_t *cycles){
    uint8_t last_bit = this->registers.get_flag(FLAG_C);
    uint8_t result = (this->memory.read_8_bit(this->registers.registers.HL_double) << 1)  + last_bit;
    this->registers.check_if_result_zero(result);
    this->memory.write_8_bit(this->registers.registers.HL_double, result);
    this->registers.registers.PC += 2;
    *cycles -= 4;
}
void CPU::RR_2B_2C(uint8_t* reg, uint32_t *cycles){
    uint8_t first_bit = this->registers.get_flag(FLAG_C);
    *reg = (*reg >> 1) + (first_bit << 7);
    this->registers.check_if_result_zero(*reg);
    this->registers.registers.PC += 2;
    *cycles -= 2;
}
void CPU::RR_2B_4C(uint32_t *cycles){
    uint8_t first_bit = this->registers.get_flag(FLAG_C);
    uint8_t result = (this->memory.read_8_bit(this->registers.registers.HL_double) << 1)  + (first_bit << 7);
    this->registers.check_if_result_zero(result);
    this->memory.write_8_bit(this->registers.registers.HL_double, result);
    this->registers.registers.PC += 2;
    *cycles -= 4;
}