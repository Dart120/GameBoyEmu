#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "pixel_fetcher.h"
#include "tiledata.h"
#include "memory.h"
#include "modes.h"
#include "background.h"
#include "window.h"
#include "sprite.h"
#include "objects.h"
#include "display_ctl.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>
using namespace std;
uint8_t get_bit(uint8_t num, uint8_t bit){
    return (num >> bit) & 1;
}

uint8_t clear_bit(uint8_t num, uint8_t bit){
    return (num) & (~(1 << bit));
    
}
uint8_t set_bit(uint8_t num, uint8_t bit){
    return (num) | (1 << bit);
}
uint8_t reverse_bits(uint8_t input){
    uint8_t result = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t j = 7 - i;
        if (get_bit(input,i)){
            result = set_bit(result,j);
        } else {
            result = clear_bit(result, j);
        }
    }
    return result;
    
}

#define STAT 0xFF41
#define LCDC 0xFF40
#define SCX 0xFF43
#define SCY 0xFF42
#define WX 0xFF4B
#define LY_ADDR 0xFF44
#define WY 0xFF4A
#define BGP 0xFF47
PixelFetcher::PixelFetcher(Memory& memory, std::queue<Sprite>& to_display, bool& fetching_sprites, bool& tall_mode): 
        memory(memory), to_display(to_display), fetching_sprites(fetching_sprites), tall_mode(tall_mode){}
void PixelFetcher::process_2_cycles(uint8_t LY, bool should_push){
    if (fetching_sprites){
        populate_sprite_fifo(LY, should_push);
        return;
    }
    switch (this->mode)
    {
    case GET_TILE:
        {
            // cout<<"gettile"<<endl;

            get_tile(LY);
            mode = GET_TILE_DATA_LOW;
            break;
        }
    case GET_TILE_DATA_LOW:
    
    // PPU access to ram may be blocked for some reason
    // sprites always use 8000 mode
    
        {
            // cout<<"low"<<endl;
            uint8_t rowInTile;
            bool use_8000 = this->memory.get_bit_from_addr(LCDC, 4);
        uint8_t row_in_tile = rendering_window ? (WLC) % 8 : ((LY + this->memory.read_8_bit(SCY)) % 8);
        tile_addr_lower = (use_8000 ? 0x8000 + (this->tile_number * 16): 0x8800 + static_cast<int8_t>(this->tile_number) * 16) + row_in_tile * 2;
        // if (LY == 50) cout << "memloc " <<  tile_addr_lower << endl;
        tile_data_lower = this->memory.read_8_bit(tile_addr_lower);
        mode = GET_TILE_DATA_HIGH;
        break;}
    case GET_TILE_DATA_HIGH:
    
        {
            // cout<<"high"<<endl;
            tile_data_upper = this->memory.read_8_bit(tile_addr_lower + 1);
            mode = PUSH;
            if (first_time_on_line){
                reset(true,false);
            }
        break;}
    case PUSH:{
        // cout<<"push"<<endl;
        if (BG_FIFO.empty() && should_push){
            for (int i = 7; i >= 0; i--)
            {
                uint8_t low = tile_data_lower>>i  & 1;
                uint8_t upper = tile_data_upper>>i & 1;
                BG_FIFO.push({idx_to_color(upper * 2 + low), upper * 2 + low});
                
            }
            X_POS++;
       
            // check if XPOS has a sprite
            mode = GET_TILE;
        }
        break;}
    default:
        break;
    }

}
void PixelFetcher::populate_sprite_fifo(uint8_t LY, bool should_push){
    switch (this->sprite_mode)
    {
    case GET_TILE:
        {
            // cout<<"gettile"<<endl;

            sprite_tile_number = to_display.front().tile_number;
            sprite_mode = GET_TILE_DATA_LOW;
            break;
        }
    case GET_TILE_DATA_LOW:
    
    // PPU access to ram may be blocked for some reason
    // sprites always use 8000 mode
    
        {
            // cout<<"low"<<endl;
            uint8_t rowInTile;
            // TODO need to deal with flips
            uint8_t height = (tall_mode ? 16 : 8);
            uint8_t row_in_tile = (LY + this->memory.read_8_bit(SCY)) % height;
            if (to_display.front().y_filp()) row_in_tile = height - row_in_tile - 1;
            sprite_tile_addr_lower = 0x8000 + (this->sprite_tile_number * 16) + row_in_tile * 2;
            sprite_tile_data_lower = this->memory.read_8_bit(sprite_tile_addr_lower);
            sprite_mode = GET_TILE_DATA_HIGH;
        break;}
    case GET_TILE_DATA_HIGH:
    
        {
            sprite_tile_data_upper = this->memory.read_8_bit(sprite_tile_addr_lower + 1);
            sprite_mode = PUSH;
        break;}
    case PUSH:{
        std::queue<SpritePixel> temp_S_FIFO;
        int effective_x = to_display.front().x_pos - 8;
        if (to_display.front().x_filp()) {
            sprite_tile_data_lower = reverse_bits(sprite_tile_data_lower);
            sprite_tile_data_upper = reverse_bits(sprite_tile_data_upper);
        }

        for (int i = 7; i >= 0; i--)
        {
            if(effective_x < 0){
                if(!S_FIFO.empty()){
                    temp_S_FIFO.push(S_FIFO.front());
                    S_FIFO.pop();
                }
                effective_x++;

            } else {
                uint8_t low = sprite_tile_data_lower>>i  & 1;
                uint8_t upper = sprite_tile_data_upper>>i & 1;
                SpritePixel curr_pixel {sprite_idx_to_color(upper * 2 + low, 
                to_display.front().palette()), to_display.front().oam_idx,
                 upper * 2 + low, to_display.front().obj_bg_priority()};
                if (S_FIFO.empty()){
                    temp_S_FIFO.push(curr_pixel);

                } else {
                    SpritePixel old = S_FIFO.front();
                    S_FIFO.pop();
                    if (curr_pixel.color_idx == 0){
                        temp_S_FIFO.push(old);
                    } else if (old.color_idx == 0){
                        temp_S_FIFO.push(curr_pixel);
                    } else{
                        if (old.oam_idx < curr_pixel.oam_idx) temp_S_FIFO.push(old);
                        else if (old.oam_idx > curr_pixel.oam_idx) temp_S_FIFO.push(curr_pixel);
                        else cout << "You screwed up" << endl;
                    }
                    
                }
            }
            
            

          
            
        }
        while (!S_FIFO.empty()) S_FIFO.pop();
        while (!temp_S_FIFO.empty()){
            S_FIFO.push(temp_S_FIFO.front());
            temp_S_FIFO.pop();
        }
        to_display.pop();
        // check if XPOS has a sprite
        if (to_display.empty()){
            fetching_sprites = false;
        }
        sprite_mode = GET_TILE;
        
        break;}
    default:
        break;
    }

}

void PixelFetcher::get_tile(uint8_t LY){
    uint16_t addr;
    if (rendering_window){
        uint16_t base_addr = this->memory.get_bit_from_addr(LCDC, 6) ? 0x9C00 : 0x9800;
        uint8_t x_offset = ((X_POS - this->memory.read_8_bit(WX)) / 8) & 0x1F;
        uint8_t y_offset = ((LY - this->memory.read_8_bit(WY) ) / 8) & 0x1F;
        addr = base_addr + x_offset + (y_offset * 32);
    } else {
        uint16_t base_addr = this->memory.get_bit_from_addr(LCDC, 3) ? 0x9C00 : 0x9800;
        uint8_t x_offset = (X_POS + (this->memory.read_8_bit(SCX) / 8)) & 0x1F;
        uint8_t y_offset = ((LY + this->memory.read_8_bit(SCY)) & 0xFF) / 8;
        addr = base_addr + (x_offset + (y_offset * 32) & 0x3ff);
        // if(LY == 50) cout <<(int) base_addr << " " << x_offset<< " " << y_offset << addr<<endl;
    }
    this->tile_number = this->memory.read_8_bit(addr);
}
void PixelFetcher::switch_to_window(){
    while (!BG_FIFO.empty()){
        BG_FIFO.pop();
    }
    rendering_window = true;
    mode = GET_TILE;
    // TODO broken?
    X_POS = max(this->memory.read_8_bit(WX) - 7, 0);

    tile_number = 0;
  
    tile_addr_lower = 0;
    tile_addr_upper = 0;
    tile_data_upper = 0;
    tile_data_lower = 0;
    if (this->memory.read_8_bit(LY_ADDR) == this->memory.read_8_bit(WY)) {
    WLC = 0;  // Reset only if the window starts fresh.
    }
}


void PixelFetcher::reset(bool stall, bool switching_to_sprite){
    if (!switching_to_sprite){
        while (!BG_FIFO.empty()){
            BG_FIFO.pop();
        }
        X_POS = 0;
        first_time_on_line = !stall;
        
    }
    sprite_mode = GET_TILE;
    rendering_window = false;
    mode = GET_TILE;
 
    
    tile_number = 0;
   
    tile_addr_lower = 0;
    tile_addr_upper = 0;
    tile_data_upper = 0;
    tile_data_lower = 0;
    
    
}
uint8_t PixelFetcher::idx_to_color(uint8_t idx){
    uint8_t palette = this->memory.read_8_bit(BGP);
    return (palette >> (idx * 2)) & 3;
}
uint8_t PixelFetcher::sprite_idx_to_color(uint8_t idx, bool use_OBP1){
    uint8_t palette = use_OBP1 ? this->memory.read_8_bit(0xFF49) : this->memory.read_8_bit(0xFF48);
    return (palette >> (idx * 2)) & 3;
}
uint8_t PixelFetcher::pixel_mixing(){
    if (!S_FIFO.empty()){
        SpritePixel s_p = S_FIFO.front();
        S_FIFO.pop();
        Pixel bg_p = BG_FIFO.front();
        BG_FIFO.pop();
        if (s_p.color_idx == 0) return bg_p.color;
        if (s_p.bg_priority && bg_p.color_idx) return bg_p.color;
        return s_p.color;
    } else {
        Pixel bg_p = BG_FIFO.front();
        BG_FIFO.pop();
        return bg_p.color;
    }
}





