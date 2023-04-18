#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "gpu.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
// TODO finish this
GPU::GPU(Memory& memory): memory(memory){
        this->memory = memory;
        this->bg_1 = std::vector<uint8_t>(1024,0);
        this->bg_2 = std::vector<uint8_t>(1024,0);
  
    }
void GPU::READ_BACKGROUND(uint16_t starting_at){
    for (size_t i = 0; i < 32; i++){
        for (size_t j = 0; j < 32; j++){
            uint16_t address = starting_at + (j * 32) + i;
            if (starting_at == 0x9800){
                this->bg_1[(j * 32) + i] = this->memory.read_8_bit(address);
            } else if (starting_at == 0x9C00){
                this->bg_2[(j * 32) + i] = this->memory.read_8_bit(address);
            } else{
                spdlog::error("Read From Non Existent BG Map {:X}", starting_at);
                exit(1);
            }
        }
    }
}
void GPU::READ_BACKGROUNDS(){
    this->READ_BACKGROUND(0x9800);
    this->READ_BACKGROUND(0x9C00);
    
}