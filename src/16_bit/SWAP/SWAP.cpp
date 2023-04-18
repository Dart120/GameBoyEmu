#include "cpu.h"

void CPU::SWAP_2B_2C(uint8_t* reg, uint32_t *cycles){
    uint8_t high = *reg >> 4;
    *reg = (*reg << 4) + high;
    this->registers->check_if_result_zero(*reg);
    this->registers->registers.PC += 2;
    *cycles -= 2;
}
void CPU::SWAP_2B_4C(uint32_t *cycles){
    uint8_t high = this->memory.read_8_bit(this->registers->registers.HL_double) >> 4;
    uint8_t result = (this->memory.read_8_bit(this->registers->registers.HL_double) << 4) + high;
    this->registers->check_if_result_zero(result);
    this->memory.write_8_bit(this->registers->registers.HL_double, result);
    this->registers->registers.PC += 2;
    *cycles -= 4;
}