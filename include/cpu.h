
#ifndef CPU_H
#define CPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
struct double_register{
    u_int8_t high;
    u_int8_t low;
};
enum register_index {AF,BC,DE,HL,SP,PC};
enum flag_index {U0,U1,U2,U3,c,h,n,z};
class CPU
{
    
    public:
    CPU(Memory memory);
    u_int8_t read_8_bit(u_int16_t address);
    int write_8_bit(u_int16_t address, u_int8_t data);
    u_int16_t read_16_bit(u_int16_t address);
    int write_16_bit(u_int16_t address, u_int16_t data);
    void FDE();
    int set_registers(u_int16_t  num);
    // Access specifier
    private:
    Memory memory;

    // Data Members
    struct registers{
        union{
            struct {
                u_int8_t A;
                u_int8_t F;
            } AF;
            u_int16_t AF_double;
        };
        union{
            struct {
                u_int8_t B;
                u_int8_t C;
            } BC;
            u_int16_t BC_double;
        };
        union{
            struct {
                u_int8_t D;
                u_int8_t E;
            } DE;
            u_int16_t DE_double;
        };
        union{
            struct {
                u_int8_t H;
                u_int8_t L;
            } HL;
            u_int16_t HL_double;
        };
        u_int16_t SP;
        u_int16_t PC;
    } registers;
    // Member Functions()
    u_int16_t read_double_register(register_index index);
    int set_flag(flag_index index);
    bool get_flag(flag_index index);
    
};
#endif