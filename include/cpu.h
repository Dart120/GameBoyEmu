
#ifndef CPU_H
#define CPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "Registers/Registers.h"
#include <vector>
struct system_status_struct{
    uint32_t cycles;
    uint16_t *PC_value;
};

class CPU
{
    
    public:
    CPU(Memory memory,Registers register);
    uint8_t read_8_bit(uint16_t address);
    int write_8_bit(uint16_t address, uint8_t data);
    uint16_t read_16_bit(uint16_t address);
    int write_16_bit(uint16_t address, uint16_t data);
    void FDE();
    
    // Access specifier
    
    Memory memory;
    Registers registers;
    struct system_status_struct system_status;
    // Data Members

    // INCDEC
    void INC_8_BIT(uint8_t* reg, uint32_t *cycles);
    void DEC_8_BIT(uint8_t* reg, uint32_t *cycles);
    void INC_16_BIT(uint16_t* reg, uint32_t *cycles);
    void DEC_16_BIT(uint16_t* reg, uint32_t *cycles);
    void INC_ADD(uint16_t address, uint32_t *cycles);
    void DEC_ADD(uint16_t address, uint32_t *cycles);
    // LD
    void LD_1B_2C_REG_TO_MEM(uint16_t address, uint8_t reg, uint32_t *cycles);
    void LD_1B_2C_MEM_TO_REG(uint16_t address, uint8_t* reg, uint32_t *cycles);
    void LD_1B_1C(uint8_t* into, uint8_t load, uint32_t *cycles);

    void LD_2B_2C(uint8_t* into, uint32_t *cycles);
    void LD_2B_3C(uint16_t address, uint32_t *cycles);
    void LD_3B_5C(uint16_t* SP, uint32_t *cycles);
    void LD_3B_3C(uint16_t* into, uint32_t *cycles);
    void increment_HL(uint16_t* HL);

    void decrement_HL(uint16_t* HL);
      

    // Member Functions()
    void ADD_1B_2C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles);
    void ADD_1B_1C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles);
    void ADC_1B_2C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles);
    void ADC_1B_1C(uint8_t *reg1,uint8_t reg2, uint32_t *cycles);
    

};
#endif