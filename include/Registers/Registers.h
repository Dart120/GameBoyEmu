
#ifndef RegisterFunctions_H
#define RegisterFunctions_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include <stdint.h>
#include <vector>
#define FLAG_Z 7                //00001111
#define FLAG_N 6                //0000CHNZ
#define FLAG_H 5                //00004567
#define FLAG_C 4 
enum register_index {AF,BC,DE,HL,SP,PC};
class Registers{
    
    public:
    bool IME;
     struct registers{
        union{
            struct{
                uint8_t A;
                uint8_t F;
            } AF;
            uint16_t AF_double;
        };
        union{
            struct{
                uint8_t B;
                uint8_t C;
            } BC;
            uint16_t BC_double;
        };
        union{
            struct{
                uint8_t D;
                uint8_t E;
            } DE;
            uint16_t DE_double;
        };
        union{
            struct{
                uint8_t H;
                uint8_t L;
            } HL;
            uint16_t HL_double;
        };
        uint16_t SP;
        uint16_t PC;
    } registers;
  
  
    int set_flag(int index){                       //set flag sets corresponding flag to true i.e. 1
        this->registers.AF.F |= 1UL << index;
        return 1;
     }
     bool  get_flag(int index){
        bool bit = (this->registers.AF.F >> index) & 1UL;
        return bit;
     }
     int  clear_flag(int index){                    //clear flag sets corresponding flag to false i.e. 0
        this->registers.AF.F = ~(~(this->registers.AF.F) | 1UL << index);
        return 1;
     }

    template <typename T> void  check_H_8_ADD(T a, T b){  
        // This doesn't work as it ignores what occures before the bit in question, it might be 0         
        // if (((a >> 3) & 1)  && ((b >> 3) & 1)){
        //     this->set_flag(FLAG_H);
        // }
        if ((((a & 0xf) + (b & 0xf)) & 0x10) == 0x10){
            this->set_flag(FLAG_H);
        }
     }
    template <typename T> void  check_H_8_SUB(T a, T b){
       
        if (((a | 0xff) - (b & 0xf)) & 0x10 == 0x10){
            this->set_flag(FLAG_H);
        }
     }
    // template <typename T> void  check_H_8_INC(T a, T b){  
    //     // This doesn't work as it ignores what occures before the bit in question, it might be 0         
    //     // if (((a >> 3) & 1)  && ((b >> 3) & 1)){
    //     //     this->set_flag(FLAG_H);
    //     // }
    //     if ((((a & 0xf) + (b & 0xf)) & 0x10) == 0x10){
    //         this->set_flag(FLAG_H);
    //     }
    //  }

     template <typename T> void  check_H_16_INC(T a, T b){
        if ((((a & 0xfff) + (b & 0xfff)) & 0x800) == 0x800){
            this->set_flag(FLAG_H);
        }
     }
     template <typename T> void  check_C_15_INC(T a, T b){
        if ((((a & 0xffff) + (b & 0xffff)) & 0x8000) == 0x8000){
            this->set_flag(FLAG_C);
        }
     }

     template <typename T> void  check_C_8_ADD(T a, T b){
        a = (uint16_t) a;
        b = (uint16_t) b;
        if((((a & 0xff) + (b & 0xff)) & 0x100) == 0x100){
            this->set_flag(FLAG_C);
        }
     }
     template <typename T> void  check_C_8_SUB(T a, T b){
        a = (uint16_t) a;
        b = (uint16_t) b;
        if (((a | 0xffff) - (b & 0xff)) & 0x200 == 0x200){
            this->set_flag(FLAG_C);
        }
     }
     template <typename T> void  check_if_result_zero(T result){
        if (!result){
            this->set_flag(FLAG_Z);
        }
     }
    // uint16_t read_double_register(register_index index);

        std::vector<int>  num_to_list(int num){
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
     int set_registers(){
        this->registers.AF_double = 0xB001;
        this->registers.BC_double = 0x1300;
        this->registers.DE_double = 0xD800;
        this->registers.HL_double = 0x4D01;
        this->registers.PC = 0x0100;
        this->registers.SP = 0xFFFE;
        return 1;
    }

};
#endif