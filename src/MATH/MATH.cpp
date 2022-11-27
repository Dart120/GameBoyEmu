#include "cpu.h"


void CPU::ADD_1B_1C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_INC(*reg1, reg2);
    this->registers.check_C_INC(*reg1, reg2);
    this->registers.registers.AF.A += reg2;
    this->registers.check_if_result_zero(*reg1);
    *cycles--;
    this->registers.registers.PC++;
}
void CPU::ADC_1B_1C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_INC(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.check_C_INC(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.registers.AF.A += (uint8_t) (reg2 + this->registers.get_flag(FLAG_C));
    this->registers.check_if_result_zero(*reg1);
    *cycles--;
    this->registers.registers.PC++;
}
void CPU::ADD_1B_2C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_INC(*reg1, reg2);
    this->registers.check_C_INC(*reg1, reg2);
    this->registers.registers.AF.A += reg2;
    this->registers.check_if_result_zero(*reg1);
    *cycles-=2;
    this->registers.registers.PC++;
}
void CPU::ADC_1B_2C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_INC(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.check_C_INC(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.registers.AF.A += (uint8_t) (reg2 + this->registers.get_flag(FLAG_C));
    this->registers.check_if_result_zero(*reg1);
    *cycles-=2;
    this->registers.registers.PC++;
}
