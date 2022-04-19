#pragma once
#ifndef CPU_H
#define CPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
// #include <fmt/core.h> 
struct double_register{
    u_int8_t high;
    u_int8_t low;
};
enum register_index {AF,BC,DE,HL,SP,PC};
class CPU
{
    public:
    CPU();
    // Access specifier
    private:
 
    // Data Members
    struct reg{
        double_register AF;
        double_register BC;
        double_register DE;
        double_register HL;
        double_register SP;
        double_register PC;
    } regs;
    // Member Functions()
    u_int16_t read_double_register(register_index index);
 
};
#endif