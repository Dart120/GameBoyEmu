
#ifndef CPU_H
#define CPU_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "system_status.h"
#include "Registers/Registers.h"
#include <vector>
#include <map>
struct system_status_struct;

class CPU
{
    
    public:
    CPU(Memory& memory, system_status_struct& system, std::function<void()> process_4t_cycles);
    uint8_t read_8_bit(uint16_t address);
    int write_8_bit(uint16_t address, uint8_t data);
    uint16_t read_16_bit(uint16_t address);
    int write_16_bit(uint16_t address, uint16_t data);
    int8_t unsigned_8_to_signed_8(uint8_t n);
    void FDE();
    
    
    // Access specifier
    Memory memory;

    system_status_struct& system;
    std::function<void()> process_4t_cycles;
    
    Registers* registers;
 

    bool halted = false;
    // Data Members
    void handle_interrupts();


    // INCDEC
    void INC_8_BIT(uint8_t* reg, uint16_t *cycles);
    void DEC_8_BIT(uint8_t* reg, uint16_t *cycles);
    void INC_16_BIT(uint16_t* reg, uint16_t *cycles);
    void DEC_16_BIT(uint16_t* reg, uint16_t *cycles);
    void INC_FROM_MEMORY(uint16_t address, uint16_t *cycles);
    void DEC_FROM_MEMORY(uint16_t address, uint16_t *cycles);

    // void INC_ADD(uint16_t address, uint16_t *cycles);
    // void DEC_ADD(uint16_t address, uint16_t *cycles);
    // LD
    void LD_1B_2C_REG_TO_MEM(uint16_t address, uint8_t reg, uint16_t *cycles);
    void LD_1B_2C_MEM_TO_REG(uint16_t address, uint8_t* reg, uint16_t *cycles);
    void LD_1B_2C_REG_TO_REG(uint16_t *cycles);
    void LD_1B_1C(uint8_t* into, uint8_t load, uint16_t *cycles);
    void LD_3B_4C(uint8_t* into, uint8_t load, uint16_t *cycles);
    void LD_3B_4C_MEM_TO_REG(uint8_t* reg, uint16_t *cycles);
    void LD_3B_4C_REG_TO_MEM(uint8_t reg, uint16_t *cycles);
    void LD_2B_3C_HL(uint16_t *cycles);

    void LD_2B_2C(uint8_t* into, uint16_t *cycles);
    void LD_2B_3C_ACC_TO_MEM(uint16_t *cycles);
    void LD_2B_3C_MEM_TO_ACC(uint16_t *cycles);
    void LD_2B_3C(uint16_t *cycles);
    void LD_3B_5C(uint16_t* SP, uint16_t *cycles);
    void LD_3B_3C(uint16_t* into, uint16_t *cycles);
    void increment_HL(uint16_t* HL);

    void decrement_HL(uint16_t* HL);
      

    // MATH
    void ADD_1B_2C_8Bit(uint8_t reg1, uint16_t *cycles);
    void ADD_1B_2C_16Bit(uint16_t reg1, uint16_t *cycles);
    void ADD_2B_4C(uint16_t* reg1, uint16_t *cycles);
    void ADD_1B_1C(uint8_t reg1, uint16_t *cycles);
    void ADD_2B_2C(uint16_t *cycles);
    void ADC_1B_2C_8Bit(uint8_t reg1, uint16_t *cycles);
    void ADC_1B_2C(uint16_t *cycles);
    void ADC_1B_1C(uint8_t reg1, uint16_t *cycles);
    void ADC_2B_2C(uint16_t *cycles);
    void SUB_1B_1C(uint8_t reg1,uint16_t *cycles);
    void SUB_2B_2C(uint16_t *cycles);
    void SUB_1B_2C(uint16_t address, uint16_t *cycles);
    void SBC_1B_1C(uint8_t reg1,uint16_t *cycles);
    void SBC_1B_2C(uint16_t address, uint16_t *cycles);
    void SBC_2B_2C(uint16_t *cycles);


    // Jumps

    void JUMP_ON_COND_s8(bool cond,  uint16_t *cycles);
    void JUMP_UNCOND_s8(uint16_t *cycles);
    void JUMP_UNCOND_REG(uint16_t reg, uint16_t *cycles);
    void JUMP_ON_COND_a16(bool cond,  uint16_t *cycles);
    void JUMP_UNCOND_a16( uint16_t *cycles);
    
    // LOGIC
    void AND_1B_1C(uint8_t reg1,uint16_t *cycles);
    void AND_1B_2C(uint16_t address, uint16_t *cycles);
    void AND_2B_2C(uint16_t *cycles);
    void XOR_1B_1C(uint8_t reg1,uint16_t *cycles);
    void XOR_1B_2C(uint16_t address, uint16_t *cycles);
    void XOR_2B_2C(uint16_t *cycles);
    void OR_1B_1C(uint8_t reg1,uint16_t *cycles);
    void OR_1B_2C(uint16_t address, uint16_t *cycles);
    void OR_2B_2C(uint16_t *cycles);
    void CP_1B_1C(uint8_t reg1,uint16_t *cycles);
    void CP_2B_2C(uint16_t *cycles);
    void CP_1B_2C(uint16_t address, uint16_t *cycles);



    // POPPUSH
    void POP(uint16_t* reg ,  uint16_t *cycles);
    void PUSH(uint16_t reg , uint16_t *cycles);


    // Returns
    void RET_COND(uint8_t COND, uint16_t *cycles);
    void RET_UNCOND(uint16_t *cycles);
    void RETI(uint16_t *cycles);


    // CALL
    void CALL_COND(uint8_t COND, uint16_t *cycles);
    void CALL_UNCOND(uint16_t *cycles);

    // RST
    void RST_UNCOND(uint8_t number,uint16_t *cycles);
    // void RST_COND(uint8_t COND, uint16_t *cycles);

    // ROTATE
    
    void RLC_2B_2C(uint8_t* reg,uint16_t *cycles);
    void RLC_2B_4C(uint16_t *cycles);
    void RRC_2B_2C(uint8_t* reg,uint16_t *cycles);
    void RRC_2B_4C(uint16_t *cycles);
    void RL_2B_2C(uint8_t* reg,uint16_t *cycles);
    void RL_2B_4C(uint16_t *cycles);
    void RR_2B_2C(uint8_t* reg,uint16_t *cycles);
    void RR_2B_4C(uint16_t *cycles);

    // SHIFT

    void SLA_2B_2C(uint8_t* reg,uint16_t *cycles);
    void SLA_2B_4C(uint16_t *cycles);
    void SRA_2B_2C(uint8_t* reg,uint16_t *cycles);
    void SRA_2B_4C(uint16_t *cycles);
    void SRL_2B_2C(uint8_t* reg,uint16_t *cycles);
    void SRL_2B_4C(uint16_t *cycles);

    // SWAP

    void SWAP_2B_2C(uint8_t* reg,uint16_t *cycles);
    void SWAP_2B_4C(uint16_t *cycles);


    // BIT

    void BIT_2B_2C(uint8_t bit_n,uint8_t reg,uint16_t *cycles);
    void BIT_2B_3C(uint8_t bit_n,uint16_t *cycles);
    void RES_2B_2C(uint8_t bit_n, uint8_t* reg, uint16_t *cycles);
    void RES_2B_4C(uint8_t bit_n, uint16_t *cycles);
    void SET_2B_2C(uint8_t bit_n, uint8_t* reg, uint16_t *cycles);
    void SET_2B_4C(uint8_t bit_n, uint16_t *cycles);


    // ROTATES
    void RRA(uint16_t *cycles);
};
#endif