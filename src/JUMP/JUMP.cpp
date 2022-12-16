#include "cpu.h"

void CPU::JUMP_ON_COND_s8(bool cond, uint32_t* cycles){
    if (cond){
        (this->registers.registers.PC) += this->memory.read_8_bit(this->registers.registers.PC + 1);
        (*cycles) += 3;
    } else {
        (this->registers.registers.PC)++;
        (*cycles) += 2;
    }
}
void CPU::JUMP_UNCOND_s8(uint32_t* cycles){
    this->registers.registers.PC += this -> memory.read_8_bit(this->registers.registers.PC + 1);
    (*cycles) += 3;  
}


void CPU::JUMP_ON_COND_s16(bool cond, uint32_t* cycles){
    if (cond){
        (this->registers.registers.PC) = this->memory.read_16_bit(this->registers.registers.PC + 1);
        (*cycles) += 4;
    } else {
        (this->registers.registers.PC)++;
        (*cycles) += 3;
    }
}
void CPU::JUMP_UNCOND_s16(uint32_t* cycles){
    this->registers.registers.PC += this -> memory.read_16_bit(this->registers.registers.PC + 1);
    (*cycles) += 3;  
}