
#ifndef DISPLAY_CTL_H
#define DISPLAY_CTL_H
#include<iostream>
// #define FMT_HEADER_ONLY
#include <SDL2/SDL.h>
#include <vector>
#include <map>


class Display_Ctl
{
    
    public:
    Display_Ctl(std::array<std::array<u_int8_t,160>,144>& buffer);
    std::array<std::array<u_int8_t,160>,144>& buffer;
    void update(u_int8_t line_n);
    void render();
    uint32_t pixels[144][160];
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};
#endif