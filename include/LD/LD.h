#ifndef LD_H
#define LD_H
#include<iostream>
// #define FMT_HEADER_ONLY
template <class F>
struct LD_instructions{
    void LD_1B_2C(u_int16_t* address, u_int8_t* value);
    void LD_1B_1C(u_int8_t* into, u_int8_t* load);
    void LD_2B_2C(u_int8_t* into, u_int8_t* immediate);
    void LD_3B_5C(u_int8_t* immediate, u_int16_t* SP);
    void increment_HL(u_int8_t* HL, F then);
};


#endif