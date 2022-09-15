#include<iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "cpu.h"
#include "memory.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#define FLAG_Z 7                //00001111
#define FLAG_N 6                //0000CHNZ
#define FLAG_H 5                //00004567
#define FLAG_C 4                
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
    int CPU::set_flag(int index){                       //set flag sets corresponding flag to true i.e. 1
        this->registers.AF.F |= 1UL << index;
        return 1;
     }
     bool CPU::get_flag(int index){
        bool bit = (this->registers.AF.F >> index) & 1UL;
        return bit;
     }
     int CPU::clear_flag(int index){                    //clear flag sets corresponding flag to false i.e. 0
        this->registers.AF.F = ~(~(this->registers.AF.F) | 1UL << index);
        return 1;
     }
     template <typename T> void CPU::check_H_8_INC(T a, T b){           
        if ((((a & 0xf) + (b & 0xf)) & 0x10) == 0x10){
            this->set_flag(FLAG_H);
        }
     }
     template <typename T> void CPU::check_H_11_INC(T a, T b){
        if ((((a & 0xfff) + (b & 0xfff)) & 0x800) == 0x800){
            this->set_flag(FLAG_H);
        }
     }
     template <typename T> void CPU::check_C_15_INC(T a, T b){
        if ((((a & 0xffff) + (b & 0xffff)) & 0x8000) == 0x8000){
            this->set_flag(FLAG_C);
        }
     }
     template <typename T> void CPU::check_H_8_DEC(T a, T b){
       
        if (!((a >> 3) & 1) && ((b >> 3) & 1)){
this->set_flag(FLAG_H);
        }
     }
     template <typename T> void CPU::check_C_INC(T a, T b){
        if((((a & 0xf) + (b & 0xf)) & 0x10) == 0x10){
this->set_flag(FLAG_C);
        }
     }
     template <typename T> void CPU::check_if_result_zero(T result){
        if (!result){
            this->set_flag(FLAG_Z);
        }
     }
     std::vector<int> CPU::num_to_list(int num){
        int last_digit = num % 10;
        std::vector<int> result(0);
        result.push_back(last_digit);
        while (num>10){
            num = num / 10;
            last_digit = num % 10;
            result.push_back(last_digit);
        }
        return result;
     }
     void CPU::FDE(){
         u_int32_t cycles = 69905;
         while (cycles){
            u_int16_t* PC_value_ptr = &this->registers.PC;
            u_int16_t PC_value = *PC_value_ptr;
            u_int8_t* PC_pointer = this->memory.mem + PC_value;
            // fmt::print("here");
            spdlog::info("PC Value: {:X} read", PC_value);
            u_int8_t opcode = *PC_pointer;
            spdlog::info("Opcode: {:X} read", opcode);
            switch (opcode)
            {
            case 0x00:
                {spdlog::info("NOP {:X}", opcode);
                this->registers.PC += 1;
                cycles--;
                PC_value += 1;
                break;}
            // case 0x10:
            // // NOT IMPLEMENTED STOP
            //     {spdlog::info("STOP {:X}", opcode);
            //     cycles--;
            //     break;}
            // case 0x20:
            //     {spdlog::info("JR NZ, s8 {:X}", opcode);
            //     cycles--;
            //     break;}
            // case 0x40:
            //     {spdlog::info("LD B,B {:X}", opcode);
            //     this -> registers.BC.B = this->registers.BC.B;
            //     cycles--;
            //     break;}
            // case 0x50:
            //     {spdlog::info("LD D, B {:X}", opcode);
            //     this -> registers.BC.B = this ->registers.DE.D;
            //     cycles--;

                // // this -> registers.BC.B = this->memory.mem[this->registers.HL_double];

                // break;}
            case 0x01:
              {  spdlog::info("LD BC, d16 {:X}", opcode);
                this -> registers.BC_double = this -> memory.read_16_bit(PC_value + 1);
                PC_value += 3;
                cycles = cycles - 3;
                break;}
        
            case 0x02:
                {spdlog::info("LD (BC), A {:X}", opcode);
                this->memory.write_8_bit(this->registers.BC_double, this->registers.AF.A);
                PC_value += 1;
                cycles = cycles - 2;
                break;}
              
            case 0x03:
                {spdlog::info("INC BC {:X}", opcode);
                this->registers.BC_double++;
                PC_value += 1;
                cycles = cycles - 2;
                break;}
             
            case 0x04:
            {    spdlog::info("INC B {:X}", opcode);
                this->check_H_8_INC(this->registers.BC.B,(u_int8_t) 1);
                char result = ++this->registers.BC.B;
                this->check_if_result_zero(result);
                this->clear_flag(FLAG_N);
                PC_value += 1;
                cycles--;
                break;}
            case 0x05:
                {spdlog::info("DEC B {:X}", opcode);
                char result = --this->registers.BC.B;
                this->set_flag(FLAG_N);
                this->check_if_result_zero(result);
                this->check_H_8_DEC(this->registers.BC.B,(u_int8_t) 1);
                PC_value += 1;
                cycles--;
                break;}


            case 0x06:
            {    spdlog::info("LD B, d8 {:X}", opcode);
                this -> registers.BC.B = this -> memory.read_8_bit(PC_value + 1);
                PC_value += 2;
                cycles -= 2;
                break;}

            case 0x07:
                {spdlog::info("RLCA {:X}", opcode);
                bool lastValue = this -> registers.AF.A >> 7 & 1UL;
                this -> registers.AF.A = this -> registers.AF.A << 1;
                if (lastValue){
                    this -> registers.AF.A++;
                    this->set_flag(FLAG_C);
                }else{
                    this->clear_flag(FLAG_C);
                }
                this->check_if_result_zero(this -> registers.AF.A);
                this->clear_flag(FLAG_N);
                this->clear_flag(FLAG_H);
                cycles++;
                PC_value += 1;
                break;}
               
            case 0x08:
                // The stack grows down
                // in other words the least significant byte is first in memory. This scheme is known as little-endian and its opposite is known as big-endian.
                {spdlog::info("LD (a16), SP {:X}", opcode);
                this -> memory.write_16_bit(PC_value + 1,(*this->memory.SP));
                cycles -= 2;
                PC_value += 3;
                break;}
            case 0x09:
            // Fix with info from manual, then go down
                {spdlog::info("ADD HL, BC {:X}", opcode);
                this->clear_flag(FLAG_N);
                this->check_C_15_INC(this -> registers.HL_double,this->registers.BC_double);
                this -> registers.HL_double += this->registers.BC_double;
                cycles -= 2;
                PC_value += 1;
                break;}
            
            case 0x0A:
            {   
                spdlog::info("LD A, (BC) {:X}", opcode);
                this->registers.AF.A = memory.read_8_bit(this->registers.BC_double);
                cycles -= 2;
                PC_value += 1;
                break;
            }

            case 0x0B:                                  
            {
                spdlog::info("DEC BC {:X}", opcode);
                this->registers.BC_double-- ; 
                cycles -= 2;       
                break;     
            }

            case 0x0C:                  //increment contents of register C by 1
            {
                spdlog::info("INC C {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this->check_H_8_INC(this ->registers.BC.C, (u_int8_t) 1);
                char result = ++this ->registers.BC.C;
                this->check_if_result_zero(result);
                cycles -= 1;
                PC_value++;
                break;
                
            }

            case 0x0D:
            {
                spdlog::info("DEC C {:X}", opcode);
                this -> set_flag(FLAG_N);
                this -> check_H_8_DEC(this -> registers.BC.C, (u_int8_t) 1);
                char result = --this -> registers.BC.C;
                this -> check_if_result_zero(result);
                PC_value++;
                cycles -= 1;
                break;
            }

            case 0x0E:
            {
                spdlog::info("LD C, d8 {:X}", opcode);
                this -> registers.BC.C = memory.read_8_bit(PC_value + 1 );
                PC_value += 2;
                cycles -= 2;
                break;
            }

            case 0x0F:
            {
                spdlog::info("RRCA {:X}", opcode);
                bool firstValue = this -> registers.AF.A & 1UL;
                this -> registers.AF.A = this -> registers.AF.A >> 1;
                if (firstValue){
                    this->registers.AF.A |= 1UL << 7;
                    this->set_flag(FLAG_C);
                }else{
                    this->clear_flag(FLAG_C);
                }
                this->check_if_result_zero(this -> registers.AF.A);
                this->clear_flag(FLAG_N);
                this->clear_flag(FLAG_H);
                PC_value += 1;
                cycles++;
                break;
            }
            

            
            case 0x20:{
                if (!this->get_flag(FLAG_Z)){
                    PC_value += this->memory.read_8_bit(PC_value + 1);
                    cycles += 3;
                } else {
                    PC_value++;
                    cycles += 2;
                }
            }
              case 0x21:
              {  spdlog::info("LD HL, d16 {:X}", opcode);
                this -> registers.HL_double = this -> memory.read_16_bit(PC_value + 1);
                PC_value += 3;
                cycles = cycles - 3;
                break;}
            case 0x22:
                {spdlog::info("LD (HL+), A {:X}", opcode);
                this->memory.write_8_bit(this->registers.HL_double, this->registers.AF.A);
                this->registers.HL_double++;
                PC_value += 1;
                cycles = cycles - 2;
                break;}
            case 0x23:
                {spdlog::info("INC HL {:X}", opcode);
                this->registers.HL_double++;
                PC_value += 1;
                cycles = cycles - 2;
                break;}
            case 0x24:
            {    spdlog::info("INC H {:X}", opcode);
                this->check_H_8_INC(this->registers.HL.H,(u_int8_t) 1);
                char result = ++this->registers.HL.H;
                this->check_if_result_zero(result);
                this->clear_flag(FLAG_N);
                PC_value += 1;
                cycles--;
                break;}
            case 0x25:
                {
                    spdlog::info("DEC H {:X}", opcode);
                    char result = --this->registers.HL.H;
                    this->set_flag(FLAG_N);
                    this->check_if_result_zero(result);
                    this->check_H_8_DEC(this->registers.HL.H,(u_int8_t) 1);
                    PC_value += 1;
                    cycles--;
                    break;
                }
            case 0x26:
            {    spdlog::info("LD H, d8 {:X}", opcode);
                this -> registers.HL.H = this -> memory.read_8_bit(PC_value + 1);
                PC_value += 2;
                cycles -= 2;
                break;}
            case 0x27:
                {spdlog::info("DAA {:X}", opcode);
                std::vector<int> digits = this->num_to_list(this->registers.AF.A);
                reverse(digits.begin(),digits.end());
                if (this->get_flag(FLAG_N)){
                    if (digits[0] > 9 || this->get_flag(FLAG_C)){
                        digits[0] -= 6; 
                    }
                    if (digits[1] > 9 || this->get_flag(FLAG_H)){
                        digits[1] -= 6; 
                    }
                }else{
                    if (digits[0] > 9 || this->get_flag(FLAG_C)){
                        digits[0] += 6; 
                    }
                    if (digits[1] > 9 || this->get_flag(FLAG_H)){
                        digits[1] += 6; 
                    }
                }
                this->registers.AF.A = (digits[0] * 10) + digits[1];
                if (this->registers.AF.A > 0x99){
                    this->set_flag(FLAG_C);
                }else{
                    this->clear_flag(FLAG_C);
                }
                cycles++;
                PC_value += 1;
                break;}
            case 0x28:
            {
                if (this->get_flag(FLAG_Z)){
                    PC_value += this->memory.read_8_bit(PC_value + 1);
                    cycles += 3;
                } else {
                    PC_value++;
                    cycles += 2;
                }
            }
            case 0x29:
            // Fix with info from manual, then go down
                {
                spdlog::info("ADD HL, HL {:X}", opcode);
                this->clear_flag(FLAG_N);
                this->check_C_15_INC(this -> registers.HL_double,this->registers.HL_double);
                this -> registers.HL_double += this->registers.HL_double;
                cycles -= 2;
                PC_value += 1;
                break;
                }

            case 0x2A:
            {   
                spdlog::info("LD A, (BC) LD A, (HL+) {:X}", opcode);
                this->registers.HL_double++;
                this->registers.AF.A = memory.read_8_bit(this->registers.HL_double);
                cycles -= 2;
                PC_value += 1;
                break;
            }
            case 0x2B:                                  
            {
                spdlog::info("DEC HL {:X}", opcode);
                this->registers.HL_double-- ; 
                cycles -= 2;  
                PC_value++;     
                break;     
            }
            case 0x2C:                  //increment contents of register C by 1
            {
                spdlog::info("INC L {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this->check_H_8_INC(this ->registers.HL.L, (u_int8_t) 1);
                char result = ++this ->registers.HL.L;
                this->check_if_result_zero(result);
                PC_value++;
                cycles -= 1;
                break;
                
            }

            case 0x2D:
            {
                spdlog::info("DEC L {:X}", opcode);
                this -> set_flag(FLAG_N);
                this -> check_H_8_DEC(this -> registers.HL.L, (u_int8_t) 1);
                char result = --this -> registers.HL.L;
                this -> check_if_result_zero(result);
                PC_value++;
                cycles -= 1;
                break;
            }

             case 0x2E:
            {
                spdlog::info("LD L, d8 {:X}", opcode);
                this -> registers.HL.L = memory.read_8_bit(PC_value + 1 );
                PC_value += 2;
                cycles -= 2;
                break;
            }

            case 0x2F:
            {
                spdlog::info("CPL {:X}", opcode);
                this->registers.AF.A = ~this->registers.AF.A;
                this->set_flag(FLAG_N);
                this->set_flag(FLAG_H);
                PC_value += 1;
                cycles++;
                break;
            }
            case 0x40:
            {   
                spdlog::info("LD B, B {:X}", opcode);
                this -> registers.BC.B = this -> registers.BC.B;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x41:
            {   
                spdlog::info("LD B, C {:X}", opcode);
                this -> registers.BC.B = this -> registers.BC.C;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x42:
            {   
                spdlog::info("LD B, D {:X}", opcode);
                this -> registers.BC.B = this -> registers.DE.D;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x43:
            {   
                spdlog::info("LD B, E {:X}", opcode);
                this -> registers.BC.B = this -> registers.DE.E;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x44:
            {   
                spdlog::info("LD B, H {:X}", opcode);
                this -> registers.BC.B = this -> registers.HL.H;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x45:
            {   
                spdlog::info("LD B, L {:X}", opcode);
                this -> registers.BC.B = this -> registers.HL.L;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x46:
            {   
                spdlog::info("LD B, (HL) {:X}", opcode);
                this -> registers.BC.B = this->read_8_bit(this->registers.HL_double);
                PC_value += 1;
                cycles -= 2;
                break;
            }
            case 0x47:
            {   
                spdlog::info("LD B, A {:X}", opcode);
                this -> registers.BC.B = this -> registers.AF.A;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x48:
            {   
                spdlog::info("LD C, B {:X}", opcode);
                this -> registers.BC.C = this -> registers.BC.B;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x49:
            {   
                spdlog::info("LD C, C {:X}", opcode);
                this -> registers.BC.C = this -> registers.BC.C;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x4A:
            {   
                spdlog::info("LD C, D {:X}", opcode);
                this -> registers.BC.C = this -> registers.DE.D;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x4B:
            {   
                spdlog::info("LD C, E {:X}", opcode);
                this -> registers.BC.C = this -> registers.DE.E;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x4C:
            {   
                spdlog::info("LD C, H {:X}", opcode);
                this -> registers.BC.C = this -> registers.HL.H;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x4D:
            {   
                spdlog::info("LD C, L {:X}", opcode);
                this -> registers.BC.C = this -> registers.HL.L;
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x4E:
            {   
                spdlog::info("LD C, (HL) {:X}", opcode);
                this -> registers.BC.B = this->read_8_bit(this->registers.HL_double);
                PC_value += 1;
                cycles -= 1;
                break;
            }
            case 0x4F:
            {   
                spdlog::info("LD C, A {:X}", opcode);
                this -> registers.BC.C= this -> registers.AF.A;
                PC_value += 2;
                cycles -= 2;
                break;
            }
            
            

           

            default:
                break;
            }
         }
  
     }

 
