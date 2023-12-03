#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "gb.h"
#include "system_status.h"
#include "modes.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <chrono>
using namespace std::chrono;





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
    MODES GPU_Mode = OAM_SCAN;
    MODES& GPU_Mode_REF = GPU_Mode;


    this->system = new system_status_struct;
    this->system->t_cycles = 0;
    this->system->m_cycles = 0;
    // System.cycles = 0;
    this->system_counter = 0;
    this->memory = new Memory(*this->system, GPU_Mode_REF);
    this->gpu = new GPU(*memory, GPU_Mode_REF,2);
    
    // std::cout<<" ROWS: " << this->gpu->VP_ROWS << std::endl;
    // this->clock = new Clock();
    std::function<void()> func = [this](){ this->process_t_cycle(); };
    this->cpu = new CPU(*memory,*this->system,func);
}
void GB::go() {
    this->gpu->render();
    auto start = std::chrono::steady_clock::now();
    while(1){
        
        // std::cout<<"b4 cpu ROWS: " << this->gpu->VP_ROWS << std::endl;
        // std::function<void()> func = [this](){ this->process_t_cycle(); };
        
        this->cpu->FDE();
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > 16.7){
          
            this->gpu->render();
            start = std::chrono::steady_clock::now();
        }
        
        // SDL_Delay(1);
        // std::cout<<"after cpu ROWS: " << this->gpu->VP_ROWS << std::endl;
        
        
    }
}
void GB::process_t_cycle(){
    // std::cout<<"T cycle processed" << std::endl;
    this->system->m_cycles += 1;
    this->system->t_cycles += 4;
    this->gpu->do_4_dots();


}