#include "cpu.h"


void CPU::CALL_COND(uint8_t COND, uint16_t *cycles){
    if (COND){
        uint8_t low = ((this->registers->registers.PC + 3) & 0xFF);
        uint8_t high = ((this->registers->registers.PC + 3) & 0xFF00) >> 8;
        uint16_t new_PC = this->memory.read_16_bit(this->registers->registers.PC + 1);
        this->registers->registers.SP--;
        this->memory.write_8_bit(this->registers->registers.SP,high);
        this->registers->registers.SP--;
        this->memory.write_8_bit(this->registers->registers.SP,low);
        this->registers->registers.PC = new_PC;
        // spdlog::info("call high: {:X}, low: {:X}",high,low);
       
        *cycles += 6;
       
    } else {
        this->registers->registers.PC += 3;
        *cycles += 3;
    }
}
void CPU::CALL_UNCOND(uint16_t *cycles){
    uint8_t low = ((this->registers->registers.PC + 3) & 0xFF);
    uint8_t high = ((this->registers->registers.PC + 3) & 0xFF00) >> 8;
    // spdlog::info("call high: {:X}, low: {:X}",high,low);
    uint16_t new_PC = this->memory.read_16_bit(this->registers->registers.PC + 1);
    this->registers->registers.SP--;
    this->memory.write_8_bit(this->registers->registers.SP,high);
    this->registers->registers.SP--;
    this->memory.write_8_bit(this->registers->registers.SP,low);
    this->registers->registers.PC = new_PC;
    *cycles += 6;
}

