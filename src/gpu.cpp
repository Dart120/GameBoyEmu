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

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
GPU::GPU(Memory& memory): memory(memory),tiledata(memory),background(memory,tiledata){
        // this->memory = memory;
        // this->tiledata = tiledata;
        // this->background = new Background(&memory,&tiledata);
    }
void GPU::read_tiledata(){
    this->tiledata.read_tiledata();
}