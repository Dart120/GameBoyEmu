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
// Because it's a little-endian processor you put least significant byte first.
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
                this->ADD_1B_2C_16Bit(this->registers.registers.BC_double,&cycles);
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
                this->JUMP_UNCOND_s8(&cycles);
                break;
            }

            case 0x19:
            {
                spdlog::info("ADD HL, DE {:X}", opcode);
                this->ADD_1B_2C_16Bit(this->registers.registers.DE_double,&cycles);
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
                this->JUMP_ON_COND_s8(!this->registers.get_flag(FLAG_Z), &cycles);
                // if (!this->registers.get_flag(FLAG_Z)){
                //    (this->registers.registers.PC) += this->memory.read_8_bit(this->registers.registers.PC + 1);
                //    (cycles) += 3;
                // } else {
                //    (this->registers.registers.PC)++;
                //    (cycles) += 2;
                // }
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
                spdlog::info("JR s8 {:X}", opcode);
                this->JUMP_UNCOND_s8(&cycles);
            }
            case 0x29:
            // Fix with info from manual, then go down
                {
                spdlog::info("ADD HL, HL {:X}", opcode);
                this->ADD_1B_2C_16Bit(this->registers.registers.HL_double,&cycles);
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
                this->JUMP_ON_COND_s8(!this->registers.get_flag(FLAG_C), &cycles);
                break;
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

            case 0x34:
            {
                spdlog::info("INC (HL) {:X}", opcode);
                this->INC_FROM_MEMORY(this->registers.registers.HL_double,&cycles);
                break;
            }

            case 0x35:
            {
                spdlog::info("DEC (HL) {:X}", opcode);
                this->DEC_FROM_MEMORY(this->registers.registers.HL_double,&cycles);
                break;
            }

            case 0x36:
            {
                spdlog::info("LD (HL), d8 {:x}", opcode);
                this->LD_2B_3C_HL(&cycles);
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
                this->JUMP_ON_COND_s8(this->registers.get_flag(FLAG_C), &cycles);
                break;
            }
                

            case 0x39:
            {
                spdlog::info("ADD HL, SP {:X}", opcode);
                this->ADD_1B_2C_16Bit(this->registers.registers.SP,&cycles);
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
                if (this->registers.get_flag(FLAG_C)){
                    this->registers.clear_flag(FLAG_C);
                }else{
                    this->registers.set_flag(FLAG_C);
                }
                this->registers.clear_flag(FLAG_N);
                this->registers.clear_flag(FLAG_H);
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
                this->ADD_1B_1C(this->registers.registers.BC.B, &cycles);
            }
            case 0x81:
            {
                spdlog::info("ADD A, C {:X}", opcode);
                this->ADD_1B_1C(this->registers.registers.BC.C, &cycles);
            }
            case 0x82:
            {
                spdlog::info("ADD A, D {:X}", opcode);
                this->ADD_1B_1C(this->registers.registers.DE.D, &cycles);
            }
            case 0x83:
            {
                spdlog::info("ADD A, E {:X}", opcode);
                this->ADD_1B_1C(this->registers.registers.DE.E, &cycles);
            }
            case 0x84:
            {
                spdlog::info("ADD A, H {:X}", opcode);
                this->ADD_1B_1C(this->registers.registers.HL.H, &cycles);
            }
            case 0x85:
            {
                spdlog::info("ADD A, L {:X}", opcode);
                this->ADD_1B_1C(this->registers.registers.HL.L, &cycles);
            }
            case 0x86:
            {
                spdlog::info("ADD A, (HL) {:X}", opcode);
                
                this->ADD_1B_2C_8Bit(this->memory.read_8_bit(this->registers.registers.HL_double), &cycles);
            }
            case 0x87:
            {
                spdlog::info("ADD A, A {:X}", opcode);
                this->ADD_1B_1C(this->registers.registers.AF.F, &cycles);
            }
        case 0x88:
        {
            spdlog::info("ADC A, B {:X}", opcode);
            this->ADC_1B_1C(this->registers.registers.BC.B, &cycles);
        }
    case 0x89:
    {
        spdlog::info("ADC A, C {:X}", opcode);
        this->ADC_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0x8A:
    {
        spdlog::info("ADC A, D {:X}", opcode);
        this->ADC_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0x8B:
    {
        spdlog::info("ADC A, E {:X}", opcode);
        this->ADC_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0x8C:
    {
        spdlog::info("ADC A, H {:X}", opcode);
        this->ADC_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0x8D:
    {
        spdlog::info("ADC A, L {:X}", opcode);
        this->ADC_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0x8E:
    {
        spdlog::info("ADC A, (HL) {:X}", opcode);
        this->ADC_1B_1C(this->memory.read_8_bit(this->registers.registers.HL_double), &cycles);
    }
    case 0x8F:
    {
        spdlog::info("ADC A, A {:X}", opcode);
        this->ADC_1B_1C(this->registers.registers.AF.A, &cycles);
    }
    case 0x90:
    {
        spdlog::info("SUB B {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.BC.B, &cycles);
    }
    case 0x91:
    {
        spdlog::info("SUB C {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0x92:
    {
        spdlog::info("SUB D {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0x93:
    {
        spdlog::info("SUB E {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0x94:
    {
        spdlog::info("SUB H {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.HL.H, &cycles);
    }
    case 0x95:
    {
        spdlog::info("SUB L {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0x96:
    {
        spdlog::info("SUB (HL) {:X}", opcode);
        this->SUB_1B_2C(this->registers.registers.HL_double, &cycles);
    }
    case 0x97:
    {
        spdlog::info("SUB A {:X}", opcode);
        this->SUB_1B_1C(this->registers.registers.AF.A, &cycles);
    }
    case 0x98:
    {
        spdlog::info("SBC B {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.BC.B, &cycles);
    }
    case 0x99:
    {
        spdlog::info("SBC C {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0x9A:
    {
        spdlog::info("SBC D {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0x9B:
    {
        spdlog::info("SBC E {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0x9C:
    {
        spdlog::info("SBC H {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.HL.H, &cycles);
    }
    case 0x9D:
    {
        spdlog::info("SBC L {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0x9E:
    {
        spdlog::info("SBC (HL) {:X}", opcode);
        this->SBC_1B_2C(this->registers.registers.HL_double, &cycles);
    }
    case 0x9F:
    {
        spdlog::info("SBC A {:X}", opcode);
        this->SBC_1B_1C(this->registers.registers.AF.A, &cycles);
    }
    case 0xA0:
    {
        spdlog::info("AND B {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.BC.B, &cycles);
    }
    case 0xA1:
    {
        spdlog::info("AND C {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0xA2:
    {
        spdlog::info("AND D {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0xA3:
    {
        spdlog::info("AND E {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0xA4:
    {
        spdlog::info("AND H {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.HL.H, &cycles);
    }
    case 0xA5:
    {
        spdlog::info("AND L {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0xA6:
    {
        spdlog::info("AND (HL) {:X}", opcode);
        this->AND_1B_2C(this->registers.registers.HL_double, &cycles);
    }
    case 0xA7:
    {
        spdlog::info("AND A {:X}", opcode);
        this->AND_1B_1C(this->registers.registers.AF.A, &cycles);
    }
    case 0xA8:
    {
        spdlog::info("XOR B {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.BC.B, &cycles);
    }
    case 0xA9:
    {
        spdlog::info("XOR C {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0xAA:
    {
        spdlog::info("XOR D {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0xAB:
    {
        spdlog::info("XOR E {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0xAC:
    {
        spdlog::info("XOR H {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.HL.H, &cycles);
    }
    case 0xAD:
    {
        spdlog::info("XOR L {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0xAE:
    {
        spdlog::info("XOR (HL) {:X}", opcode);
        this->XOR_1B_2C(this->registers.registers.HL_double, &cycles);
    }
    case 0xAF:
    {
        spdlog::info("XOR A {:X}", opcode);
        this->XOR_1B_1C(this->registers.registers.AF.A, &cycles);
    }
    case 0xB0:
    {
        spdlog::info("OR B {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.BC.B, &cycles);
    }
    case 0xB1:
    {
        spdlog::info("OR C {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0xB2:
    {
        spdlog::info("OR D {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0xB3:
    {
        spdlog::info("OR E {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0xB4:
    {
        spdlog::info("OR H {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.HL.H, &cycles);
    }
    case 0xB5:
    {
        spdlog::info("OR L {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0xB6:
    {
        spdlog::info("OR (HL) {:X}", opcode);
        this->OR_1B_2C(this->registers.registers.HL_double, &cycles);
    }
    case 0xB7:
    {
        spdlog::info("OR A {:X}", opcode);
        this->OR_1B_1C(this->registers.registers.AF.A, &cycles);
    }
    case 0xB8:
    {
        spdlog::info("CP B {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.BC.B, &cycles);
    }
    case 0xB9:
    {
        spdlog::info("CP C {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.BC.C, &cycles);
    }
    case 0xBA:
    {
        spdlog::info("CP D {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.DE.D, &cycles);
    }
    case 0xBB:
    {
        spdlog::info("CP E {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.DE.E, &cycles);
    }
    case 0xBC:
    {
        spdlog::info("CP H {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.HL.H, &cycles);
    }
    case 0xBD:
    {
        spdlog::info("CP L {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.HL.L, &cycles);
    }
    case 0xBE:
    {
        spdlog::info("CP (HL) {:X}", opcode);
        this->CP_1B_2C(this->registers.registers.HL_double, &cycles);
    }
    case 0xBF:
    {
        spdlog::info("CP A {:X}", opcode);
        this->CP_1B_1C(this->registers.registers.AF.A, &cycles);
        
    }
    case 0xC0:
    {
        spdlog::info("RET NZ {:X}", opcode);
        this->RET_COND(!this->registers.get_flag(FLAG_Z),&cycles);
        
    }
    case 0xC1:
    {
        spdlog::info("POP BC {:X}", opcode);
        this->POP(&this->registers.registers.BC_double,&cycles);
        
    }
    case 0xC2:
    {
        spdlog::info("JP NZ, a16 {:X}", opcode);
        this->JUMP_ON_COND_a16(!this->registers.get_flag(FLAG_Z),&cycles);
        
    }
    case 0xC3:
    {
        spdlog::info("JP a16 {:X}", opcode);
        this->JUMP_UNCOND_a16(&cycles);
        
    }
    case 0xC4:
    {
        spdlog::info("CALL NZ, a16 {:X}", opcode);
        this->CALL_COND(!this->registers.get_flag(FLAG_Z),&cycles);
        
    }
    case 0xC5:
    {
        spdlog::info("PUSH BC {:X}", opcode);
        this->PUSH(this->registers.registers.BC_double,&cycles);
        
    }
    case 0xC6:
    {
        spdlog::info("ADD A, d8 {:X}", opcode);
        this->ADD_2B_2C(&cycles);
    }
    case 0xC7:
    {
        spdlog::info("RST 0 {:X}", opcode);
        this->RST_UNCOND(0,&cycles);
    }
    case 0xC8:
    {
        spdlog::info("RST Z {:X}", opcode);
        this->RST_COND(this->registers.get_flag(FLAG_Z),&cycles);
    }
    case 0xC9:
    {
        spdlog::info("RET {:X}", opcode);
        this->RET_UNCOND(&cycles);
    }
    case 0xCA:
    {
        spdlog::info("JP Z, a16 {:X}", opcode);
        this->JUMP_ON_COND_a16(this->registers.get_flag(FLAG_Z),&cycles);
    }
    case 0xCC:
    {
        spdlog::info("CALL Z, a16 {:X}", opcode);
        this->CALL_COND(this->registers.get_flag(FLAG_Z),&cycles);
    }
    case 0xCD:
    {
        spdlog::info("CALL a16 {:X}", opcode);
        this->CALL_UNCOND(&cycles);
    }
    case 0xCE:
    {
        spdlog::info("ADC A, d8 {:X}", opcode);
        this->ADC_2B_2C(&cycles);
    }
    case 0xCF:
    {
        spdlog::info("RST 1 {:X}", opcode);
        this->RST_UNCOND(1,&cycles);
    }
    case 0xD0:
    {
        spdlog::info("RET NC {:X}", opcode);
        this->RET_COND(!this->registers.get_flag(FLAG_C),&cycles);
        
    }
    case 0xD1:
    {
        spdlog::info("POP DE {:X}", opcode);
        this->POP(&this->registers.registers.DE_double,&cycles);
        
    }
    case 0xD2:
    {
        spdlog::info("JP NC, a16 {:X}", opcode);
        this->JUMP_ON_COND_a16(!this->registers.get_flag(FLAG_C),&cycles);
        
    }

    case 0xD4:
    {
        spdlog::info("CALL NC, a16 {:X}", opcode);
        this->CALL_COND(!this->registers.get_flag(FLAG_C),&cycles);
        
    }
    case 0xD5:
    {
        spdlog::info("PUSH DE {:X}", opcode);
        this->PUSH(this->registers.registers.DE_double,&cycles);
        
    }
    case 0xD6:
    {
        spdlog::info("SUB A, d8 {:X}", opcode);
        this->SUB_2B_2C(&cycles);
    }
    case 0xD7:
    {
        spdlog::info("RST 2 {:X}", opcode);
        this->RST_UNCOND(2,&cycles);
    }
    case 0xD8:
    {
        spdlog::info("RST C {:X}", opcode);
        this->RST_COND(this->registers.get_flag(FLAG_C),&cycles);
    }
    case 0xD9:
    { //Needs interrupt for RETI
        spdlog::info("RETI {:X}", opcode);
        this->RET_UNCOND(&cycles);
    }
    case 0xDA:
    {
        spdlog::info("JP C, a16 {:X}", opcode);
        this->JUMP_ON_COND_a16(this->registers.get_flag(FLAG_C),&cycles);
    }
    case 0xDC:
    {
        spdlog::info("CALL C, a16 {:X}", opcode);
        this->CALL_COND(this->registers.get_flag(FLAG_C),&cycles);
    }
    case 0xDE:
    {
        spdlog::info("SBC A, d8 {:X}", opcode);
        this->SBC_2B_2C(&cycles);
    }
    case 0xDF:
    {
        spdlog::info("RST 3 {:X}", opcode);
        this->RST_UNCOND(3,&cycles);
    }
    case 0xE0:
    {
        spdlog::info("LD (a8), A {:X}", opcode);
        
        this->LD_2B_3C_ACC_TO_MEM(&cycles);
    }
    case 0xE1:
    {
        spdlog::info("POP HL {:X}", opcode);
        this->POP(&this->registers.registers.HL_double,&cycles);
        
    }
    case 0xE2:
    {
        spdlog::info("LD (C), A {:X}", opcode);
        uint16_t address = 0xFF00 + this->registers.registers.BC.C;
        this->LD_1B_2C_REG_TO_MEM(address,this->registers.registers.AF.A,&cycles);
        
    }
    case 0xE5:
    {
        spdlog::info("PUSH HL {:X}", opcode);
        this->PUSH(this->registers.registers.HL_double,&cycles);
        
    }
    case 0xE6:
    {
        // Impl SUB d8
        spdlog::info("AND d8 {:X}", opcode);
        this->AND_2B_2C(&cycles);
    }
    case 0xE7:
    {
        spdlog::info("RST 4 {:X}", opcode);
        this->RST_UNCOND(4,&cycles);
    }
    case 0xE8:
    {
       
        spdlog::info("ADD SP, s8 {:X}", opcode);
        this->ADD_2B_4C(&this->registers.registers.SP,&cycles);
    }
    case 0xE9:
    { 
        spdlog::info("JP HL {:X}", opcode);
        this->JUMP_UNCOND_REG(this->registers.registers.HL_double,&cycles);
    }
    case 0xEA:
    {
        // I forgor
        spdlog::info("LD (a16), A {:X}", opcode);
        this->LD_3B_4C_REG_TO_MEM(this->registers.registers.AF.A, &cycles);
        
    }
    case 0xEE:
    {
        spdlog::info("XOR d8 {:X}", opcode);
        this->XOR_2B_2C(&cycles);
    }
    case 0xEF:
    {
        spdlog::info("RST 5 {:X}", opcode);
        this->RST_UNCOND(5,&cycles);
    }
    case 0xF0:
    {
        spdlog::info("LD A, (a8) {:X}", opcode);
        this->LD_2B_3C_MEM_TO_ACC(&cycles);
    }
    case 0xF1:
    {
        spdlog::info("POP AF {:X}", opcode);
        this->POP(&this->registers.registers.AF_double,&cycles);
        
    }
    case 0xF2:
    {
        spdlog::info("LD A, (C) {:X}", opcode);
        uint16_t address = 0xFF00 + this->registers.registers.BC.C;
        this->LD_1B_2C_MEM_TO_REG(address,&this->registers.registers.AF.A,&cycles);
        
    }
    case 0xF3:
    {
        spdlog::info("DI {:X}", opcode);
        // Requires interrupts
        this->PUSH(this->registers.registers.HL_double,&cycles);
        
    }
    case 0xF5:
    {
        spdlog::info("PUSH AF {:X}", opcode);
        this->PUSH(this->registers.registers.AF_double,&cycles);
    }
    case 0xF6:
    {
        spdlog::info("OR d8 {:X}", opcode);
        this->OR_2B_2C(&cycles);
    }
    case 0xF7:
    {
        spdlog::info("RST 6, s8 {:X}", opcode);
        this->RST_UNCOND(6,&cycles);
    }
    case 0xF8:
    { 
        spdlog::info("LD HL, SP+s8 {:X}", opcode);
        this->LD_2B_3C(&cycles);
    }
    case 0xF9:
    {
        spdlog::info("LD SP, HL {:X}", opcode);
        this->LD_1B_2C_REG_TO_REG(&cycles);
    }
    case 0xFA:
    {
        spdlog::info("LD A, (a16)", opcode);
        this->LD_3B_4C_MEM_TO_REG(&this->registers.registers.AF.A,&cycles);
    }
    case 0xFB:
    {
        // TODO implement interrupts
        spdlog::info("EI {:X}", opcode);
        this->RST_UNCOND(5,&cycles);
    }
    case 0xFE:
    {
        spdlog::info("CP d8 {:X}", opcode);
        this->RST_UNCOND(5,&cycles);
    }
    case 0xFF:
    {
        spdlog::info("RST 7 {:X}", opcode);
        this->RST_UNCOND(7,&cycles);
    }















            default:
                break;
            }
         }
  
     }

 
