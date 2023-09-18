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
#include <map>
// TODO finish this
// TODO Read tile data for objects into a map, this will have tile address as keys and mem addresses as values
GPU::GPU(Memory& memory): memory(memory){
        this->memory = memory;
        this->tiledata = new TileData(*memory);
    }
void GPU::read_tilemaps(){
    this->tiledata.read_tilemaps();
}