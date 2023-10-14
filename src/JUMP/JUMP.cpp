#include "cpu.h"
#include <spdlog/spdlog.h>
void CPU::JUMP_ON_COND_s8(bool cond, uint16_t *cycles){
    this->process_4t_cycles();

    if (cond){
        this->process_4t_cycles();
        (this->registers->registers.PC) += this->unsigned_8_to_signed_8(this->memory.read_8_bit(this->registers->registers.PC + 1));
        this->process_4t_cycles();
        (*cycles) += 3;
    } else {
        this->process_4t_cycles();
        (*cycles) += 2;
    }
    this->registers->registers.PC += 2;
    
}
void CPU::JUMP_UNCOND_s8(uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->registers->registers.PC += this->unsigned_8_to_signed_8(this -> memory.read_8_bit(this->registers->registers.PC + 1));
    this->process_4t_cycles();
    (*cycles) += 3;  
    this->registers->registers.PC += 2;
}
void CPU::JUMP_UNCOND_REG(uint16_t reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->registers.PC = reg;
    // this->registers->registers.PC += 2;
}


void CPU::JUMP_ON_COND_a16(bool cond, uint16_t *cycles){
    this->process_4t_cycles();
    if (cond){
        this->process_4t_cycles();
        this->process_4t_cycles();
        (this->registers->registers.PC) = this->memory.read_16_bit(this->registers->registers.PC + 1);
        this->process_4t_cycles();
        (*cycles) += 4;
    } else {
        this->process_4t_cycles();
        this->process_4t_cycles();
        (this->registers->registers.PC) += 3;
        (*cycles) += 3;
    }
}
void CPU::JUMP_UNCOND_a16(uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->registers->registers.PC = this->memory.read_16_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    (*cycles) += 4;  
}