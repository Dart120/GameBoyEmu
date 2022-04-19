#include<iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "cpu.h"

    u_int16_t CPU::read_double_register(register_index index){
        double_register d_r;
        switch (index)
        {
        case AF:
            d_r = this->regs.AF;
            break;
        case BC:
            d_r = this->regs.BC;
            break;
        case DE:
            d_r = this->regs.DE;
            break;
        case HL:
            d_r = this->regs.HL;
            break;
        case SP:
            d_r = this->regs.SP;
            break;
        case PC:
            d_r = this->regs.PC;
            break;
        
        default:
            fmt::print("Invalid Register");
            return 0;
            break;
        }
        u_int16_t number = d_r.high << 8 | d_r.low;
        return number;
        
    }
    //  CPU::read_double_register(register_index index){
 
