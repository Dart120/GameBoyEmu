#include "cpu.h"


void CPU::POP(uint16_t* reg, uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
    low = this->registers->dont_touch_F(reg, low);
    this->registers->registers.SP++;
    uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;
    *reg = (*reg) & 0xFF00;
    *reg = (*reg) | low;
    this->process_4t_cycles();
    *reg = (*reg) & 0x00FF;
    *reg = (*reg) | (high << 8);
    this->process_4t_cycles();
    *cycles += 3;
    this->registers->registers.PC++;
}

void CPU::PUSH(uint16_t reg, uint16_t *cycles){
    this->process_4t_cycles();
    this->process_4t_cycles();
    this->registers->registers.SP--;
    uint8_t high = reg >> 8;
    this->memory.write_8_bit(this->registers->registers.SP--,high);
    this->process_4t_cycles();
    uint8_t low = reg & 0xFF;
    this->memory.write_8_bit(this->registers->registers.SP,low);
    this->process_4t_cycles();
    *cycles += 4;
    this->registers->registers.PC++;
}