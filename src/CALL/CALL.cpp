#include "cpu.h"


void CPU::CALL_COND(uint8_t COND, uint32_t *cycles){
    if (COND){
        uint8_t low = this->memory.read_8_bit(this->registers.registers.PC +3);
        uint8_t high = this->memory.read_8_bit(this->registers.registers.PC +4);
        uint16_t new_PC = this->read_16_bit(this->registers.registers.PC + 1);
        this->registers.registers.SP++;
        this->memory.write_8_bit(this->registers.registers.SP,low);
        this->registers.registers.SP++;
        this->memory.write_8_bit(this->registers.registers.SP,high);
        this->registers.registers.PC = new_PC;
        
       
        *cycles -= 6;
       
    } else {
        this->registers.registers.PC += 3;
        *cycles -= 3;
    }
}
