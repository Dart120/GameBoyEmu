#include "cpu.h"
#include <spdlog/spdlog.h>
void CPU::JUMP_ON_COND_s8(bool cond, uint32_t* cycles){
    if (cond){
        (this->registers->registers.PC) += this->memory.read_8_bit(this->registers->registers.PC + 1);
        (*cycles) += 3;
    } else {
        (this->registers->registers.PC)++;
        (*cycles) += 2;
    }
}
void CPU::JUMP_UNCOND_s8(uint32_t* cycles){
    this->registers->registers.PC += this -> memory.read_8_bit(this->registers->registers.PC + 1);
    (*cycles) += 3;  
}
void CPU::JUMP_UNCOND_REG(uint16_t reg, uint32_t* cycles){
    this->registers->registers.PC = reg;
}


void CPU::JUMP_ON_COND_a16(bool cond, uint32_t* cycles){
    if (cond){
        (this->registers->registers.PC) = this->memory.read_16_bit(this->registers->registers.PC + 1);
        (*cycles) += 4;
    } else {
        (this->registers->registers.PC)++;
        (*cycles) += 3;
    }
}
void CPU::JUMP_UNCOND_a16(uint32_t* cycles){
    spdlog::info("jump by {:X}",this->memory.read_16_bit(this->registers->registers.PC + 1));
    this->registers->registers.PC = this->memory.read_16_bit(this->registers->registers.PC + 1);
    (*cycles) += 3;  
}