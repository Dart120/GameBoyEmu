
#ifndef CPU_H
#define CPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include <vector>
struct system_status_struct{
    u_int32_t cycles;
    u_int16_t *PC_value;
};
enum register_index {AF,BC,DE,HL,SP,PC};
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
    struct system_status_struct system_status;
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
    int set_flag(int index);
    bool get_flag(int index);
    int clear_flag(int index);
    template <typename T> void check_if_result_zero (T result);
    template <typename T> void check_H_8_INC(T a, T b);
    template <typename T> void check_C_INC(T a, T b);
    template <typename T> void check_H_11_INC(T a, T b);
    template <typename T> void check_C_15_INC(T a, T b);
    template <typename T> void check_H_8_DEC(T a, T b);
    std::vector<int> num_to_list(int num);

};
#endif