#include "cpu.h"


void CPU::POP(uint16_t* reg, uint32_t *cycles){
    
    uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);

    low = this->registers->dont_touch_F(reg, low);
    this->registers->registers.SP++;
    uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;

    uint16_t result = low + uint16_t (high << 8);
    *reg = result;
    *cycles -= 3;
    this->registers->registers.PC++;
}
// TODO
void CPU::PUSH(uint16_t reg, uint32_t *cycles){
    this->registers->registers.SP--;
    uint8_t high = reg >> 8;
    this->memory.write_8_bit(this->registers->registers.SP--,high);
    uint8_t low = reg & 0xFF;
    this->memory.write_8_bit(this->registers->registers.SP,low);
    *cycles -= 4;
    this->registers->registers.PC++;
}