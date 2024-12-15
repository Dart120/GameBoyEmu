#include "cpu.h"


void CPU::RET_COND(uint8_t COND, uint16_t *cycles){
    this->process_4t_cycles();
    
    if (COND){
        this->process_4t_cycles();
        this->process_4t_cycles();
        uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
        this->registers->registers.SP++;
        this->process_4t_cycles();
        uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
        this->registers->registers.SP++;
        this->process_4t_cycles();
        uint16_t result = low + (uint16_t) (high << 8);
        this->registers->registers.PC = result;
      
        // *cycles += 5;
        
    } else {
        this->process_4t_cycles();
        this->registers->registers.PC++;
        // *cycles += 2;
    }
}
void CPU::RET_UNCOND(uint16_t *cycles){
    this->process_4t_cycles();
    uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;
    this->process_4t_cycles();
    uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
    this->process_4t_cycles();
    uint16_t result = low + (uint16_t) (high << 8);
    // spdlog::info("ret high: {:X}, low: {:X}",high,low);
    // spdlog::info("Fool: {:X}",result);
  
    this->registers->registers.PC = result;
    this->process_4t_cycles();
    // *cycles += 4;
    this->registers->registers.SP++;
}
void CPU::RETI(uint16_t *cycles){
    this->process_4t_cycles();
    this->registers->IME = true;
    uint8_t low = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;
    this->process_4t_cycles();
    uint8_t high = this->memory.read_8_bit(this->registers->registers.SP);
    this->registers->registers.SP++;
    this->process_4t_cycles();
    uint16_t result = low + (uint16_t) (high << 8);
    this->registers->registers.PC = result;
    this->process_4t_cycles();
    // *cycles += 4;
    
}
