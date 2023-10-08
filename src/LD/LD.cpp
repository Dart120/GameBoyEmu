#include "cpu.h"
#include "memory.h"
#include "Registers.h"
#include<iostream>
#include <spdlog/spdlog.h>
void CPU::LD_1B_2C_REG_TO_MEM(uint16_t address, uint8_t reg, uint16_t *cycles){
    this->process_4t_cycles();
     this->memory.write_8_bit(address, reg);
     this->process_4t_cycles();
    this->registers->registers.PC++;
    (*cycles) += 2;       
}

void CPU::LD_1B_2C_MEM_TO_REG(uint16_t address, uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    *reg = this->memory.read_8_bit(address);
    this->process_4t_cycles();
    this->registers->registers.PC++;
    (*cycles) += 2;    
}
void CPU::LD_1B_2C_REG_TO_REG(uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->registers.SP = this->registers->registers.HL_double;
    this->process_4t_cycles();
    this->registers->registers.PC++;
    (*cycles) += 2;    
}

void CPU::LD_1B_1C(uint8_t* into, uint8_t load, uint16_t *cycles){
    this->process_4t_cycles();
    *into = load;
    this->registers->registers.PC++;
    (*cycles) += 1;
}
// void CPU::LD_3B_4C(uint8_t* into, uint8_t load, uint16_t *cycles){
//     this->memory.write_8_bit( this->memory.read_16_bit(this->registers->registers.PC + 1),this->registers->registers.AF.A);
//     this->registers->registers.PC += 3;
//     (*cycles) += 4;
// }

void CPU::LD_3B_4C_MEM_TO_REG(uint8_t* reg, uint16_t *cycles){
    // spdlog::info("address {:X}", this->memory.read_16_bit(this->registers->registers.PC + 1));
    // spdlog::info("address reversed {:X}", swapped);
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    *reg = this->memory.read_8_bit(this->memory.read_16_bit(this->registers->registers.PC + 1));
    // spdlog::info("fetched {:X}", *reg);
    // spdlog::info("alt {:X}", this->memory.read_8_bit(swapped));
    this->registers->registers.PC += 3;
    (*cycles) += 4;
}
void CPU::LD_3B_4C_REG_TO_MEM(uint8_t reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->memory.write_8_bit(this->memory.read_16_bit(this->registers->registers.PC + 1),reg);
    this->registers->registers.PC += 3;
    (*cycles) += 4;
}

void CPU::LD_2B_2C(uint8_t* into, uint16_t *cycles){
        this->process_4t_cycles();
        *into = this->memory.read_8_bit(this->registers->registers.PC + 1);
        this->process_4t_cycles();
        this->registers->registers.PC += 2;
        (*cycles) += 2;
}

void CPU::LD_2B_3C_ACC_TO_MEM(uint16_t *cycles){
    this->process_4t_cycles();
    uint16_t address = 0xFF00 + this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    this->memory.write_8_bit(address,this->registers->registers.AF.A);
    this->process_4t_cycles();
    this->registers->registers.PC += 2;
    (*cycles) += 3;
}

void CPU::LD_2B_3C(uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_Z);
    int8_t s8 = this->unsigned_8_to_signed_8(this->memory.read_8_bit(this->registers->registers.PC + 1));
    this->process_4t_cycles();
    u_int16_t old_sp = this->registers->registers.SP;
    // u_int16_t new_sp = this->registers->registers.SP + s8;
    // if ((((old_sp & 0xff) + (((int16_t) s8) & 0xff)) & 0x100)){
    //     this->registers->set_flag(FLAG_C);
    // } else {
    //     this->registers->clear_flag(FLAG_C);
    // }
    this->registers->check_C_8_ADD(old_sp,(int16_t) s8);
    this->registers->check_H_8_ADD((uint8_t) old_sp, s8);
    this->registers->registers.HL_double = this->registers->registers.SP + (int16_t) s8;
    this->process_4t_cycles();
    (*cycles) += 3;
    (this->registers->registers.PC) += 2;
}
void CPU::LD_2B_3C_HL(uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t d8 = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    this->memory.write_8_bit(this->registers->registers.HL_double,d8);
    this->process_4t_cycles();
    (*cycles) += 2;
    (this->registers->registers.PC) += 3;
}
void CPU::LD_2B_3C_MEM_TO_ACC(uint16_t *cycles){
    this->process_4t_cycles();
    uint16_t address = 0xFF00 + this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    this->registers->registers.AF.A =  this->memory.read_8_bit(address);
    this->process_4t_cycles();
    this->registers->registers.PC += 2;
    (*cycles) += 3;
}

void CPU::LD_3B_5C(uint16_t* SP, uint16_t *cycles){
    this->process_4t_cycles();
    u_int8_t low = this->memory.read_8_bit(this->registers->registers.PC + 1);
    this->process_4t_cycles();
    u_int8_t high = this->memory.read_8_bit(this->registers->registers.PC + 2);
    this->process_4t_cycles();
    this->memory.write_16_bit(this->memory.read_16_bit(this->registers->registers.PC + 1),*SP);
    *SP = (*SP) & 0xFF00;
    *SP = (*SP) | low;
    this->process_4t_cycles();
    *SP = (*SP) & 0x00FF;
    *SP = (*SP) | (high << 8);
    this->process_4t_cycles();
    (*cycles) += 5;
    this->registers->registers.PC += 3;
}

void CPU::LD_3B_3C(uint16_t* into, uint16_t *cycles){
    this->process_4t_cycles();
    u_int8_t low = this->memory.read_8_bit(this->registers->registers.PC + 1);
    u_int8_t high = this->memory.read_8_bit(this->registers->registers.PC + 2);
    *into = (*into) & 0xFF00;
    *into = (*into) | low;
    this->process_4t_cycles();
    *into = (*into) & 0x00FF;
    *into = (*into) | (high << 8);
    this->process_4t_cycles();
    this->registers->registers.PC += 3;
    (*cycles) += 3;
}

void CPU::increment_HL(uint16_t* HL){
    (*HL)++;
}

void CPU::decrement_HL(uint16_t* HL){
    (*HL)--;
}
