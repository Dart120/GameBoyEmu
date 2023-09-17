#include "cpu.h"


void CPU::RST_COND(uint8_t COND, uint16_t *cycles){
    if (COND){
        uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
        this->registers->registers.SP++;
        uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
        uint16_t result = low + uint16_t (high << 8);
        this->registers->registers.PC = result;
        *cycles += 5;
        this->registers->registers.SP++;
    } else {
        *cycles += 2;
        this->registers->registers.PC++;
    }
}
void CPU::RST_UNCOND(uint8_t number,uint16_t *cycles){
    uint16_t byte_address = number * 8;
    uint16_t curr_pc = this->registers->registers.PC + 1;
    uint8_t high = (curr_pc >> 8) & 0xFF;
    uint8_t low = curr_pc & 0xFF;
    this->memory.write_8_bit(--this->registers->registers.SP,high);
    this->memory.write_8_bit(--this->registers->registers.SP,low);
    // uint16_t new_pc = this->memory.read_16_bit(byte_address);
    this->registers->registers.PC = byte_address;
    *cycles += 4;
}