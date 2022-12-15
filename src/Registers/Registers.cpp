#include "Registers.h"

    
 
//      template <typename T> void Registers::check_H_8_INC(T a, T b){           
//         if ((((a & 0xf) + (b & 0xf)) & 0x10) == 0x10){
//             this->set_flag(FLAG_H);
//         }
//      }
//      template <typename T> void Registers::check_H_11_INC(T a, T b){
//         if ((((a & 0xfff) + (b & 0xfff)) & 0x800) == 0x800){
//             this->set_flag(FLAG_H);
//         }
//      }
//      template <typename T> void Registers::check_C_15_INC(T a, T b){
//         if ((((a & 0xffff) + (b & 0xffff)) & 0x8000) == 0x8000){
//             this->set_flag(FLAG_C);
//         }
//      }
//      template <typename T> void Registers::check_H_8_SUB(T a, T b){
       
//         if (!((a >> 3) & 1) && ((b >> 3) & 1)){
// this->set_flag(FLAG_H);
//         }
//      }
//      template <typename T> void Registers::check_C_8_ADD(T a, T b){
//         if((((a & 0xf) + (b & 0xf)) & 0x10) == 0x10){
// this->set_flag(FLAG_C);
//         }
//      }
//      template <typename T> void Registers::check_if_result_zero(T result){
//         if (!result){
//             this->set_flag(FLAG_Z);
//         }
//      }
 