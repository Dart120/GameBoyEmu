#include "cpu.h"


void CPU::CALL_COND(uint8_t COND, uint32_t *cycles){
    if (COND){
        uint8_t low = this->memory.read_8_bit(this->registers.registers.PC +3);
        uint8_t high = this->memory.read_8_bit(this->registers.registers.PC +4);
        this->registers.registers.SP++;
        this->memory.write_8_bit(this->registers.registers.SP,low);
        this->registers.registers.SP++;
        this->memory.write_8_bit(this->registers.registers.SP,high);
        this->registers.registers.PC = this->registers.registers.PC + 2;
        
       
        *cycles -= 6;
       
    } else {
        this->registers.registers.PC += 3;
        *cycles -= 3;
    }
}
