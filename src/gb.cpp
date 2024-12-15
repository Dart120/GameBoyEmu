#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include "gb.h"
#include "timer.h"
#include "system_status.h"
#include "modes.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <string>
#include <bitset>
using namespace std::chrono;





GB::GB(std::string log_to){
    // auto last_sync = std::chrono::high_resolution_clock::now();
    
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

    std::function<void()> func2 = [this](){ this->reset_timer(); };
    std::function<void(uint8_t)> func3 = [this](uint8_t data){ this->start_dma(data); };
    
    this->system = new system_status_struct;
    this->system->t_cycles = 0;
    this->system->m_cycles = 0;
    this->memory = new Memory(func2,cycles_left_DMA,GPU_Mode_REF);
    this->gpu = new GPU(*memory, GPU_Mode_REF,2);
    
    // std::cout<<" ROWS: " << this->gpu->VP_ROWS << std::endl;
    this->timer = new Timer(*memory);
    std::function<void()> func = [this](){ this->process_t_cycle(); };
    
    this->cpu = new CPU(*memory,*this->system,func);
}
void GB::go() {
  
    auto start = std::chrono::steady_clock::now();
    while(1){
        
        // std::cout<<"b4 cpu ROWS: " << this->gpu->VP_ROWS << std::endl;
        // std::function<void()> func = [this](){ this->process_t_cycle(); };
        if (cycles_left_DMA){
            if (cycles_left_DMA == 640){
                this->start_dma(this->memory->read_8_bit(0xFF46));
            }
            this->timer->process_4t_cycles();
            this->gpu->do_4_dots();
            
            cycles_left_DMA -= 4;
        } else {
            this->cpu->FDE();
        }

        
        
        SDL_Event e;
    // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                // quit = true;
                exit(0);
            }
            switch( e.type ){
                case SDL_KEYDOWN:
                    std::cout<<"key pressed"<<std::endl;
                    switch( e.key.keysym.sym ){
                        case SDLK_LEFT:
                        std::cout<<"left pressed"<<std::endl;
                            dir_keys.insert(1);
                            break;
                        case SDLK_RIGHT:
                            dir_keys.insert(0);
                            break;
                        case SDLK_UP:
                            dir_keys.insert(2);
                            break;
                        case SDLK_DOWN:
                            dir_keys.insert(3);
                            break;
                        case SDLK_a:
                            but_keys.insert(0);
                            break;
                        case SDLK_s:
                            but_keys.insert(1);
                            break;
                        case SDLK_z:
                            but_keys.insert(2);
                            break;
                        case SDLK_x:
                            but_keys.insert(3);
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch( e.key.keysym.sym ){
                        case SDLK_LEFT:
                            dir_keys.erase(1);
                            break;
                        case SDLK_RIGHT:
                            dir_keys.erase(0);
                            break;
                        case SDLK_UP:
                            dir_keys.erase(2);
                            break;
                        case SDLK_DOWN:
                            dir_keys.erase(3);
                            break;
                        case SDLK_a:
                            but_keys.erase(0);
                            break;
                        case SDLK_s:
                            but_keys.erase(1);
                            break;
                        case SDLK_z:
                            but_keys.erase(2);
                            break;
                        case SDLK_x:
                            but_keys.erase(3);
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
                }

        }
        this->memory->mem[0xFF00] |= 0x0F;

        // std::cout<<  std::bitset<8>(this->memory->mem[0xFF00]) <<" dir key registering "<<std::endl;
        if(!this->memory->get_bit_from_addr(0xFF00,4)){
            // std::cout<<"dir key registering"<<std::endl;
            
            for (uint8_t bit: dir_keys){
                std::cout<<"clear dir "<< (int) bit<<std::endl;
                this->memory->clear_bit_from_addr(0xFF00,bit);
            }
        } else if (!this->memory->get_bit_from_addr(0xFF00,5)){
            for (uint8_t bit: but_keys){
                std::cout<<"clear but "<< (int) bit<<std::endl;
                this->memory->clear_bit_from_addr(0xFF00,bit);
            }
        }

        
        // SDL_Delay(1);
        // std::cout<<"after cpu ROWS: " << this->gpu->VP_ROWS << std::endl;
        
        
    }
}
void GB::process_t_cycle(){
    this->timer->process_4t_cycles();
    // const double t_cycle_time_ns = 238.0; // Nanoseconds per T-cycle
    // const int cycles_per_callback = 4;
    // const double callback_time_ns = t_cycle_time_ns * cycles_per_callback;
    // std::cout<<"T cycle processed" << std::endl;
 
    this->gpu->do_4_dots();

    // auto now = std::chrono::high_resolution_clock::now();
    // double elapsed_ns = std::chrono::duration<double, std::nano>(now - last_sync).count();

    // // Calculate expected time for the work done
    // double expected_ns = callback_time_ns;

    // if (elapsed_ns < expected_ns) {
    //     // Wait for the remaining time
    //     std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<int>(expected_ns - elapsed_ns)));
    // }

    // // Update last sync time
    // last_sync = std::chrono::high_resolution_clock::now();
}
void GB::reset_timer(){
    this->timer->reset_timer();
}
void GB::start_dma(uint8_t data){
    
    uint16_t start = data * 0x100;
    uint16_t end = (data * 0x100) + 0x9F;
    uint16_t start_oam = 0xFE00;
    while (start <= end){
        this->memory->write_8_bit(start_oam,this->memory->read_8_bit(start));
        start_oam++;
        start++;
    }
    cycles_left_DMA = 640;
    
}