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
#include <queue>
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

    
    window = nullptr;
    renderer = nullptr;
    window = SDL_CreateWindow("emu",0,0,160,144,SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
 
    SDL_UpdateWindowSurface(window);

    SDL_LockSurface(surface);
    SDL_memset(surface->pixels,255,surface->h * surface->pitch);
    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(window);
    // this->texture =  SDL_CreateTexture(this->renderer,
    //                             SDL_PIXELFORMAT_RGB888,
    //                             SDL_TEXTUREACCESS_TARGET, 160,
    //                             144);

}
void Display_Ctl::update(u_int8_t LY, uint8_t x, uint8_t color){
    SDL_Color palette[4] = {
        {255, 255, 255, 255}, // White
        {192, 192, 192, 255}, // Light Gray
        {96, 96, 96, 255},    // Dark Gray
        {0, 0, 0, 255}        // Black
    };
    SDL_LockSurface(surface);
    SDL_Color c = palette[color];

        // Access the pixel at (x, LY)
        Uint32 mapped_color = SDL_MapRGB(surface->format, c.r, c.g, c.b);
        Uint8* target_pixel = static_cast<Uint8*>(surface->pixels) + (LY * surface->pitch) + (x * surface->format->BytesPerPixel);

        // Write the color
        *(Uint32*)target_pixel = mapped_color;
    SDL_UnlockSurface(surface);
    // if (color){
    //     std::cout << color*20 << std::endl;
    // }
    // std::cout <<(int) LY<<" "<<(int) x<<" "<<(int) color << std::endl;
    

}
void Display_Ctl::render(){

    //     // // Clear screen with white color
    //     // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // RGBA for white
    //     // SDL_RenderClear(renderer);

    //     // // Update screen
    //     // SDL_RenderPresent(renderer);

    // SDL_RenderClear(this->renderer);
    // SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    // SDL_RenderPresent(this->renderer);
    SDL_UpdateWindowSurface(window);
}
