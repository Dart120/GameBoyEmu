#include<iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "cpu.h"
#include "memory.h"
#include "LD.h"
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
         u_int32_t *cycles = &this->system_status.cycles;
        (*cycles) = 69905;
         while (cycles){
            (this->system_status.PC_value) = &this->registers.PC;
            u_int16_t *PC_value = &this->registers.PC;
            // u_int8_t *PC_pointer = this->memory.mem +(*PC_value);
            // fmt::print("here");
            spdlog::info("PC Value: {:X} read",(*PC_value));
            u_int8_t opcode = this->memory.mem[*PC_value];
            spdlog::info("Opcode: {:X} read", opcode);
            switch (opcode)
            {
            case 0x00:
                {spdlog::info("NOP {:X}", opcode);
                this->registers.PC += 1;
               (*cycles)--;
               (*PC_value) += 1;
                break;}
            // case 0x10:
            // // NOT IMPLEMENTED STOP
            //     {spdlog::info("STOP {:X}", opcode);
            //    (*cycles)--;
            //     break;}
            // case 0x20:
            //     {spdlog::info("JR NZ, s8 {:X}", opcode);
            //    (*cycles)--;
            //     break;}
            // case 0x40:
            //     {spdlog::info("LD B,B {:X}", opcode);
            //     this -> registers.BC.B = this->registers.BC.B;
            //    (*cycles)--;
            //     break;}
            // case 0x50:
            //     {spdlog::info("LD D, B {:X}", opcode);
            //     this -> registers.BC.B = this ->registers.DE.D;
            //    (*cycles)--;

                // // this -> registers.BC.B = this->memory.mem[this->registers.HL_double];

                // break;}
            case 0x01:
              {  spdlog::info("LD BC, d16 {:X}", opcode);
                 LD_instructions::LD_3B_3C(&(this -> registers.BC_double),&(this->system_status), &(this->memory));
            //     this -> registers.BC_double = this -> memory.read_16_bit(*PC_value + 1);
            //    (*PC_value) += 3;
            //    (*cycles) =(*cycles) - 3;
                break;}
        
            case 0x02:
                {spdlog::info("LD (BC), A {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this -> registers.BC_double),(this -> registers.AF.A),&(this->system_status), &(this->memory));
            //     this->memory.write_8_bit(this->registers.BC_double, this->registers.AF.A);
            //    (*PC_value) += 1;
            //    (*cycles) =(*cycles) - 2;
                break;}
              
            case 0x03:
                {spdlog::info("INC BC {:X}", opcode);
                this->registers.BC_double++;
               (*PC_value) += 1;
               (*cycles) =(*cycles) - 2;
                break;}
             
            case 0x04:
            {    spdlog::info("INC B {:X}", opcode);
                this->check_H_8_INC(this->registers.BC.B,(u_int8_t) 1);
                char result = ++this->registers.BC.B;
                this->check_if_result_zero(result);
                this->clear_flag(FLAG_N);
               (*PC_value) += 1;
               (*cycles)--;
                break;}
            case 0x05:
                {spdlog::info("DEC B {:X}", opcode);
                char result = --this->registers.BC.B;
                this->set_flag(FLAG_N);
                this->check_if_result_zero(result);
                this->check_H_8_DEC(this->registers.BC.B,(u_int8_t) 1);
               (*PC_value) += 1;
               (*cycles)--;
                break;}


            case 0x06:
            {    spdlog::info("LD B, d8 {:X}", opcode);
                LD_instructions::LD_2B_2C(&(this -> registers.BC.B),&(this->system_status), &(this->memory));
            //     this -> registers.BC.B = this -> memory.read_8_bit(*PC_value + 1);
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
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
               (*cycles)++;
               (*PC_value) += 1;
                break;}
               
            case 0x08:
                // The stack grows down
                // in other words the least significant byte is first in memory. This scheme is known as little-endian and its opposite is known as big-endian.
                {spdlog::info("LD (a16), SP {:X}", opcode);
                LD_instructions::LD_3B_5C(&(this -> registers.SP), &(this->system_status), &(this->memory));
            //     this -> memory.write_16_bit(*PC_value + 1,(*this->memory.SP));
            //    (*cycles) -= 2;
            //    (*PC_value) += 3;
                break;}
            case 0x09:
            // Fix with info from manual, then go down
                {spdlog::info("ADD HL, BC {:X}", opcode);
                this->clear_flag(FLAG_N);
                this->check_C_15_INC(this -> registers.HL_double,this->registers.BC_double);
                this -> registers.HL_double += this->registers.BC_double;
               (*cycles) -= 2;
               (*PC_value) += 1;
                break;}
            
            case 0x0A:
            {   
                spdlog::info("LD A, (BC) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this -> registers.BC_double),&(this -> registers.AF.A),&(this->system_status), &(this->memory));
            //     this->registers.AF.A = memory.read_8_bit(this->registers.BC_double);
            //    (*cycles) -= 2;
            //    (*PC_value) += 1;
                break;
            }

            case 0x0B:                                  
            {
                spdlog::info("DEC BC {:X}", opcode);
                this->registers.BC_double-- ; 
               (*cycles) -= 2;    
               (*PC_value) += 1;   
                break;     
            }

            case 0x0C:                  //increment contents of register C by 1
            {
                spdlog::info("INC C {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this->check_H_8_INC(this ->registers.BC.C, (u_int8_t) 1);
                char result = ++this ->registers.BC.C;
                this->check_if_result_zero(result);
               (*cycles) -= 1;
               (*PC_value)++;
                break;
                
            }

            case 0x0D:
            {
                spdlog::info("DEC C {:X}", opcode);
                this -> set_flag(FLAG_N);
                this -> check_H_8_DEC(this -> registers.BC.C, (u_int8_t) 1);
                char result = --this -> registers.BC.C;
                this -> check_if_result_zero(result);
               (*PC_value)++;
               (*cycles) -= 1;
                break;
            }

            case 0x0E:
            {
                spdlog::info("LD C, d8 {:X}", opcode);
                LD_instructions::LD_2B_2C(&(this -> registers.BC.C),&(this->system_status), &(this->memory));
            //     this -> registers.BC.C = memory.read_8_bit(*PC_value + 1 );
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
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
               (*PC_value) += 1;
               (*cycles)++;
                break;
            }

            case 0x10:
            {
                spdlog::info("STOP {:X} read", opcode);
                exit(0);
               (*cycles)--;
               (*PC_value) += 2;
                break;
            }

            case 0x11:
            {
                spdlog::info("LD DE, d16 {:X}", opcode);
                LD_instructions::LD_3B_3C(&(this -> registers.DE_double),&(this->system_status), &(this->memory));
            //     this -> registers.DE_double = this -> memory.read_16_bit(*PC_value + 1);
            //    (*PC_value) += 3;
            //    (*cycles) -= 3;
                break;
            }

            case 0x12:
            {
                spdlog::info("LD (DE), A {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this -> registers.DE_double),this->registers.AF.A,&(this->system_status), &(this->memory));
            //     this -> memory.write_8_bit(this -> registers.DE_double, this -> registers.AF.A);
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x13:
            {
                spdlog::info("INC DE {:X}", opcode);
                this -> registers.DE_double++;
               (*PC_value) += 1;
               (*cycles) -= 2;
                break;
            }
             case 0x14:
            {
                spdlog::info("INC D {:X}", opcode);
                this -> check_H_8_INC(this -> registers.DE.D, (u_int8_t) 1);
                char result = ++this ->registers.DE.D;
                this -> check_if_result_zero(result);
                this -> clear_flag(FLAG_N);
               (*PC_value) += 1;
               (*cycles)--;
                break;
            }

            case 0x15:
            {
                spdlog::info("DEC D {:X}", opcode);
                this -> check_H_8_DEC(this -> registers.DE.D, (u_int8_t) 1);
                char result = --this -> registers.DE.D;
                this -> check_if_result_zero(result);
                this -> set_flag(FLAG_N);
               (*PC_value) += 1;
               (*cycles)--;
                break;
            }

            case 0x16:
            {
                spdlog::info("LD D, d8 {:X}", opcode);
                LD_instructions::LD_2B_2C(&(this -> registers.DE.D),&(this->system_status), &(this->memory));
            //     this -> registers.DE.D = this -> memory.read_8_bit(*PC_value +1);
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
                break;
            }

            case 0x17:
            {
                spdlog::info("RLA {:X}", opcode);
                this -> registers.AF.A = this -> registers.AF.A<< 1;
                if(get_flag(FLAG_C)){
                   this -> registers.AF.A |= 1UL;
                   
                }
                
                this -> check_if_result_zero(this -> registers.AF.A);
                this -> clear_flag(FLAG_N);
                this -> clear_flag(FLAG_H);
               (*PC_value) += 1;
               (*cycles) -= 1;
                break;
            }

            case 0x18:
            {
                spdlog::info("JR s8 {:X}", opcode);
                
               (*PC_value) += this -> memory.read_8_bit(*PC_value + 1);
               (*cycles) += 3;  
                break;
            }

            case 0x19:
            {
                spdlog::info("ADD HL, DE {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this -> check_C_15_INC(this -> registers.HL_double, this -> registers.DE_double);
                this -> registers.HL_double += this -> registers.DE_double;
               (*PC_value) += 1;
               (*cycles) -= 1;
                break;
            }

            case 0x1A:
            {
                spdlog::info("LD A, (DE) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this -> registers.DE_double),&(this->registers.AF.A),&(this->system_status), &(this->memory));
            //     this -> registers.AF.A = memory.read_8_bit(this -> registers.DE_double);
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x1B:
            {
                spdlog::info("DEC DE {:X}", opcode);
                this -> registers.DE_double--;
               (*PC_value) += 1;
               (*cycles) -= 2;
                break;
            }

            case 0x1C:
            {
                spdlog::info("INC E {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this -> check_H_8_INC(this -> registers.DE.E, (u_int8_t) 1);
                char result = ++this -> registers.DE.E;
                this -> check_if_result_zero(result);
               (*cycles) -= 1;
               (*PC_value) += 1;
                break;
            }

            case 0x1D:
            {
                spdlog::info("DEC E {:X}", opcode);
                this -> set_flag(FLAG_N);
                this -> check_H_8_DEC(this -> registers.DE.E, (u_int8_t) 1);
                char result = --this -> registers.DE.E;
                this -> check_if_result_zero(result);
               (*PC_value) += 1;
               (*cycles) -= 1;
                break;
            }

            case 0x1E:
            {
                spdlog::info("LD E, d8 {:X}", opcode);
                LD_instructions::LD_2B_2C(&(this -> registers.DE.E),&(this->system_status), &(this->memory));
            //     this -> registers.DE.E = memory.read_8_bit(*PC_value + 1);
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
                break;
            }

            case 0x1F:
            {
                spdlog::info("RRA {:X}", opcode);
                
                this -> registers.AF.A = this -> registers.AF.A >> 1;
                if(get_flag(FLAG_C)){
                    this -> registers.AF.A |= 1L;
                }

                clear_flag(FLAG_H);
                clear_flag(FLAG_N);
                this -> check_if_result_zero(this -> registers.AF.A);
               (*PC_value) += 1;
               (*cycles) -= 1;
                break;
            }
            
            

            
            case 0x20:
            {
                spdlog::info("JR NZ, s8 {:X}", opcode);
                if (!this->get_flag(FLAG_Z)){
                   (*PC_value) += this->memory.read_8_bit(*PC_value + 1);
                   (*cycles) += 3;
                } else {
                   (*PC_value)++;
                   (*cycles) += 2;
                }
            }
              case 0x21:
              {  spdlog::info("LD HL, d16 {:X}", opcode);
                LD_instructions::LD_3B_3C(&(this -> registers.HL_double),&(this->system_status), &(this->memory));
            //     this -> registers.HL_double = this -> memory.read_16_bit(*PC_value + 1);
            //    (*PC_value) += 3;
            //    (*cycles) =(*cycles) - 3;
                break;}
            case 0x22:
                {spdlog::info("LD (HL+), A {:X}", opcode);
                LD_instructions::increment_HL(&(this -> registers.HL_double));
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this -> registers.AF.A),&(this->system_status), &(this->memory));
                
            //     this->memory.write_8_bit(this->registers.HL_double, this->registers.AF.A);
            //     this->registers.HL_double++;
            //    (*PC_value) += 1;
            //    (*cycles) =(*cycles) - 2;
                break;}
            case 0x23:
                {spdlog::info("INC HL {:X}", opcode);
                this->registers.HL_double++;
               (*PC_value) += 1;
               (*cycles) =(*cycles) - 2;
                break;}
            case 0x24:
            {    spdlog::info("INC H {:X}", opcode);
                this->check_H_8_INC(this->registers.HL.H,(u_int8_t) 1);
                char result = ++this->registers.HL.H;
                this->check_if_result_zero(result);
                this->clear_flag(FLAG_N);
               (*PC_value) += 1;
               (*cycles)--;
                break;}
            case 0x25:
                {
                    spdlog::info("DEC H {:X}", opcode);
                    char result = --this->registers.HL.H;
                    this->set_flag(FLAG_N);
                    this->check_if_result_zero(result);
                    this->check_H_8_DEC(this->registers.HL.H,(u_int8_t) 1);
                   (*PC_value) += 1;
                   (*cycles)--;
                    break;
                }
            case 0x26:
            {    spdlog::info("LD H, d8 {:X}", opcode);
           
                LD_instructions::LD_2B_2C(&(this->registers.HL.H),&(this->system_status), &(this->memory));
            //     this -> registers.HL.H = this -> memory.read_8_bit(*PC_value + 1);
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
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
               (*cycles)++;
               (*PC_value) += 1;
                break;}
            case 0x28:
            {
                if (this->get_flag(FLAG_Z)){
                   (*PC_value) += this->memory.read_8_bit(*PC_value + 1);
                   (*cycles) += 3;
                } else {
                   (*PC_value)++;
                   (*cycles) += 2;
                }
            }
            case 0x29:
            // Fix with info from manual, then go down
                {
                spdlog::info("ADD HL, HL {:X}", opcode);
                this->clear_flag(FLAG_N);
                this->check_C_15_INC(this -> registers.HL_double,this->registers.HL_double);
                this -> registers.HL_double += this->registers.HL_double;
               (*cycles) -= 2;
               (*PC_value) += 1;
                break;
                }

            case 0x2A:
            {   
                spdlog::info("LD A, (HL+) {:X}", opcode);
                LD_instructions::increment_HL(&(this -> registers.HL_double));
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this -> registers.AF.A),&(this->system_status), &(this->memory));
            //     this->registers.HL_double++;
            //     this->registers.AF.A = memory.read_8_bit(this->registers.HL_double);
            //    (*cycles) -= 2;
            //    (*PC_value) += 1;
                break;
            }
            case 0x2B:                                  
            {
                spdlog::info("DEC HL {:X}", opcode);
                this->registers.HL_double-- ; 
               (*cycles) -= 2;  
               (*PC_value)++;     
                break;     
            }
            case 0x2C:                  //increment contents of register C by 1
            {
                spdlog::info("INC L {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this->check_H_8_INC(this ->registers.HL.L, (u_int8_t) 1);
                char result = ++this ->registers.HL.L;
                this->check_if_result_zero(result);
               (*PC_value)++;
               (*cycles) -= 1;
                break;
                
            }

            case 0x2D:
            {
                spdlog::info("DEC L {:X}", opcode);
                this -> set_flag(FLAG_N);
                this -> check_H_8_DEC(this -> registers.HL.L, (u_int8_t) 1);
                char result = --this -> registers.HL.L;
                this -> check_if_result_zero(result);
               (*PC_value)++;
               (*cycles) -= 1;
                break;
            }

             case 0x2E:
            {
                spdlog::info("LD L, d8 {:X}", opcode);
                LD_instructions::LD_2B_2C(&(this -> registers.HL.L),&(this->system_status), &(this->memory));
            //     this -> registers.HL.L = memory.read_8_bit(*PC_value + 1 );
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
                break;
            }

            case 0x2F:
            {
                spdlog::info("CPL {:X}", opcode);
                this->registers.AF.A = ~this->registers.AF.A;
                this->set_flag(FLAG_N);
                this->set_flag(FLAG_H);
               (*PC_value) += 1;
               (*cycles)++;
                break;
            }

            case 0x30:
            {
                spdlog::info("JR NC s8 {:X}", opcode);
                if (!this -> get_flag(FLAG_C)){
                   (*PC_value) += this -> memory.read_8_bit(*PC_value + 1);
                   (*cycles) += 3;
                } else{
                   (*PC_value)++;
                   (*cycles) += 2;
                }
            }

            case 0x31:
            {
                spdlog::info("LD SP, d16 {:X}", opcode);
                LD_instructions::LD_3B_3C(&(this -> registers.SP),&(this->system_status), &(this->memory));
            //     this -> registers.SP = this -> memory.read_16_bit(*PC_value +1);
            //    (*PC_value) += 3;
            //    (*cycles) -= 3;
                break;
            }

            case 0x32:
            {
                spdlog::info("LD (HL-), A {:X}", opcode);
                LD_instructions::decrement_HL(&(this -> registers.HL_double));
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this -> registers.AF.A),&(this->system_status), &(this->memory));
            //     this -> memory.write_8_bit(this -> registers.HL_double, this -> registers.AF.A);
            //     this -> registers.HL_double--;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }


            case 0x33:
            {
                spdlog::info("INC SP {:X}", opcode);
                this -> registers.SP++;
               (*PC_value) += 1;
               (*cycles) -= 2;
                break;
            }

            // case 0x34:
            // {
            //     spdlog::info("INC (HL) {:X}", opcode);
            //     this->check_H_8_INC(this->registers.HL,(u_int8_t) 1);            ERROR HERE This is because you need to cast 1 to u_int16_t not 8 because HL is 16bits   all errors you are having stem from this
            //     char result = ++this -> registers.HL;                            ERROR HERE You cant store HL in a char as HL is 16bits and a char is 8 buits
            //     this -> check_if_result_zero(result);
            //     this -> clear_flag(FLAG_N);
            //    (*PC_value) += 1;
            //    (*cycles)-= 3;
            //     break;
            // }

            case 0x35:
            {
                spdlog::info("DEC (HL) {:X}", opcode);
                // this -> check_H_8_DEC(this -> registers.HL, (u_int8_t) 1); ERRORS HERE
                // char result = --this -> registers.HL;                      ERRORS HERE
                //this -> check_if_result_zero(result);
                this -> clear_flag(FLAG_N);
               (*PC_value) += 1;
               (*cycles) -= 3;
                break;
            }

            case 0x36:
            {
                spdlog::info("LD (HL), d8 {:x}", opcode);
                LD_instructions::LD_2B_3C((this->registers.HL_double),&(this->system_status), &(this->memory));
                //this -> registers.HL = this -> memory.read_8_bit(*PC_value + 1);    
            //    (*PC_value) += 2;
            //    (*cycles) -= 3;
                break;
            }

            case 0x37:
            {
                spdlog::info("SCF {:X}", opcode);
                this->set_flag(FLAG_C);
            }

            case 0x38:
            {
                spdlog::info("JR C, s8 {:X}", opcode);
                if (this -> get_flag(FLAG_C)){
                   (*PC_value) += this -> memory.read_8_bit(*PC_value + 1);
                   (*cycles) += 3;
                } else{
                   (*PC_value) ++;
                   (*cycles) += 2;
                }
            }
                

            case 0x39:
            {
                spdlog::info("ADD HL, SP {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this -> check_C_15_INC(this -> registers.SP, this -> registers.HL_double);
                this -> registers.HL_double += this -> registers.HL_double;
               (*cycles) -= 2;
               (*PC_value) += 1;
                break;
            }

            case 0x3A:
            {
                spdlog::info("LD A, (HL-) {:X}", opcode);
                LD_instructions::decrement_HL(&(this->registers.HL_double));
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this->registers.AF.A),&(this->system_status), &(this->memory));
            //     this -> registers.HL_double--;
            //     this -> registers.AF.A = memory.read_8_bit(this -> registers.HL_double);
            //    (*cycles) -= 2;
            //    (*PC_value) += 1;
                break;
            }

            case 0x3B:
            {
                spdlog::info("DEC SP {:x}", opcode);
                this -> registers.SP --;
               (*cycles) -= 2;
               (*PC_value)++ ;
                break;
            }

            case 0x3c:
            {
                spdlog::info("INC A {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this -> check_H_8_INC(this -> registers.AF.A, (u_int8_t) 1);
                char result = -- this -> registers.AF.A;
                this -> check_if_result_zero(result);
               (*PC_value)++;
               (*cycles) -= 1;
                break;
            }

            case 0x3D:
            {
                spdlog::info("DEC A {:x}", opcode);
                this -> set_flag(FLAG_N);
                this -> check_H_8_DEC(this -> registers.AF.A, (u_int8_t) 1);
                char result = -- this -> registers.AF.A;
                this -> check_if_result_zero(result);
               (*PC_value) ++;
               (*cycles) -= 1;
                break;
            }

            case 0X3E:
            {
                spdlog::info("LD A, d8 {:X}", opcode);
                LD_instructions::LD_2B_2C(&(this->registers.AF.A),&system_status,&memory);
            //     this -> registers.AF.A = memory.read_8_bit(*PC_value + 1);
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
                break;   
            }

            case 0x3F:
            {
                spdlog::info("CCF {:X}", opcode);
                this -> clear_flag(FLAG_N);
                this -> clear_flag(FLAG_H);
               // this -> ~set_flag(FLAG_C);            ONLY ERROR WHERE IM LIKE AIGHT FAIR ENOUGH, IDK IF I CAN DO THIS TO FLIP CARRY FLAG
            //    You can, if the bit is set then clear it if the bit is clear then set it
               (*PC_value) += 1;
               (*cycles) -= 1;
            }












            case 0x40:
            {   
                spdlog::info("LD B, B {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.BC.B),&system_status);
            //     this -> registers.BC.B = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x41:
            {   
                spdlog::info("LD B, C {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.BC.C),&system_status);
            //     this -> registers.BC.B = this -> registers.BC.C;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x42:
            {   
                spdlog::info("LD B, D {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.DE.D),&system_status);
            //     this -> registers.BC.B = this -> registers.DE.D;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x43:
            {   
                spdlog::info("LD B, E {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.DE.E),&system_status);
            //     this -> registers.BC.B = this -> registers.DE.E;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x44:
            {   
                spdlog::info("LD B, H {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.HL.H),&system_status);
            //     this -> registers.BC.B = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x45:
            {   
                spdlog::info("LD B, L {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.HL.L),&system_status);
            //     this -> registers.BC.B = this -> registers.HL.L;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x46:
            {   
                spdlog::info("LD B, (HL) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this->registers.BC.B),&system_status,&memory);
            //     this -> registers.BC.B = this->read_8_bit(this->registers.HL_double);
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }
            case 0x47:
            {   
                spdlog::info("LD B, A {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.B),(this->registers.AF.A),&system_status);
            //     this -> registers.BC.B = this -> registers.AF.A;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x48:
            {   
                spdlog::info("LD C, B {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.BC.B),&system_status);
            //     this -> registers.BC.C = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x49:
            {   
                spdlog::info("LD C, C {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.BC.C),&system_status);
            //     this -> registers.BC.C = this -> registers.BC.C;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x4A:
            {   
                spdlog::info("LD C, D {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.DE.D),&system_status);
            //     this -> registers.BC.C = this -> registers.DE.D;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x4B:
            {   
                spdlog::info("LD C, E {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.DE.E),&system_status);
            //     this -> registers.BC.C = this -> registers.DE.E;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x4C:
            {   
                spdlog::info("LD C, H {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.HL.H),&system_status);
            //     this -> registers.BC.C = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x4D:
            {   
                spdlog::info("LD C, L {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.HL.L),&system_status);
            //     this -> registers.BC.C = this -> registers.HL.L;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x4E:
            {   
                spdlog::info("LD C, (HL) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this->registers.BC.C),&system_status,&memory);
            //     this -> registers.BC.B = this->read_8_bit(this->registers.HL_double);
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x4F:
            {   
                spdlog::info("LD C, A {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.BC.C),(this->registers.AF.A),&system_status);
            //     this -> registers.BC.C= this -> registers.AF.A;
            //    (*PC_value) += 2;
            //    (*cycles) -= 2;
                break;
            }

            case 0x50:
            {
                spdlog::info("LD D, B {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.BC.B),&system_status);
            //     this -> registers.DE.D = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x51:
            {
                spdlog::info("LD D, C {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.BC.C),&system_status);
            //     this -> registers.DE.D = this -> registers.BC.C;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x52:
            {
                spdlog::info("LD D, D {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.DE.D),&system_status);

            //     this -> registers.DE.D = this -> registers.DE.D;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x53:
            {
                spdlog::info("LD D, E {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.DE.E),&system_status);
            //     this -> registers.DE.D = this -> registers.DE.E;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x54:
            {
                spdlog::info("LD D, H {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.HL.H),&system_status);
            //     this -> registers.DE.D = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x55:
            {
                spdlog::info("LD D, L {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.HL.L),&system_status);
            //     this -> registers.DE.D = this -> registers.HL.L;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x56:
            {
                spdlog::info("LD D, (HL) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this->registers.DE.D),&system_status,&memory);
            //     this -> registers.DE.D = this -> registers.HL_double;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x57:
            {
                spdlog::info("LD D, A {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.D),(this->registers.AF.A),&system_status);
            //     this -> registers.DE.D = this -> registers.AF.A;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x58:
            {
                spdlog::info("LD E, B {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.BC.B),&system_status);
            //     this -> registers.DE.E = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x59:
            {
                spdlog::info("LD E, C {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.BC.C),&system_status);
            //     this -> registers.DE.E = this -> registers.BC.C;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x5A:
            {
                spdlog::info("LD E, D {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.DE.D),&system_status);
            //     this -> registers.DE.E = this -> registers.DE.D;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x5B:
            {
                spdlog::info("LD E, E {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.DE.E),&system_status);
            //     this -> registers.DE.E = this -> registers.DE.E;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x5C:
            {
                spdlog::info("LD E, H {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.HL.H),&system_status);
            //     this -> registers.DE.E = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x5D:
            {
                spdlog::info("LD E, L {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.HL.L),&system_status);
            //     this -> registers.DE.E = this -> registers.HL.L;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x5E:
            {
                spdlog::info("LD E, (HL) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this->registers.DE.E),&system_status,&memory);
                this -> registers.DE.E = this -> registers.HL_double;
               (*PC_value) += 1;
               (*cycles) -= 1;
                break;
            }


            case 0x5F:
            {
                spdlog::info("LD E, A {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.DE.E),(this->registers.AF.A),&system_status);
            //     this -> registers.DE.E = this -> registers.AF.A;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }



            case 0x70:
            {
                spdlog::info("LD (HL), B {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.BC.B),&system_status,&memory);
            //     this -> registers.HL_double = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }
            

            case 0x71:
            {
                spdlog::info("LD (HL), C {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.BC.C),&system_status,&memory);
            //     this -> registers.HL_double = this -> registers.BC.C;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x72:
            {
                spdlog::info("LD (HL), D {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.DE.D),&system_status,&memory);

            //     this -> registers.HL_double = this -> registers.DE.D;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x73:
            {
                spdlog::info("LD (HL), D {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.DE.D),&system_status,&memory);

            //     this -> registers.HL_double = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x74:
            {
                spdlog::info("LD (HL), H {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.HL.H),&system_status,&memory);
            //     this -> registers.HL_double = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x75:
            {
                spdlog::info("LD (HL), L {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.HL.L),&system_status,&memory);
            //     this -> registers.HL_double = this -> registers.HL.L;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x76:
            {
                spdlog::info("HALT {:X}", opcode);
                ;
            }

            case 0x77:
            {
                spdlog::info("LD (HL), A {:X}", opcode);
                LD_instructions::LD_1B_2C_REG_TO_MEM((this->registers.HL_double),(this->registers.AF.A),&system_status,&memory);
            //     this -> registers.HL_double = this -> registers.AF.A;
            //    (*PC_value) += 1;
            //    (*cycles) -= 2;
                break;
            }

            case 0x78:
            {
                spdlog::info("LD A, B {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.BC.B),&system_status);
            //     this -> registers.AF.A = this -> registers.BC.B;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x79:
            {
                spdlog::info("LD A, C {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.BC.C),&system_status);
            //     this -> registers.AF.A = this -> registers.BC.C;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x7A:
            {
                spdlog::info("LD A, D {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.DE.D),&system_status);
            //     this -> registers.AF.A = this -> registers.DE.D;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x7B:
            {
                spdlog::info("LD A, E {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.DE.E),&system_status);
            //     this -> registers.AF.A = this -> registers.DE.E;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x7C:
            {
                spdlog::info("LD A, H {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.HL.H),&system_status);
            //     this -> registers.AF.A = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x7D:
            {
                spdlog::info("LD A, L {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.HL.L),&system_status);
            //     this -> registers.AF.A = this -> registers.HL.H;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x7E:
            {
                spdlog::info("LD A, (HL) {:X}", opcode);
                LD_instructions::LD_1B_2C_MEM_TO_REG((this->registers.HL_double),&(this->registers.AF.A),&system_status,&memory);
            //     this -> registers.AF.A = this -> registers.HL_double;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }

            case 0x7F:
            {
                spdlog::info("LD A, A {:X}", opcode);
                LD_instructions::LD_1B_1C(&(this->registers.AF.A),(this->registers.AF.A),&system_status);
            //     this -> registers.AF.A = this -> registers.AF.A;
            //    (*PC_value) += 1;
            //    (*cycles) -= 1;
                break;
            }
            case 0x80:
            {
                spdlog::info("ADD A, B {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.BC.B);
                this->check_C_INC(this->registers.AF.A, this->registers.BC.B);
                this->registers.AF.A += this->registers.BC.B;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x81:
            {
                spdlog::info("ADD A, C {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.BC.C);
                this->check_C_INC(this->registers.AF.A, this->registers.BC.C);
                this->registers.AF.A += this->registers.BC.C;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x82:
            {
                spdlog::info("ADD A, D {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.DE.D);
                this->check_C_INC(this->registers.AF.A, this->registers.DE.D);
                this->registers.AF.A += this->registers.DE.D;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x83:
            {
                spdlog::info("ADD A, E {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.DE.E);
                this->check_C_INC(this->registers.AF.A, this->registers.DE.E);
                this->registers.AF.A += this->registers.DE.E;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x84:
            {
                spdlog::info("ADD A, H {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.HL.H);
                this->check_C_INC(this->registers.AF.A, this->registers.HL.H);
                this->registers.AF.A += this->registers.HL.H;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x85:
            {
                spdlog::info("ADD A, L {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.HL.L);
                this->check_C_INC(this->registers.AF.A, this->registers.HL.L);
                this->registers.AF.A += this->registers.HL.L;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x86:
            {
                spdlog::info("ADD A, (HL) {:X}", opcode);
                u_int8_t value = this->memory.read_8_bit(this->registers.HL_double);
                this->check_H_8_INC(this->registers.AF.A, value);
                this->check_C_INC(this->registers.AF.A, value);
                this->registers.AF.A += value;
                this->check_if_result_zero(this->registers.AF.A);
            }
            case 0x87:
            {
                spdlog::info("ADD A, A {:X}", opcode);
                this->check_H_8_INC(this->registers.AF.A, this->registers.AF.A);
                this->check_C_INC(this->registers.AF.A, this->registers.AF.A);
                this->registers.AF.A += this->registers.AF.A;
                this->check_if_result_zero(this->registers.AF.A);
            }
        case 0x88:
        {
            spdlog::info("ADC A, B {:X}", opcode);
            this->check_H_8_INC(this->registers.AF.A, (u_int8_t) (this->registers.BC.B + this->get_flag(FLAG_C)));
            this->check_C_INC(this->registers.AF.A, (u_int8_t) (this->registers.BC.B + this->get_flag(FLAG_C)));
            this->registers.AF.A += (u_int8_t) (this->registers.BC.B + this->get_flag(FLAG_C));
            this->check_if_result_zero(this->registers.AF.A);
        }
    case 0x89:
    {
        spdlog::info("ADC A, C {:X}", opcode);
        this->check_H_8_INC(this->registers.AF.A, (u_int8_t) (this->registers.BC.C + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A, (u_int8_t) (this->registers.BC.C + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (this->registers.BC.C + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }
    case 0x8A:
    {
        spdlog::info("ADC A, D {:X}", opcode);
        this->check_H_8_INC(this->registers.AF.A, (u_int8_t) (this->registers.DE.D + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A, (u_int8_t) (this->registers.DE.D + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (this->registers.DE.D + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }
    case 0x8B:
    {
        spdlog::info("ADC A, E {:X}", opcode);
        this->check_H_8_INC(this->registers.AF.A, (u_int8_t) (this->registers.DE.E + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A, (u_int8_t) (this->registers.DE.E + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (this->registers.DE.E + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }
    case 0x8C:
    {
        spdlog::info("ADC A, H {:X}", opcode);
        this->check_H_8_INC(this->registers.AF.A, (u_int8_t) (this->registers.HL.H + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A, (u_int8_t) (this->registers.HL.H + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (this->registers.HL.H + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }
    case 0x8D:
    {
        spdlog::info("ADC A, L {:X}", opcode);
        this->check_H_8_INC(this->registers.AF.A,(u_int8_t)  (this->registers.HL.L + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A,(u_int8_t)  (this->registers.HL.L + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (this->registers.HL.L + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }
    case 0x8E:
    {
        spdlog::info("ADC A, (HL) {:X}", opcode);
        u_int8_t value = this->memory.read_8_bit(this->registers.HL_double);
        this->check_H_8_INC(this->registers.AF.A,(u_int8_t)  (value + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A,(u_int8_t)  (value + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (value + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }
    case 0x8F:
    {
        spdlog::info("ADC A, A {:X}", opcode);
        this->check_H_8_INC(this->registers.AF.A,(u_int8_t)  (this->registers.AF.A + this->get_flag(FLAG_C)));
        this->check_C_INC(this->registers.AF.A,(u_int8_t)  (this->registers.AF.A + this->get_flag(FLAG_C)));
        this->registers.AF.A += (u_int8_t) (this->registers.AF.A + this->get_flag(FLAG_C));
        this->check_if_result_zero(this->registers.AF.A);
    }













            default:
                break;
            }
         }
  
     }

 
