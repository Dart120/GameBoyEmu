#include "cpu.h"


void CPU::RST_COND(uint8_t COND, uint32_t *cycles){
    if (COND){
        uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
        this->registers->registers.SP++;
        uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
        uint16_t result = low + uint16_t (high << 8);
        this->registers->registers.PC = result;
        *cycles -= 5;
        this->registers->registers.SP++;
    } else {
        *cycles -= 2;
    }
}
void CPU::RST_UNCOND(uint8_t number,uint32_t *cycles){
    uint16_t byte_address = number * 8;
    uint16_t curr_pc = this->registers->registers.PC;
    uint8_t low = curr_pc & 0xFF;
    uint8_t high = curr_pc >> 8;
    this->memory.write_8_bit(--this->registers->registers.SP,high);
    this->memory.write_8_bit(--this->registers->registers.SP,low);
    uint8_t new_pc_low = this->memory.read_8_bit(byte_address);
    this->registers->registers.PC = (uint16_t) new_pc_low;
    *cycles -= 4;
}