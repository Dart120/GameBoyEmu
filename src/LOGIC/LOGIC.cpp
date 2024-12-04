#include "cpu.h"

void CPU::AND_1B_1C(uint8_t reg1, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->set_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A & reg1;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=1;
    this->registers->registers.PC++;
}
void CPU::AND_1B_2C(uint16_t address, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t value = this->memory.read_8_bit(address);
    this->registers->set_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A & value;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=2;
    this->registers->registers.PC++;
}
void CPU::AND_2B_2C(uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    this->registers->set_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    uint8_t result = this->registers->registers.AF.A & d8;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=2;
    this->registers->registers.PC += 2;
}

void CPU::XOR_1B_1C(uint8_t reg1, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A ^ reg1;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=1;
    this->registers->registers.PC++;
}
void CPU::XOR_1B_2C(uint16_t address, uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t value = this->memory.read_8_bit(address);
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A ^ value;
    this->process_4t_cycles();
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);

    // *cycles += 2;
    this->registers->registers.PC++;
}
void CPU::XOR_2B_2C(uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A ^ d8;
    this->process_4t_cycles();
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=2;
    this->registers->registers.PC +=2 ;
}
void CPU::OR_1B_1C(uint8_t reg1, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A | reg1;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=1;
    this->registers->registers.PC++;
}
void CPU::OR_1B_2C(uint16_t address, uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t value = this->memory.read_8_bit(address);
    this->process_4t_cycles();
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A | value;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);

    // *cycles+=2;
    this->registers->registers.PC++;
}
void CPU::OR_2B_2C(uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t value = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    char result = this->registers->registers.AF.A | value;
    this->process_4t_cycles();
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    // *cycles+=2;
    this->registers->registers.PC += 2;
}
void CPU::CP_1B_1C(uint8_t reg1, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->check_H_8_SUB(this->registers->registers.AF.A, reg1);
    this->registers->check_C_8_SUB(this->registers->registers.AF.A, reg1);
    char result = this->registers->registers.AF.A - reg1;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    // *cycles+=1;
    this->registers->registers.PC++;
}
void CPU::CP_2B_2C(uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    this->registers->check_H_8_SUB(this->registers->registers.AF.A, d8);
    this->registers->check_C_8_SUB(this->registers->registers.AF.A, d8);
    char result = this->registers->registers.AF.A - d8;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    // *cycles+=2;
    this->registers->registers.PC += 2;
}
void CPU::CP_1B_2C(uint16_t address, uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t value = this->memory.read_8_bit(address);
    this->process_4t_cycles();
    this->registers->check_H_8_SUB(this->registers->registers.AF.A, value);
    this->registers->check_C_8_SUB(this->registers->registers.AF.A, value);
    char result = this->registers->registers.AF.A - value;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
  
    // *cycles+=2;
    this->registers->registers.PC++;
}