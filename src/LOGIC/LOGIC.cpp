#include "cpu.h"

void CPU::AND_1B_1C(uint8_t reg1, uint32_t *cycles){
    this->registers.set_flag(FLAG_H);
    this->registers.clear_flag(FLAG_C);
    this->registers.clear_flag(FLAG_N);
    char result = this->registers.registers.AF.A & reg1;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    *cycles-=1;
    this->registers.registers.PC++;
}
void CPU::AND_1B_2C(uint16_t address, uint32_t *cycles){
    uint8_t value = this->memory.read_8_bit(address);
    this->registers.set_flag(FLAG_H);
    this->registers.clear_flag(FLAG_C);
    this->registers.clear_flag(FLAG_N);
    char result = this->registers.registers.AF.A & value;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    *cycles-=2;
    this->registers.registers.PC++;
}

void CPU::XOR_1B_1C(uint8_t reg1, uint32_t *cycles){
    this->registers.clear_flag(FLAG_H);
    this->registers.clear_flag(FLAG_C);
    this->registers.clear_flag(FLAG_N);
    char result = this->registers.registers.AF.A ^ reg1;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    *cycles-=1;
    this->registers.registers.PC++;
}
void CPU::XOR_1B_2C(uint16_t address, uint32_t *cycles){
    uint8_t value = this->memory.read_8_bit(address);
    this->registers.clear_flag(FLAG_H);
    this->registers.clear_flag(FLAG_C);
    this->registers.clear_flag(FLAG_N);
    char result = this->registers.registers.AF.A ^ value;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    *cycles-=2;
    this->registers.registers.PC++;
}