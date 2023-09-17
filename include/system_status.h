#ifndef SS_H
#define SS_H
#include<iostream>
// #define FMT_HEADER_ONLY
struct system_status_struct{
    uint16_t m_cycles;
    uint16_t t_cycles;
    uint16_t *PC_value;
};
#endif