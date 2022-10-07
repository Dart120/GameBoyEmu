#ifndef LD_H
#define LD_H
#include<iostream>
#include "cpu.h"
#include "memory.h"
// #define FMT_HEADER_ONLY

struct LD_instructions{

static void LD_1B_2C_REG_TO_MEM(u_int16_t address, u_int8_t reg, system_status_struct* system_status, Memory* memory);
static void LD_1B_2C_MEM_TO_REG(u_int16_t address, u_int8_t* reg, system_status_struct* system_status, Memory* memory);
static void LD_1B_1C(u_int8_t* into, u_int8_t load, system_status_struct* system_status);

static void LD_2B_2C(u_int8_t* into, system_status_struct* system_status, Memory* memory);
static void LD_2B_3C(u_int16_t address, system_status_struct* system_status, Memory* memory);
static void LD_3B_5C(u_int16_t* SP,system_status_struct* system_status, Memory* memory);
static void LD_3B_3C(u_int16_t* into, system_status_struct* system_status, Memory* memory);
static void increment_HL(u_int16_t* HL);

static void decrement_HL(u_int16_t* HL);
};


#endif