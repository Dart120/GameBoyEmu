#include "LD.h"
#include<iostream>
template<class F>
void LD_instructions<F>::LD_1B_2C(u_int16_t* address, u_int8_t* value){

}
template<class F>
void LD_instructions<F>::LD_1B_1C(u_int8_t* into, u_int8_t* load){
    // *into = *load;
    // PC_value += 1;
    // cycles -= 1;
    // break;
}
template<class F>
void LD_instructions<F>::LD_2B_2C(u_int8_t* into, u_int8_t* immediate){

}
template<class F>
void LD_instructions<F>::LD_3B_5C(u_int8_t* immediate, u_int16_t* SP){

}
template<class F>
void LD_instructions<F>::increment_HL(u_int8_t* HL, F then){

}
