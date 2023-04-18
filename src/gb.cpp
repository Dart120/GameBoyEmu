#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "gb.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

GB::GB(){
    try 
    {
        auto logger = spdlog::basic_logger_mt("basic_logger", "./logs/basic-log.txt");
        spdlog::set_default_logger(logger);
        spdlog::flush_on(spdlog::level::info);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    this->system_counter = 0;
    this->memory = new Memory(&this->system_counter);
    this->clock = new Clock(*memory,&this->system_counter);
    this->cpu = new CPU(*memory, *this->clock);
}