#include<iostream>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "display_ctl.h"

#include <SDL2/SDL.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
#include <array>
// void printArray(std::array<unsigned char, 160> a,int n){
// 	for(int i=0;i<n;i++)
//       std::cout<<a[i]<<" ";
//   	std::cout<<std::endl;
// }
// TODO find the tile indexes that produced this
// ly  126  coloured  41
Display_Ctl::Display_Ctl(std::array<std::array<u_int8_t,160>,144>& buffer): buffer(buffer){
//  Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        // return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("SDL White Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 144, 160, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        // return 1;
    }

    // Create renderer
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        // return 1;
    }
    this->texture =  SDL_CreateTexture(this->renderer,
                                SDL_PIXELFORMAT_RGB888,
                                SDL_TEXTUREACCESS_TARGET, 160,
                                144);

}
void Display_Ctl::update(u_int8_t line_n){
 
    int count = 0;
    bool did_draw = false;
    for (int x = 0; x < 160; ++x) {
        uint8_t grayscale = this->buffer[line_n][x];
        grayscale = (255 - grayscale) * 50;
        this->pixels[line_n][x] = (grayscale << 16) | (grayscale << 8) | grayscale; // ARGB format
        
        // std::cout <<"Pixel value: "<< pixels[0][0] << std::endl;
        // std::cout <<"Line number: "<< (int)line_n << std::endl;
        
        if (this->buffer[line_n][x]){
            did_draw = true;
            count ++;
        }
       
       
    }
    // if (did_draw && line_n == 126){

    //         std::cout <<"LINE : "<<(int) line_n << " has stuff on it " << count << std::endl;
    //         // exit(0);
    //     }
// exit(0);

SDL_UpdateTexture(this->texture, NULL, pixels, 160 * sizeof(uint32_t));

}
void Display_Ctl::render(){
    SDL_Event e;
    // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                // quit = true;
                exit(0);
            }
        }

        // // Clear screen with white color
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // RGBA for white
        // SDL_RenderClear(renderer);

        // // Update screen
        // SDL_RenderPresent(renderer);

    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}
