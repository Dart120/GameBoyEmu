#include<iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "cpu.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
    CPU::CPU(Memory memory){
        this->memory = memory;
        
        memset(this->memory.mem,5,65536);
        this->memory.mem[0] = 0;
    }
    u_int8_t CPU::read_8_bit(u_int16_t address){
        return this->memory.read_8_bit(address);
    }
    int CPU::write_8_bit(u_int16_t address, u_int8_t data){
        return this->memory.write_8_bit(address,data);
    }
    u_int16_t CPU::read_16_bit(u_int16_t address){
        return this->memory.read_16_bit(address);
    }
    int CPU::write_16_bit(u_int16_t address, u_int16_t data){
        return this->memory.write_16_bit(address,data);
    }
    int CPU::set_registers(u_int16_t num){
        this->registers.AF_double = 0x01B0;
        this->registers.BC_double = 0x0013;
        this->registers.DE_double = 0x00D8;
        this->registers.HL_double = 0x014D;
        this->registers.PC = 0x0100;
        this->registers.SP = 0xFFFE;
        return 1;
    }
    int CPU::set_flag(flag_index index){
        this->registers.AF.F |= 1UL << index;
        return 1;
     }
     bool CPU::get_flag(flag_index index){
        bool bit = (this->registers.AF.F >> index) & 1U;
        return bit;
     }
     void CPU::FDE(){
         u_int32_t cycles = 69905;
         while (cycles){
            u_int16_t PC_value = this->registers.PC;
            u_int8_t* PC_pointer = this->memory.mem + PC_value;
            fmt::print("here");
            spdlog::info("PC Value: {:X} read", PC_value);
            u_int8_t opcode = *PC_pointer;
            spdlog::info("Opcode: {:X} read", opcode);
            switch (opcode)
            {
            case 0x00:
                spdlog::info("NOP {:X}", opcode);
                cycles--;
                break;
            case 0x1000:
            // NOT IMPLEMENTED STOP
                spdlog::info("STOP {:X}", opcode);
                cycles--;
                break;
            case 0x20:
                spdlog::info("STOP {:X}", opcode);
                cycles--;
                break;
            
            default:
                break;
            }
         }
  
     }

 
