#include "cpu.h"
#include <spdlog/spdlog.h>
void CPU::JUMP_ON_COND_s8(bool cond, uint32_t* cycles){
    //FIXME need to increment by two anyway becuase of the length of the instruction
    if (cond){
        (this->registers->registers.PC) += this->unsigned_8_to_signed_8(this->memory.read_8_bit(this->registers->registers.PC + 1));
        (*cycles) += 3;
    } else {
        (*cycles) += 2;
    }
    this->registers->registers.PC += 2;
    
}
void CPU::JUMP_UNCOND_s8(uint32_t* cycles){
    this->registers->registers.PC += this->unsigned_8_to_signed_8(this -> memory.read_8_bit(this->registers->registers.PC + 1));
    (*cycles) += 3;  
    this->registers->registers.PC += 2;
}
void CPU::JUMP_UNCOND_REG(uint16_t reg, uint32_t* cycles){
    this->registers->registers.PC = reg;
    // this->registers->registers.PC += 2;
}


void CPU::JUMP_ON_COND_a16(bool cond, uint32_t* cycles){
    if (cond){
        (this->registers->registers.PC) = this->memory.read_16_bit(this->registers->registers.PC + 1);
        (*cycles) += 4;
    } else {
        (this->registers->registers.PC) += 3;
        (*cycles) += 3;
    }
}
void CPU::JUMP_UNCOND_a16(uint32_t* cycles){
    this->registers->registers.PC = this->memory.read_16_bit(this->registers->registers.PC + 1);
    (*cycles) += 3;  
}