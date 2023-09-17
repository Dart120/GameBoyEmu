#include "cpu.h"
#include "memory.h"
#include "Registers.h"
#include<iostream>
#include <spdlog/spdlog.h>
void CPU::RRA(uint16_t *cycles){
    uint8_t first_bit = this -> registers->registers.AF.A & 1;
    // bool p_c = this->registers->get_flag(FLAG_C);
    this -> registers->registers.AF.A = this -> registers->registers.AF.A >> 1;
    if(this->registers->get_flag(FLAG_C)){
        this -> registers->registers.AF.A |= (1 << 7);
    }
    if (first_bit){
        this->registers->set_flag(FLAG_C);
    } else {
        this->registers->clear_flag(FLAG_C);
    }
    this->registers->clear_flag(FLAG_H);
    this->registers->clear_flag(FLAG_N);
    this->registers->clear_flag(FLAG_Z);

    (this->registers->registers.PC) += 1;
    *cycles += 1;    
}

