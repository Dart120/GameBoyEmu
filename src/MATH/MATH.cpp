#include "cpu.h"
#include<iostream>
using namespace std;

void CPU::ADD_2B_2C(uint32_t *cycles){
    uint8_t data =  this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->registers->check_H_8_ADD(this->registers->registers.AF.A,data);
    this->registers->check_C_8_ADD(this->registers->registers.AF.A,data);
    this->registers->registers.AF.A += data;
    this->registers->check_if_result_zero(this->registers->registers.AF.A);
    this->registers->clear_flag(FLAG_N);
    *cycles-=2;
    this->registers->registers.PC += 2;
}
void CPU::ADD_1B_1C(uint8_t reg1, uint32_t *cycles){
    this->registers->check_H_8_ADD(this->registers->registers.AF.A, reg1);
    this->registers->check_C_8_ADD(this->registers->registers.AF.A, reg1);
    this->registers->registers.AF.A += reg1;
    this->registers->check_if_result_zero(this->registers->registers.AF.A);
    this->registers->clear_flag(FLAG_N);
    *cycles--;
    this->registers->registers.PC++;
}
void CPU::ADC_1B_1C(uint8_t reg1, uint32_t *cycles){
    uint8_t c = this->registers->get_flag(FLAG_C);
    this->registers->clear_flag(FLAG_N);
    this->registers->check_H_8_ADD(reg1,(uint8_t)  (c));
    this->registers->check_C_8_ADD(reg1,(uint8_t)  (c));
    uint8_t to_add = (reg1 + c);
    if (!this->registers->get_flag(FLAG_H)){
        this->registers->check_H_8_ADD(this->registers->registers.AF.A,to_add);
    }
    if (!this->registers->get_flag(FLAG_C)){
        this->registers->check_C_8_ADD(this->registers->registers.AF.A,to_add);
    }
    this->registers->registers.AF.A += (uint8_t) (reg1 + c);
    this->registers->check_if_result_zero(this->registers->registers.AF.A);
    *cycles--;
    this->registers->registers.PC++;
}
void CPU::ADC_2B_2C(uint32_t *cycles){
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    uint8_t c = this->registers->get_flag(FLAG_C);

    this->registers->check_H_8_ADD(this->registers->registers.AF.A,(uint8_t)  (d8 + c));
    this->registers->check_C_8_ADD(this->registers->registers.AF.A,(uint8_t)  (d8 + c));
    this->registers->registers.AF.A += (uint8_t) (d8 + c);
    this->registers->check_if_result_zero(this->registers->registers.AF.A);
    *cycles -= 2;
    this->registers->registers.PC += 2;
}

void CPU::ADD_1B_2C_8Bit(uint8_t reg1, uint32_t *cycles){
    this->registers->check_H_8_ADD(this->registers->registers.AF.A, reg1);
    this->registers->check_C_8_ADD(this->registers->registers.AF.A, reg1);
    this->registers->clear_flag(FLAG_N);
    this->registers->registers.AF.A += reg1;
    this->registers->check_if_result_zero(this->registers->registers.AF.A);
    *cycles-=2;
    this->registers->registers.PC++;
}
void CPU::ADD_1B_2C_16Bit(uint16_t reg1, uint32_t *cycles){
    this->registers->clear_flag(FLAG_N);
    this->registers->check_C_16_INC(this -> registers->registers.HL_double,reg1);
    this->registers->check_H_16_INC(this -> registers->registers.HL_double,reg1);
    
    this -> registers->registers.HL_double += reg1;
    (*cycles) -= 2;
    (this->registers->registers.PC) += 1;
}
// TODO another problem with megs website, this requires 8 bit check for flags but is noted as 16
void CPU::ADD_2B_4C(uint16_t* reg1, uint32_t *cycles){
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_Z);
    int8_t s8 = this->unsigned_8_to_signed_8(this->memory.read_8_bit(this->registers->registers.PC + 1));
    // this->registers->check_H_8_ADD((uint8_t) *reg1, this->memory.read_8_bit(this->registers->registers.PC + 1));
    // u_int16_t old_sp = *reg1;
    this->registers->check_C_8_ADD(*reg1,(int16_t) s8);
    this->registers->check_H_8_ADD((uint8_t) *reg1, s8);
    *reg1 += s8;
    // if ((*reg1&0xFF) < (old_sp&0xFF)){
    //     this->registers->set_flag(FLAG_C);
    // } else {
    //     this->registers->clear_flag(FLAG_C);
    // }
    
    (*cycles) -= 4;
    (this->registers->registers.PC) += 2;
}
void CPU::ADC_1B_2C_8Bit(uint8_t reg1, uint32_t *cycles){
    uint8_t c = this->registers->get_flag(FLAG_C);
    this->registers->check_H_8_ADD(this->registers->registers.AF.A ,(uint8_t)  (reg1 + c));
    this->registers->check_C_8_ADD(this->registers->registers.AF.A ,(uint8_t)  (reg1 + c));
    this->registers->registers.AF.A += (uint8_t) (reg1 + c);
    this->registers->check_if_result_zero(reg1);
    *cycles-=2;
    this->registers->registers.PC++;
}
void CPU::SUB_1B_1C(uint8_t reg1, uint32_t *cycles){
    this->registers->check_H_8_SUB(this->registers->registers.AF.A, reg1);
    this->registers->check_C_8_SUB(this->registers->registers.AF.A, reg1);
    char result = this->registers->registers.AF.A - reg1;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    *cycles-=1;
    this->registers->registers.PC++;
}
void CPU::SUB_2B_2C(uint32_t *cycles){
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->registers->check_H_8_SUB(this->registers->registers.AF.A, d8);
    this->registers->check_C_8_SUB(this->registers->registers.AF.A, d8);
    char result = this->registers->registers.AF.A - d8;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    *cycles-=2;
    this->registers->registers.PC+=2;
}
void CPU::SUB_1B_2C(uint16_t address, uint32_t *cycles){
    uint8_t value = this->memory.read_8_bit(address);
    this->registers->check_H_8_SUB(this->registers->registers.AF.A, value);
    this->registers->check_C_8_SUB(this->registers->registers.AF.A, value);
    char result = this->registers->registers.AF.A - value;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    *cycles-=2;
    this->registers->registers.PC++;
}

void CPU::SBC_1B_1C(uint8_t reg1, uint32_t *cycles){
    uint8_t c = this->registers->get_flag(FLAG_C);
    this->registers->check_H_8_ADD(reg1,(uint8_t)  (c));
    this->registers->check_C_8_ADD(reg1,(uint8_t)  (c));
    uint8_t to_sub = (reg1 + c);
    if (!this->registers->get_flag(FLAG_H)){
        this->registers->check_H_8_SUB(this->registers->registers.AF.A,to_sub);
    }
    if (!this->registers->get_flag(FLAG_C)){
        this->registers->check_C_8_SUB(this->registers->registers.AF.A,to_sub);
    }
    char result = this->registers->registers.AF.A - to_sub;
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    *cycles-=1;
    this->registers->registers.PC++;
}
void CPU::SBC_1B_2C(uint16_t address, uint32_t *cycles){
    uint8_t c = this->registers->get_flag(FLAG_C);
    uint8_t reg1 = this->memory.read_8_bit(address);
    this->registers->check_H_8_ADD(reg1,(uint8_t)  (c));
    this->registers->check_C_8_ADD(reg1,(uint8_t)  (c));
    uint8_t to_sub = (reg1 + c);
    if (!this->registers->get_flag(FLAG_H)){
        this->registers->check_H_8_SUB(this->registers->registers.AF.A,to_sub);
    }
    if (!this->registers->get_flag(FLAG_C)){
        this->registers->check_C_8_SUB(this->registers->registers.AF.A,to_sub);
    }
    char result = this->registers->registers.AF.A - to_sub;
   
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    *cycles-=2;
    this->registers->registers.PC++;
}
void CPU::SBC_2B_2C(uint32_t *cycles){
    uint8_t C = this->registers->get_flag(FLAG_C);
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->registers->check_H_8_SUB(this->registers->registers.AF.A,uint8_t (d8 + C));
    this->registers->check_C_8_SUB(this->registers->registers.AF.A,uint8_t (d8 + C));
    char result = this->registers->registers.AF.A - (d8 + C);
    this->registers->registers.AF.A = result;
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    *cycles-=2;
    this->registers->registers.PC += 2;
}
