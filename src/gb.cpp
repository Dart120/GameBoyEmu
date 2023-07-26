#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "gb.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>


GB::GB(std::string log_to){
    try 
    {
        auto logger = spdlog::basic_logger_mt("basic_logger", "./logs/"+log_to+"-basic.txt",true);
        spdlog::set_default_logger(logger);
        spdlog::flush_on(spdlog::level::info);
        // Create file sinks for two separate log files
        auto doctor_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("./logs/"+log_to+".txt", true);
 

        // Create two separate loggers for each file sink
        doctor = std::make_shared<spdlog::logger>("logger1", doctor_sink);
      

        // Set the logger level, e.g., info, warn, error, etc.
        doctor->set_level(spdlog::level::info);
        logger->set_level(spdlog::level::off);
        
       

        // Register the loggers
        spdlog::register_logger(doctor);

        doctor->set_pattern("%v");
        // Log messages to each file separately
        
      
     
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