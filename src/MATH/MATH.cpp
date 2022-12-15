#include "cpu.h"


void CPU::ADD_1B_1C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_ADD(*reg1, reg2);
    this->registers.check_C_8_ADD(*reg1, reg2);
    this->registers.registers.AF.A += reg2;
    this->registers.check_if_result_zero(*reg1);
    *cycles--;
    this->registers.registers.PC++;
}
void CPU::ADC_1B_1C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_ADD(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.check_C_8_ADD(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.registers.AF.A += (uint8_t) (reg2 + this->registers.get_flag(FLAG_C));
    this->registers.check_if_result_zero(*reg1);
    *cycles--;
    this->registers.registers.PC++;
}

void CPU::ADD_1B_2C_8Bit(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_ADD(*reg1, reg2);
    this->registers.check_C_8_ADD(*reg1, reg2);
    this->registers.registers.AF.A += reg2;
    this->registers.check_if_result_zero(*reg1);
    *cycles-=2;
    this->registers.registers.PC++;
}
void CPU::ADD_1B_2C_16Bit(uint16_t *reg1,uint16_t reg2, uint32_t *cycles){
    this->registers.clear_flag(FLAG_N);
    this->registers.check_C_15_INC(this -> registers.registers.HL_double,this->registers.registers.BC_double);
    this -> registers.registers.HL_double += this->registers.registers.BC_double;
    (*cycles) -= 2;
    (this->registers.registers.PC) += 1;
}
void CPU::ADC_1B_2C_8Bit(uint8_t *reg1,uint8_t reg2, uint32_t *cycles){
    this->registers.check_H_8_ADD(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.check_C_8_ADD(*reg1,(uint8_t)  (reg2 + this->registers.get_flag(FLAG_C)));
    this->registers.registers.AF.A += (uint8_t) (reg2 + this->registers.get_flag(FLAG_C));
    this->registers.check_if_result_zero(*reg1);
    *cycles-=2;
    this->registers.registers.PC++;
}
void CPU::SUB_1B_1C(uint8_t reg1, uint32_t *cycles){
    this->registers.check_H_8_SUB(this->registers.registers.AF.A, reg1);
    this->registers.check_C_8_SUB(this->registers.registers.AF.A, reg1);
    char result = this->registers.registers.AF.A - reg1;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    this->registers.set_flag(FLAG_N);
    *cycles-=1;
    this->registers.registers.PC++;
}
void CPU::SUB_1B_2C(uint16_t address, uint32_t *cycles){
    uint8_t value = this->memory.read_8_bit(address);
    this->registers.check_H_8_SUB(this->registers.registers.AF.A, value);
    this->registers.check_C_8_SUB(this->registers.registers.AF.A, value);
    char result = this->registers.registers.AF.A - value;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    this->registers.set_flag(FLAG_N);
    *cycles-=2;
    this->registers.registers.PC++;
}

void CPU::SBC_1B_1C(uint8_t reg1, uint32_t *cycles){
    uint8_t C = this->registers.get_flag(FLAG_C);
    this->registers.check_H_8_SUB(this->registers.registers.AF.A,(uint8_t) (reg1 + C));
    this->registers.check_C_8_SUB(this->registers.registers.AF.A,(uint8_t) (reg1 + C));
    char result = this->registers.registers.AF.A - reg1 + C;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    this->registers.set_flag(FLAG_N);
    *cycles-=1;
    this->registers.registers.PC++;
}
void CPU::SBC_1B_2C(uint16_t address, uint32_t *cycles){
    uint8_t C = this->registers.get_flag(FLAG_C);
    uint8_t value = this->memory.read_8_bit(address) + C;
    this->registers.check_H_8_SUB(this->registers.registers.AF.A, value);
    this->registers.check_C_8_SUB(this->registers.registers.AF.A, value);
    char result = this->registers.registers.AF.A - value;
    this->registers.registers.AF.A = result;
    this->registers.check_if_result_zero(result);
    this->registers.set_flag(FLAG_N);
    *cycles-=2;
    this->registers.registers.PC++;
}
