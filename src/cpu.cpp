#include<iostream>
#include "Registers.h"
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
    CPU::CPU(Memory memory, Registers registers){
        this->memory = memory;
        this->registers = registers;
        memset(this->memory.mem,5,65536);
        this->memory.mem[0] = 0;
    }

     void CPU::FDE(){
         uint32_t cycles = 69905;
         while (cycles){
            spdlog::info("PC Value: {:X} read",this->registers.registers.PC);
            uint8_t opcode = this->memory.mem[this->registers.registers.PC];
            spdlog::info("Opcode: {:X} read", opcode);
            switch (opcode)
            {
            case 0x00:
                {spdlog::info("NOP {:X}", opcode);
                this->registers.registers.PC += 1;
               (cycles)--;
               (this->registers.registers.PC) += 1;
                break;}
            // case 0x10:
            // // NOT IMPLEMENTED STOP
            //     {spdlog::info("STOP {:X}", opcode);
            //    (cycles)--;
            //     break;}
            // case 0x20:
            //     {spdlog::info("JR NZ, s8 {:X}", opcode);
            //    (cycles)--;
            //     break;}
            // case 0x40:
            //     {spdlog::info("LD B,B {:X}", opcode);
            //     this -> registers.registers.BC.B = this->registers.registers.BC.B;
            //    (cycles)--;
            //     break;}
            // case 0x50:
            //     {spdlog::info("LD D, B {:X}", opcode);
            //     this -> registers.registers.BC.B = this ->registers.DE.D;
            //    (cycles)--;

                // // this -> registers.registers.BC.B = this->memory.mem[this->registers.registers.HL_double];

                // break;}
            case 0x01:
              {  spdlog::info("LD BC, d16 {:X}", opcode);
                 this->LD_3B_3C(&(this -> registers.registers.BC_double),&cycles);
            //     this -> registers.registers.BC_double = this -> memory.read_16_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 3;
            //    (cycles) =(cycles) - 3;
                break;}
        
            case 0x02:
                {spdlog::info("LD (BC), A {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this -> registers.registers.BC_double),(this -> registers.registers.AF.A),&cycles);
            //     this->memory.write_8_bit(this->registers.registers.BC_double, this->registers.registers.AF.A);
            //    (this->registers.registers.PC) += 1;
            //    (cycles) =(cycles) - 2;
                break;}
              
            case 0x03:
                {spdlog::info("INC BC {:X}", opcode);
                this->INC_16_BIT(&this->registers.registers.BC_double,&cycles);
                break;
                }
             
            case 0x04:
            {    spdlog::info("INC B {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.BC.B,&cycles);
                break;}
            case 0x05:
                {spdlog::info("DEC B {:X}", opcode);
                this->DEC_8_BIT(&this->registers.registers.BC.B,&cycles);
                break;}


            case 0x06:
            {    spdlog::info("LD B, d8 {:X}", opcode);
                this->LD_2B_2C(&(this -> registers.registers.BC.B),&cycles);
            //     this -> registers.registers.BC.B = this -> memory.read_8_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;}

            case 0x07:
                {spdlog::info("RLCA {:X}", opcode);
                bool lastValue = this -> registers.registers.AF.A >> 7 & 1UL;
                this -> registers.registers.AF.A = this -> registers.registers.AF.A << 1;
                if (lastValue){
                    this -> registers.registers.AF.A++;
                    this -> registers.set_flag(FLAG_C);
                }else{
                    this->registers.clear_flag(FLAG_C);
                }
                this->registers.check_if_result_zero(this -> registers.registers.AF.A);
                this->registers.clear_flag(FLAG_N);
                this->registers.clear_flag(FLAG_H);
               (cycles)++;
               (this->registers.registers.PC) += 1;
                break;}
               
            case 0x08:
                // The stack grows down
                // in other words the least significant byte is first in memory. This scheme is known as little-endian and its opposite is known as big-endian.
                {spdlog::info("LD (a16), SP {:X}", opcode);
                this->LD_3B_5C(&(this -> registers.registers.SP), &cycles);
            //     this -> memory.write_16_bit(this->registers.registers.PC + 1,(*this->memory.SP));
            //    (cycles) -= 2;
            //    (this->registers.registers.PC) += 3;
                break;}
            case 0x09:
            // Fix with info from manual, then go down
                {spdlog::info("ADD HL, BC {:X}", opcode);
                this->ADD_1B_2C_16Bit(&this->registers.registers.HL_double,this->registers.registers.BC_double,&cycles);
                break;}
            
            case 0x0A:
            {   
                spdlog::info("LD A, (BC) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this -> registers.registers.BC_double),&(this -> registers.registers.AF.A),&cycles);
            //     this->registers.registers.AF.A = memory.read_8_bit(this->registers.registers.BC_double);
            //    (cycles) -= 2;
            //    (this->registers.registers.PC) += 1;
                break;
            }

            case 0x0B:                                  
            {
                spdlog::info("DEC BC {:X}", opcode);
                this->DEC_16_BIT(&this->registers.registers.BC_double,&cycles);
                break;     
            }

            case 0x0C:                  //increment contents of register C by 1
            {
                spdlog::info("INC C {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.BC.C,&cycles);
                break;
                
            }

            case 0x0D:
            {
                spdlog::info("DEC C {:X}", opcode);
                this->DEC_8_BIT(&this->registers.registers.BC.C,&cycles);
                break;
            }

            case 0x0E:
            {
                spdlog::info("LD C, d8 {:X}", opcode);
                this->LD_2B_2C(&(this -> registers.registers.BC.C),&cycles);
            //     this -> registers.registers.BC.C = memory.read_8_bit(this->registers.registers.PC + 1 );
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;
            }

            case 0x0F:
            {
                spdlog::info("RRCA {:X}", opcode);
                bool firstValue = this -> registers.registers.AF.A & 1UL;
                this -> registers.registers.AF.A = this -> registers.registers.AF.A >> 1;
                if (firstValue){
                    this->registers.registers.AF.A |= 1UL << 7;
                    this -> registers.set_flag(FLAG_C);
                }else{
                    this->registers.clear_flag(FLAG_C);
                }
                this->registers.check_if_result_zero(this -> registers.registers.AF.A);
                this->registers.clear_flag(FLAG_N);
                this->registers.clear_flag(FLAG_H);
               (this->registers.registers.PC) += 1;
               (cycles)++;
                break;
            }

            case 0x10:
            {
                spdlog::info("STOP {:X} read", opcode);
                exit(0);
               (cycles)--;
               (this->registers.registers.PC) += 2;
                break;
            }

            case 0x11:
            {
                spdlog::info("LD DE, d16 {:X}", opcode);
                this->LD_3B_3C(&(this -> registers.registers.DE_double),&cycles);
            //     this -> registers.registers.DE_double = this -> memory.read_16_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 3;
            //    (cycles) -= 3;
                break;
            }

            case 0x12:
            {
                spdlog::info("LD (DE), A {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this -> registers.registers.DE_double),this->registers.registers.AF.A,&cycles);
            //     this -> memory.write_8_bit(this -> registers.registers.DE_double, this -> registers.registers.AF.A);
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x13:
            {
                spdlog::info("INC DE {:X}", opcode);
                this->INC_16_BIT(&this->registers.registers.DE_double,&cycles);
                break;
            }
             case 0x14:
            {
                spdlog::info("INC D {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.DE.D,&cycles);
                break;
            }

            case 0x15:
            {
                spdlog::info("DEC D {:X}", opcode);
                this->DEC_8_BIT(&this->registers.registers.DE.D,&cycles);
                break;
            }

            case 0x16:
            {
                spdlog::info("LD D, d8 {:X}", opcode);
                this->LD_2B_2C(&(this -> registers.registers.DE.D),&cycles);
            //     this -> registers.registers.DE.D = this -> memory.read_8_bit(this->registers.registers.PC +1);
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;
            }

            case 0x17:
            {
                spdlog::info("RLA {:X}", opcode);
                this -> registers.registers.AF.A = this -> registers.registers.AF.A<< 1;
                if(this -> registers.get_flag(FLAG_C)){
                   this -> registers.registers.AF.A |= 1UL;
                   
                }
                
                this -> registers.check_if_result_zero(this -> registers.registers.AF.A);
                this -> registers.clear_flag(FLAG_N);
                this -> registers.clear_flag(FLAG_H);
               (this->registers.registers.PC) += 1;
               (cycles) -= 1;
                break;
            }

            case 0x18:
            {
                spdlog::info("JR s8 {:X}", opcode);
                
               (this->registers.registers.PC) += this -> memory.read_8_bit(this->registers.registers.PC + 1);
               (cycles) += 3;  
                break;
            }

            case 0x19:
            {
                spdlog::info("ADD HL, DE {:X}", opcode);
                this->ADD_1B_2C_16Bit(&this->registers.registers.HL_double,this->registers.registers.DE_double,&cycles);
                break;
            }

            case 0x1A:
            {
                spdlog::info("LD A, (DE) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this -> registers.registers.DE_double),&(this->registers.registers.AF.A),&cycles);
            //     this -> registers.registers.AF.A = memory.read_8_bit(this -> registers.registers.DE_double);
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x1B:
            {
                spdlog::info("DEC DE {:X}", opcode);
                this->DEC_16_BIT(&this->registers.registers.DE_double,&cycles);
                break;
            }

            case 0x1C:
            {
                spdlog::info("INC E {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.DE.E,&cycles);
                break;
            }

            case 0x1D:
            {
                spdlog::info("DEC E {:X}", opcode);
                this->DEC_8_BIT(&this->registers.registers.DE.E,&cycles);
                break;
            }

            case 0x1E:
            {
                spdlog::info("LD E, d8 {:X}", opcode);
                this->LD_2B_2C(&(this -> registers.registers.DE.E),&cycles);
            //     this -> registers.registers.DE.E = memory.read_8_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;
            }

            case 0x1F:
            {
                spdlog::info("RRA {:X}", opcode);
                
                this -> registers.registers.AF.A = this -> registers.registers.AF.A >> 1;
                if(this->registers.get_flag(FLAG_C)){
                    this -> registers.registers.AF.A |= 1L;
                }

                this->registers.clear_flag(FLAG_H);
                this->registers.clear_flag(FLAG_N);
                this -> registers.check_if_result_zero(this -> registers.registers.AF.A);
               (this->registers.registers.PC) += 1;
               (cycles) -= 1;
                break;
            }
            
            

            
            case 0x20:
            {
                spdlog::info("JR NZ, s8 {:X}", opcode);
                if (!this->registers.get_flag(FLAG_Z)){
                   (this->registers.registers.PC) += this->memory.read_8_bit(this->registers.registers.PC + 1);
                   (cycles) += 3;
                } else {
                   (this->registers.registers.PC)++;
                   (cycles) += 2;
                }
            }
              case 0x21:
              {  spdlog::info("LD HL, d16 {:X}", opcode);
                this->LD_3B_3C(&(this -> registers.registers.HL_double),&cycles);
            //     this -> registers.registers.HL_double = this -> memory.read_16_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 3;
            //    (cycles) =(cycles) - 3;
                break;}
            case 0x22:
                {spdlog::info("LD (HL+), A {:X}", opcode);
                this->increment_HL(&(this -> registers.registers.HL_double));
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this -> registers.registers.AF.A),&cycles);
                
            //     this->memory.write_8_bit(this->registers.registers.HL_double, this->registers.registers.AF.A);
            //     this->registers.registers.HL_double++;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) =(cycles) - 2;
                break;}
            case 0x23:
                {spdlog::info("INC HL {:X}", opcode);
                this->INC_16_BIT(&this->registers.registers.HL_double,&cycles);
                break;}
            case 0x24:
            {    spdlog::info("INC H {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.HL.H,&cycles);
                break;}
            case 0x25:
                {
                    spdlog::info("DEC H {:X}", opcode);
                    this->DEC_8_BIT(&this->registers.registers.HL.H,&cycles);
                    break;
                }
            case 0x26:
            {    spdlog::info("LD H, d8 {:X}", opcode);
           
                this->LD_2B_2C(&(this->registers.registers.HL.H),&cycles);
            //     this -> registers.registers.HL.H = this -> memory.read_8_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;}
            case 0x27:
                {spdlog::info("DAA {:X}", opcode);
                std::vector<int> digits = this->registers.num_to_list(this->registers.registers.AF.A);
                reverse(digits.begin(),digits.end());
                if (this->registers.get_flag(FLAG_N)){
                    if (digits[0] > 9 || this->registers.get_flag(FLAG_C)){
                        digits[0] -= 6; 
                    }
                    if (digits[1] > 9 || this->registers.get_flag(FLAG_H)){
                        digits[1] -= 6; 
                    }
                }else{
                    if (digits[0] > 9 || this->registers.get_flag(FLAG_C)){
                        digits[0] += 6; 
                    }
                    if (digits[1] > 9 || this->registers.get_flag(FLAG_H)){
                        digits[1] += 6; 
                    }
                }
                this->registers.registers.AF.A = (digits[0] * 10) + digits[1];
                if (this->registers.registers.AF.A > 0x99){
                    this -> registers.set_flag(FLAG_C);
                }else{
                    this->registers.clear_flag(FLAG_C);
                }
               (cycles)++;
               (this->registers.registers.PC) += 1;
                break;}
            case 0x28:
            {
                if (this->registers.get_flag(FLAG_Z)){
                   (this->registers.registers.PC) += this->memory.read_8_bit(this->registers.registers.PC + 1);
                   (cycles) += 3;
                } else {
                   (this->registers.registers.PC)++;
                   (cycles) += 2;
                }
            }
            case 0x29:
            // Fix with info from manual, then go down
                {
                spdlog::info("ADD HL, HL {:X}", opcode);
                this->ADD_1B_2C_16Bit(&this->registers.registers.HL_double,this->registers.registers.HL_double,&cycles);
                break;
                }

            case 0x2A:
            {   
                spdlog::info("LD A, (HL+) {:X}", opcode);
                this->increment_HL(&(this -> registers.registers.HL_double));
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this -> registers.registers.AF.A),&cycles);
            //     this->registers.registers.HL_double++;
            //     this->registers.registers.AF.A = memory.read_8_bit(this->registers.registers.HL_double);
            //    (cycles) -= 2;
            //    (this->registers.registers.PC) += 1;
                break;
            }
            case 0x2B:                                  
            {
                spdlog::info("DEC HL {:X}", opcode);
                this->DEC_16_BIT(&this->registers.registers.HL_double,&cycles);    
                break;     
            }
            case 0x2C:                  //increment contents of register C by 1
            {
                spdlog::info("INC L {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.HL.L,&cycles);
                break;
                
            }

            case 0x2D:
            {
                spdlog::info("DEC L {:X}", opcode);
                this->DEC_8_BIT(&this->registers.registers.HL.L,&cycles);
                break;
            }

             case 0x2E:
            {
                spdlog::info("LD L, d8 {:X}", opcode);
                this->LD_2B_2C(&(this -> registers.registers.HL.L),&cycles);
            //     this -> registers.registers.HL.L = memory.read_8_bit(this->registers.registers.PC + 1 );
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;
            }

            case 0x2F:
            {
                spdlog::info("CPL {:X}", opcode);
                this->registers.registers.AF.A = ~this->registers.registers.AF.A;
                this -> registers.set_flag(FLAG_N);
                this -> registers.set_flag(FLAG_H);
               (this->registers.registers.PC) += 1;
               (cycles)++;
                break;
            }

            case 0x30:
            {
                spdlog::info("JR NC s8 {:X}", opcode);
                if (!this -> registers.get_flag(FLAG_C)){
                   (this->registers.registers.PC) += this -> memory.read_8_bit(this->registers.registers.PC + 1);
                   (cycles) += 3;
                } else{
                   (this->registers.registers.PC)++;
                   (cycles) += 2;
                }
            }

            case 0x31:
            {
                spdlog::info("LD SP, d16 {:X}", opcode);
                this->LD_3B_3C(&(this -> registers.registers.SP),&cycles);
            //     this -> registers.registers.SP = this -> memory.read_16_bit(this->registers.registers.PC +1);
            //    (this->registers.registers.PC) += 3;
            //    (cycles) -= 3;
                break;
            }

            case 0x32:
            {
                spdlog::info("LD (HL-), A {:X}", opcode);
                this->decrement_HL(&(this -> registers.registers.HL_double));
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this -> registers.registers.AF.A),&cycles);
            //     this -> memory.write_8_bit(this -> registers.registers.HL_double, this -> registers.registers.AF.A);
            //     this -> registers.registers.HL_double--;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }


            case 0x33:
            {
                spdlog::info("INC SP {:X}", opcode);
                this->INC_16_BIT(&this->registers.registers.SP,&cycles); 
                break;
            }

            // case 0x34:
            // {
            //     spdlog::info("INC (HL) {:X}", opcode);
            //     this->INC_8_BIT(this->memory.read_8_bit(this->registers.registers.HL_double),&cycles);
            //     break;
            // }

            case 0x35:
            {
                spdlog::info("DEC (HL) {:X}", opcode);
                // this -> registers.check_H_8_DEC(this -> registers.registers.HL, (uint8_t) 1); ERRORS HERE
                // char result = --this -> registers.registers.HL;                      ERRORS HERE
                //this -> registers.check_if_result_zero(result);
                this -> registers.clear_flag(FLAG_N);
               (this->registers.registers.PC) += 1;
               (cycles) -= 3;
                break;
            }

            case 0x36:
            {
                spdlog::info("LD (HL), d8 {:x}", opcode);
                this->LD_2B_3C((this->registers.registers.HL_double),&cycles);
                //this -> registers.registers.HL = this -> memory.read_8_bit(this->registers.registers.PC + 1);    
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 3;
                break;
            }

            case 0x37:
            {
                spdlog::info("SCF {:X}", opcode);
                this -> registers.set_flag(FLAG_C);
            }

            case 0x38:
            {
                spdlog::info("JR C, s8 {:X}", opcode);
                if (this -> registers.get_flag(FLAG_C)){
                   (this->registers.registers.PC) += this -> memory.read_8_bit(this->registers.registers.PC + 1);
                   (cycles) += 3;
                } else{
                   (this->registers.registers.PC) ++;
                   (cycles) += 2;
                }
            }
                

            case 0x39:
            {
                spdlog::info("ADD HL, SP {:X}", opcode);
                this->ADD_1B_2C_16Bit(&this->registers.registers.HL_double,this->registers.registers.SP,&cycles);
                break;
            }

            case 0x3A:
            {
                spdlog::info("LD A, (HL-) {:X}", opcode);
                this->decrement_HL(&(this->registers.registers.HL_double));
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this->registers.registers.AF.A),&cycles);
            //     this -> registers.registers.HL_double--;
            //     this -> registers.registers.AF.A = memory.read_8_bit(this -> registers.registers.HL_double);
            //    (cycles) -= 2;
            //    (this->registers.registers.PC) += 1;
                break;
            }

            case 0x3B:
            {
                spdlog::info("DEC SP {:x}", opcode);
               this->DEC_16_BIT(&this->registers.registers.SP,&cycles);
                break;
            }

            case 0x3c:
            {
                spdlog::info("INC A {:X}", opcode);
                this->INC_8_BIT(&this->registers.registers.AF.A,&cycles);
                break;
            }

            case 0x3D:
            {
                spdlog::info("DEC A {:x}", opcode);
                this->DEC_8_BIT(&this->registers.registers.AF.A,&cycles);
                break;
            }

            case 0X3E:
            {
                spdlog::info("LD A, d8 {:X}", opcode);
                this->LD_2B_2C(&(this->registers.registers.AF.A) ,&cycles );
            //     this -> registers.registers.AF.A = memory.read_8_bit(this->registers.registers.PC + 1);
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;   
            }

            case 0x3F:
            {
                spdlog::info("CCF {:X}", opcode);
                this -> registers.clear_flag(FLAG_N);
                this -> registers.clear_flag(FLAG_H);
               // this -> ~set_flag(FLAG_C);            ONLY ERROR WHERE IM LIKE AIGHT FAIR ENOUGH, IDK IF I CAN DO THIS TO FLIP CARRY FLAG
            //    You can, if the bit is set then clear it if the bit is clear then set it
               (this->registers.registers.PC) += 1;
               (cycles) -= 1;
            }












            case 0x40:
            {   
                spdlog::info("LD B, B {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.BC.B),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x41:
            {   
                spdlog::info("LD B, C {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.BC.C),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.BC.C;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x42:
            {   
                spdlog::info("LD B, D {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.DE.D),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.DE.D;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x43:
            {   
                spdlog::info("LD B, E {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.DE.E),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.DE.E;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x44:
            {   
                spdlog::info("LD B, H {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.HL.H),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x45:
            {   
                spdlog::info("LD B, L {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.HL.L),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.HL.L;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x46:
            {   
                spdlog::info("LD B, (HL) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this->registers.registers.BC.B),&cycles  );
            //     this -> registers.registers.BC.B = this->read_8_bit(this->registers.registers.HL_double);
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }
            case 0x47:
            {   
                spdlog::info("LD B, A {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.B),(this->registers.registers.AF.A),&cycles );
            //     this -> registers.registers.BC.B = this -> registers.registers.AF.A;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x48:
            {   
                spdlog::info("LD C, B {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.BC.B),&cycles );
            //     this -> registers.registers.BC.C = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x49:
            {   
                spdlog::info("LD C, C {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.BC.C),&cycles );
            //     this -> registers.registers.BC.C = this -> registers.registers.BC.C;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x4A:
            {   
                spdlog::info("LD C, D {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.DE.D),&cycles );
            //     this -> registers.registers.BC.C = this -> registers.registers.DE.D;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x4B:
            {   
                spdlog::info("LD C, E {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.DE.E),&cycles );
            //     this -> registers.registers.BC.C = this -> registers.registers.DE.E;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x4C:
            {   
                spdlog::info("LD C, H {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.HL.H),&cycles );
            //     this -> registers.registers.BC.C = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x4D:
            {   
                spdlog::info("LD C, L {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.HL.L),&cycles );
            //     this -> registers.registers.BC.C = this -> registers.registers.HL.L;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x4E:
            {   
                spdlog::info("LD C, (HL) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this->registers.registers.BC.C),&cycles  );
            //     this -> registers.registers.BC.B = this->read_8_bit(this->registers.registers.HL_double);
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x4F:
            {   
                spdlog::info("LD C, A {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.BC.C),(this->registers.registers.AF.A),&cycles );
            //     this -> registers.registers.BC.C= this -> registers.registers.AF.A;
            //    (this->registers.registers.PC) += 2;
            //    (cycles) -= 2;
                break;
            }

            case 0x50:
            {
                spdlog::info("LD D, B {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.BC.B),&cycles );
            //     this -> registers.registers.DE.D = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x51:
            {
                spdlog::info("LD D, C {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.BC.C),&cycles );
            //     this -> registers.registers.DE.D = this -> registers.registers.BC.C;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x52:
            {
                spdlog::info("LD D, D {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.DE.D),&cycles );

            //     this -> registers.registers.DE.D = this -> registers.registers.DE.D;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x53:
            {
                spdlog::info("LD D, E {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.DE.E),&cycles );
            //     this -> registers.registers.DE.D = this -> registers.registers.DE.E;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x54:
            {
                spdlog::info("LD D, H {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.HL.H),&cycles );
            //     this -> registers.registers.DE.D = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x55:
            {
                spdlog::info("LD D, L {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.HL.L),&cycles );
            //     this -> registers.registers.DE.D = this -> registers.registers.HL.L;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x56:
            {
                spdlog::info("LD D, (HL) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this->registers.registers.DE.D),&cycles  );
            //     this -> registers.registers.DE.D = this -> registers.registers.HL_double;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x57:
            {
                spdlog::info("LD D, A {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.D),(this->registers.registers.AF.A),&cycles );
            //     this -> registers.registers.DE.D = this -> registers.registers.AF.A;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x58:
            {
                spdlog::info("LD E, B {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.BC.B),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x59:
            {
                spdlog::info("LD E, C {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.BC.C),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.BC.C;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x5A:
            {
                spdlog::info("LD E, D {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.DE.D),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.DE.D;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x5B:
            {
                spdlog::info("LD E, E {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.DE.E),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.DE.E;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x5C:
            {
                spdlog::info("LD E, H {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.HL.H),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x5D:
            {
                spdlog::info("LD E, L {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.HL.L),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.HL.L;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x5E:
            {
                spdlog::info("LD E, (HL) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this->registers.registers.DE.E),&cycles  );
            //     this -> registers.registers.DE.E = this -> registers.registers.HL_double;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }


            case 0x5F:
            {
                spdlog::info("LD E, A {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.DE.E),(this->registers.registers.AF.A),&cycles );
            //     this -> registers.registers.DE.E = this -> registers.registers.AF.A;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }



            case 0x70:
            {
                spdlog::info("LD (HL), B {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.BC.B),&cycles  );
            //     this -> registers.registers.HL_double = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }
            

            case 0x71:
            {
                spdlog::info("LD (HL), C {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.BC.C),&cycles  );
            //     this -> registers.registers.HL_double = this -> registers.registers.BC.C;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x72:
            {
                spdlog::info("LD (HL), D {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.DE.D),&cycles  );

            //     this -> registers.registers.HL_double = this -> registers.registers.DE.D;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x73:
            {
                spdlog::info("LD (HL), D {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.DE.D),&cycles  );

            //     this -> registers.registers.HL_double = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x74:
            {
                spdlog::info("LD (HL), H {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.HL.H),&cycles  );
            //     this -> registers.registers.HL_double = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x75:
            {
                spdlog::info("LD (HL), L {:X}", opcode);
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.HL.L),&cycles  );
            //     this -> registers.registers.HL_double = this -> registers.registers.HL.L;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
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
                this->LD_1B_2C_REG_TO_MEM((this->registers.registers.HL_double),(this->registers.registers.AF.A),&cycles  );
            //     this -> registers.registers.HL_double = this -> registers.registers.AF.A;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 2;
                break;
            }

            case 0x78:
            {
                spdlog::info("LD A, B {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.BC.B),&cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.BC.B;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x79:
            {
                spdlog::info("LD A, C {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.BC.C),&cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.BC.C;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x7A:
            {
                spdlog::info("LD A, D {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.DE.D),&cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.DE.D;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x7B:
            {
                spdlog::info("LD A, E {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.DE.E),&cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.DE.E;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x7C:
            {
                spdlog::info("LD A, H {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.HL.H),&cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x7D:
            {
                spdlog::info("LD A, L {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.HL.L),&cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.HL.H;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x7E:
            {
                spdlog::info("LD A, (HL) {:X}", opcode);
                this->LD_1B_2C_MEM_TO_REG((this->registers.registers.HL_double),&(this->registers.registers.AF.A),&cycles  );
            //     this -> registers.registers.AF.A = this -> registers.registers.HL_double;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }

            case 0x7F:
            {
                spdlog::info("LD A, A {:X}", opcode);
                this->LD_1B_1C(&(this->registers.registers.AF.A),(this->registers.registers.AF.A), &cycles );
            //     this -> registers.registers.AF.A = this -> registers.registers.AF.A;
            //    (this->registers.registers.PC) += 1;
            //    (cycles) -= 1;
                break;
            }
            case 0x80:
            {
                spdlog::info("ADD A, B {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.BC.B, &cycles);
            }
            case 0x81:
            {
                spdlog::info("ADD A, C {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.BC.C, &cycles);
            }
            case 0x82:
            {
                spdlog::info("ADD A, D {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.DE.D, &cycles);
            }
            case 0x83:
            {
                spdlog::info("ADD A, E {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.DE.E, &cycles);
            }
            case 0x84:
            {
                spdlog::info("ADD A, H {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.HL.H, &cycles);
            }
            case 0x85:
            {
                spdlog::info("ADD A, L {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.HL.L, &cycles);
            }
            case 0x86:
            {
                spdlog::info("ADD A, (HL) {:X}", opcode);
                
                this->ADD_1B_2C_8Bit(&this->registers.registers.AF.A,this->memory.read_8_bit(this->registers.registers.HL_double), &cycles);
            }
            case 0x87:
            {
                spdlog::info("ADD A, A {:X}", opcode);
                this->ADD_1B_1C(&this->registers.registers.AF.A,this->registers.registers.AF.F, &cycles);
            }
        case 0x88:
        {
            spdlog::info("ADC A, B {:X}", opcode);
            this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.BC.B, &cycles);
        }
    case 0x89:
    {
        spdlog::info("ADC A, C {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.BC.C, &cycles);
    }
    case 0x8A:
    {
        spdlog::info("ADC A, D {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.DE.D, &cycles);
    }
    case 0x8B:
    {
        spdlog::info("ADC A, E {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.DE.E, &cycles);
    }
    case 0x8C:
    {
        spdlog::info("ADC A, H {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.HL.L, &cycles);
    }
    case 0x8D:
    {
        spdlog::info("ADC A, L {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.HL.L, &cycles);
    }
    case 0x8E:
    {
        spdlog::info("ADC A, (HL) {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->memory.read_8_bit(this->registers.registers.HL_double), &cycles);
    }
    case 0x8F:
    {
        spdlog::info("ADC A, A {:X}", opcode);
        this->ADC_1B_1C(&this->registers.registers.AF.A,this->registers.registers.AF.A, &cycles);
    }













            default:
                break;
            }
         }
  
     }

 
