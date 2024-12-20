#include "Registers.h"
#include "cpu.h"
#include "memory.h"
#include <spdlog/spdlog.h>
#include<iostream>



void CPU::INC_8_BIT(uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    // spdlog::info("F: {:B}",this->registers->registers.AF.F);
    this->registers->check_H_8_ADD(*reg,(uint8_t) 1);
    // spdlog::info("F: {:B}",this->registers->registers.AF.F);
    char result = ++(*reg);
    // spdlog::info("result  {:X}",result);
    // spdlog::info("F: {:B}",this->registers->registers.AF.F);
    this->registers->check_if_result_zero(result);
    // spdlog::info("F: {:B}",this->registers->registers.AF.F);
    this->registers->clear_flag(FLAG_N);
    // spdlog::info("F: {:B}",this->registers->registers.AF.F);
    this->registers->registers.PC++;
    // (*cycles)++;
}
void CPU::DEC_8_BIT(uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->check_H_8_SUB(*reg,(uint8_t) 1);
    char result = --*reg;
    this->registers->set_flag(FLAG_N);
    this->registers->check_if_result_zero(result);
    
    this->registers->registers.PC++;
    // (*cycles)++;
}
void CPU::INC_16_BIT(uint16_t* reg, uint16_t *cycles){
    u_int16_t result = (*reg) + 1;
    u_int16_t high = result & 0xFF00;
    u_int16_t low = result & 0x00FF;
    *reg = (*reg) & 0xFF00;
    *reg = (*reg) | low;
    this->process_4t_cycles();
    *reg = (*reg) & 0x00FF;
    *reg = (*reg) | (high);
    this->process_4t_cycles();
    this->registers->registers.PC++;
    // (*cycles) += 2;
}
void CPU::DEC_16_BIT(uint16_t* reg, uint16_t *cycles){
    u_int16_t result = (*reg) - 1;
    u_int16_t high = result & 0xFF00;
    u_int16_t low = result & 0x00FF;
    *reg = (*reg) & 0xFF00;
    *reg = (*reg) | low;
    this->process_4t_cycles();
    *reg = (*reg) & 0x00FF;
    *reg = (*reg) | (high);
    this->process_4t_cycles();
    this->registers->registers.PC++;
    // (*cycles) += 2;
                
}
void CPU::DEC_FROM_MEMORY(uint16_t address, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->check_H_8_SUB(this->memory.read_8_bit(this->registers->registers.HL_double),(uint8_t) 1);
    this->process_4t_cycles();
    char result = this->memory.read_8_bit(this->registers->registers.HL_double) - 1;
    this->memory.write_8_bit(this->registers->registers.HL_double,result);
    this->process_4t_cycles();
    this->registers->check_if_result_zero(result);
    this->registers->set_flag(FLAG_N);
    // (*cycles) += 3;
this->registers->registers.PC++;
}
void CPU::INC_FROM_MEMORY(uint16_t address, uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->check_H_8_ADD(this->memory.read_8_bit(this->registers->registers.HL_double),(uint8_t) 1);
    char result = this->memory.read_8_bit(this->registers->registers.HL_double) + 1;
    this->process_4t_cycles();
    this->registers->check_if_result_zero(result);
    this->registers->clear_flag(FLAG_N);
    // (*cycles) += 3;
    this->memory.write_8_bit(this->registers->registers.HL_double,result);
    this->process_4t_cycles();
    this->registers->registers.PC++;
}
// Not sure what these were for
// void CPU::INC_ADD(uint16_t address, uint16_t *cycles){
//      this->registers->check_H_8_INC(this->memory.read_8_bit(address),(uint8_t) 1);
//     char result = (this->memory.read_8_bit(address)) + 1;
//     memory->write_8_bit(address,result);
//     this->registers->check_if_result_zero(result);
//     this->registers->clear_flag(FLAG_N);
//     (*system_status->PC_value)++;
//     system_status->cycles--;
              
// }
// void CPU::DEC_ADD(uint16_t address, uint16_t *cycles){
// char result = --memory->read_8_bit(address);
// memory->write_8_bit(address,result);
//                 this->registers->set_flag(FLAG_N);
//                 this->registers->check_if_result_zero(result);
//                 this->registers->check_H_8_SUB(memory->read_8_bit(address),(uint8_t) 1);
//                (*system_status->PC_value)++;
//                system_status->cycles--;
// }

