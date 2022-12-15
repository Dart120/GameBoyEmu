#include "cpu.h"

void CPU::JUMP_ON_COND(bool cond, uint32_t* cycles){
    if (cond){
        (this->registers.registers.PC) += this->memory.read_8_bit(this->registers.registers.PC + 1);
        (*cycles) += 3;
    } else {
        (this->registers.registers.PC)++;
        (*cycles) += 2;
    }
}
void CPU::JUMP_UNCOND(uint32_t* cycles){
    this->registers.registers.PC += this -> memory.read_8_bit(this->registers.registers.PC + 1);
    (*cycles) += 3;  

}