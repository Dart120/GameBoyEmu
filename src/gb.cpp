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
#include <thread>
using namespace std::chrono;





GB::GB(std::string log_to){
    auto last_sync = std::chrono::high_resolution_clock::now();
    
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
        logger->set_level(spdlog::level::info);
        
       

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
  
    auto start = std::chrono::steady_clock::now();
    while(1){
        
        // std::cout<<"b4 cpu ROWS: " << this->gpu->VP_ROWS << std::endl;
        // std::function<void()> func = [this](){ this->process_t_cycle(); };
        
        this->cpu->FDE();
        SDL_Event e;
    // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                // quit = true;
                exit(0);
            }
        }

        
        // SDL_Delay(1);
        // std::cout<<"after cpu ROWS: " << this->gpu->VP_ROWS << std::endl;
        
        
    }
}
void GB::process_t_cycle(){
    const double t_cycle_time_ns = 238.0; // Nanoseconds per T-cycle
    const int cycles_per_callback = 4;
    const double callback_time_ns = t_cycle_time_ns * cycles_per_callback;
    // std::cout<<"T cycle processed" << std::endl;
    this->system->m_cycles += 1;
    this->system->t_cycles += 4;
    this->gpu->do_4_dots();
    auto now = std::chrono::high_resolution_clock::now();
    double elapsed_ns = std::chrono::duration<double, std::nano>(now - last_sync).count();

    // Calculate expected time for the work done
    double expected_ns = callback_time_ns;

    if (elapsed_ns < expected_ns) {
        // Wait for the remaining time
        std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<int>(expected_ns - elapsed_ns)));
    }

    // Update last sync time
    last_sync = std::chrono::high_resolution_clock::now();


}