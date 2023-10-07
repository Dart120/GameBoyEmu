#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "gpu.h"
#include "tiledata.h"
#include "memory.h"
#include "background.h"
#include "window.h"
#include "object.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
GPU::GPU(Memory& memory): memory(memory),tiledata(memory),background(memory,tiledata), window(memory,tiledata), object(memory,tiledata) {}
void GPU::read_tiledata(){
    this->memory.mem[0] = 10;
    std::cout <<(int)this->memory.mem[0]<< std::endl;
    this->tiledata.read_tiledata();
    // std::cout << "Address of map gpu: " << &this->tiledata.bg_tile_address_mem_address << std::endl;
    this->background.tile_data_to_colour_map();
    this->window.tile_data_to_colour_map();
    this->object.ingest_objects();
}