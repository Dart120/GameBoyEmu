#include "cpu.h"
#include "memory.h"
#include "Registers.h"
#include<iostream>
void CPU::LD_1B_2C_REG_TO_MEM(uint16_t address, uint8_t reg, uint32_t *cycles){
     this->memory.write_8_bit(address, reg);
    this->registers.registers.PC++;
    (*cycles) -= 2;

               
}

void CPU::LD_1B_2C_MEM_TO_REG(uint16_t address, uint8_t* reg, uint32_t *cycles){
     *(reg) = this->memory.read_8_bit(address);
    this->registers.registers.PC++;
    (*cycles) -= 2;
               
}



void CPU::LD_1B_1C(uint8_t* into, uint8_t load, uint32_t *cycles){
    *into = load;
    this->registers.registers.PC++;
    (*cycles) -= 2;
}

void CPU::LD_2B_2C(uint8_t* into, uint32_t *cycles){
        *into = this->memory.read_8_bit(this->registers.registers.PC + 1);
        this->registers.registers.PC += 2;
        (*cycles) -= 2;
}

void CPU::LD_2B_3C(uint16_t address, uint32_t *cycles){
    
        this->memory.write_8_bit(address,this->memory.read_8_bit(this->registers.registers.PC + 1));
       this->registers.registers.PC += 2;
        (*cycles) -= 3;
}

void CPU::LD_3B_5C(uint16_t* SP, uint32_t *cycles){
    this->memory.write_16_bit(this->registers.registers.PC + 1,*SP);
    (*cycles) -= 5;
    this->registers.registers.PC += 3;

}

void CPU::LD_3B_3C(uint16_t* into, uint32_t *cycles){
    *into = this->memory.read_16_bit(this->registers.registers.PC + 1);
    this->registers.registers.PC += 3;
        (*cycles) -= 3;

}

void CPU::increment_HL(uint16_t* HL){
    *(HL)++;
}

void CPU::decrement_HL(uint16_t* HL){
    *(HL)--;
}
