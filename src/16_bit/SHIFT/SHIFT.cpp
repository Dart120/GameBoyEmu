#include "cpu.h"


void CPU::SLA_2B_2C(uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t last_bit = *reg >> 7;
    *reg = (*reg << 1);
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_H);
    this->registers->check_if_result_zero(*reg);
    last_bit ? this->registers->set_flag(FLAG_C) : this->registers->clear_flag(FLAG_C);
    this->registers->registers.PC += 2;
    // *cycles += 2;
}
void CPU::SLA_2B_4C(uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();

    uint8_t last_bit = this->memory.read_8_bit(this->registers->registers.HL_double) >> 7;
    uint8_t result = (this->memory.read_8_bit(this->registers->registers.HL_double) << 1);
    this->registers->check_if_result_zero(result);
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_H);
    last_bit ? this->registers->set_flag(FLAG_C) : this->registers->clear_flag(FLAG_C);
    this->memory.write_8_bit(this->registers->registers.HL_double, result);
    this->registers->registers.PC += 2;
    // *cycles += 4;
}
void CPU::SRA_2B_2C(uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t first_bit = *reg & 1;
    bool msb = *reg >> 7;
    *reg = (*reg >> 1);
    if (msb) {
        *reg |= (1<<7);
    }
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_H);
    this->registers->check_if_result_zero(*reg);
    first_bit ? this->registers->set_flag(FLAG_C) : this->registers->clear_flag(FLAG_C);
    this->registers->registers.PC += 2;
    // *cycles += 2;
}
void CPU::SRA_2B_4C(uint16_t *cycles){
    this->process_4t_cycles();    
    this->process_4t_cycles();    
    this->process_4t_cycles();    
    this->process_4t_cycles();    

    uint8_t first_bit = this->memory.read_8_bit(this->registers->registers.HL_double) & 1;
    bool msb = this->memory.read_8_bit(this->registers->registers.HL_double) >> 7;
    uint8_t result = (this->memory.read_8_bit(this->registers->registers.HL_double) >> 1);
    if (msb) {
        result |= (1<<7);
    }
    this->registers->check_if_result_zero(result);
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_H);
    first_bit ? this->registers->set_flag(FLAG_C) : this->registers->clear_flag(FLAG_C);
    this->memory.write_8_bit(this->registers->registers.HL_double, result);
    this->registers->registers.PC += 2;
    // *cycles += 4;
}

void CPU::SRL_2B_2C(uint8_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t first_bit = *reg & 1;
    *reg = (*reg >> 1);
    this->registers->check_if_result_zero(*reg);
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_H);
    first_bit ? this->registers->set_flag(FLAG_C) : this->registers->clear_flag(FLAG_C);
    this->registers->registers.PC += 2;
    // *cycles += 2;
}
void CPU::SRL_2B_4C(uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->process_4t_cycles();
    uint8_t first_bit = this->memory.read_8_bit(this->registers->registers.HL_double) & 1;
    uint8_t result = (this->memory.read_8_bit(this->registers->registers.HL_double) >> 1);
    this->registers->check_if_result_zero(result);
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_H);
    this->memory.write_8_bit(this->registers->registers.HL_double, result);
    first_bit ? this->registers->set_flag(FLAG_C) : this->registers->clear_flag(FLAG_C);
    this->registers->registers.PC += 2;
    // *cycles += 4;
}
