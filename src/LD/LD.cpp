#include "LD.h"
#include "cpu.h"
#include "memory.h"
#include<iostream>
void LD_instructions::LD_1B_2C_REG_TO_MEM(u_int16_t address, u_int8_t reg, system_status_struct* system_status, Memory* memory){
     memory->write_8_bit(address, reg);
    *(system_status->PC_value) += 1;
    system_status->cycles = system_status->cycles - 2;
               
}

void LD_instructions::LD_1B_2C_MEM_TO_REG(u_int16_t address, u_int8_t* reg, system_status_struct* system_status, Memory* memory){
     *(reg) = memory->read_8_bit(address);
    *(system_status->PC_value) += 1;
    system_status->cycles = system_status->cycles - 2;
               
}



void LD_instructions::LD_1B_1C(u_int8_t* into, u_int8_t load, system_status_struct* system_status){
    *into = load;
    *(system_status->PC_value)++;
    system_status->cycles--;
}

void LD_instructions::LD_2B_2C(u_int8_t* into, system_status_struct* system_status, Memory* memory){
        *into = memory->read_8_bit(*(system_status->PC_value) + 1);
        *(system_status->PC_value) += 2;
        system_status->cycles -= 2;
}

void LD_instructions::LD_2B_3C(u_int16_t address, system_status_struct* system_status, Memory* memory){
    
        memory->write_8_bit(address,memory->read_8_bit(*(system_status->PC_value) + 1));
        *(system_status->PC_value) += 2;
        system_status->cycles -= 3;
}

void LD_instructions::LD_3B_5C(u_int16_t* SP,system_status_struct* system_status, Memory* memory){
    memory->write_16_bit(*(system_status->PC_value) + 1,*SP);
    system_status->cycles -= 5;
    *(system_status->PC_value) += 3;

}

void LD_instructions::LD_3B_3C(u_int16_t* into, system_status_struct* system_status, Memory* memory){
    *into = memory->read_16_bit(*(system_status->PC_value) + 1);
    system_status->cycles -= 3;
    *(system_status->PC_value) += 3;

}

void LD_instructions::increment_HL(u_int16_t* HL){
    *(HL)++;
}

void LD_instructions::decrement_HL(u_int16_t* HL){
    *(HL)--;
}
