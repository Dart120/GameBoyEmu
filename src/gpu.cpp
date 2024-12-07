#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "gpu.h"
#include "tiledata.h"
#include "memory.h"
#include "modes.h"
#include "background.h"
#include "window.h"
#include "objects.h"
#include "display_ctl.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

#include <spdlog/sinks/basic_file_sink.h>

#include <spdlog/spdlog.h>
// void printArray(std::array<unsigned char, 160> a,int n){
// 	for(int i=0;i<n;i++)
//       std::cout<<a[i]<<" ";
//   	std::cout<<std::endl;
// }
#define STAT 0xFF41
#define LCDC 0xFF40
#define SCX 0xFF43
#define LYC 0xFF45
#define IF 0xFF0F

#define SCY 0xFF42
#define WX 0xFF4B
#define WY 0xFF4A




#define LY_ADDR 0xFF44
#define WY 0xFF4A
#define BGP 0xFF47
using namespace std;
// TODO banning CPU and PPU from memory
// TODO Spirites
// TODO Turning off LCD
// TODO palettes
// TODO DMA Trans
//  
GPU::GPU(Memory& memory, MODES& GPU_modes,int scale): memory(memory),tiledata(memory),background(memory,tiledata), window(memory,tiledata), object(memory,tiledata), GPU_modes(OAM_SCAN), buffer{}, display_ctl(buffer), pixel_fetcher(memory) {}

void GPU::do_4_dots(){
    this->clock += 4;
    bool vblank = false;
    // uint8_t LY = this->memory.read_8_bit(0xFF44);
    // spdlog::info("LY:{:02X} MODE:{:02X} cycles_left:{} X_pos :{}",
    //         LY,
    //         GPU_modes,
    //         cycles_left,
    //         X_POS);

    switch (this->GPU_modes)
    {
        
        case H_BLANK:
        {
            // cout<< "HBLANK" << endl;
            if (this->clock >= 204) {
                this->clock -= 204;
                this->line++;
                this->update_LY();
                if (this->line == 144) {
                    this->GPU_modes = V_BLANK;
                    vblank = true;
                    this->memory.set_bit_from_addr(IF,0);
                    if (this->memory.get_bit_from_addr(STAT, 4)) this->memory.set_bit_from_addr(IF, 1);
                    this->memory.set_bit_from_addr(STAT, 0);
                    this->memory.clear_bit_from_addr(STAT, 1);
                    // bg tilecache goes away
                    display_ctl.render();

                } else{
                    GPU_modes = OAM_SCAN;
                    this->memory.clear_bit_from_addr(STAT, 0);
                    this->memory.set_bit_from_addr(STAT, 1);
                    if (this->memory.get_bit_from_addr(STAT, 5)) this->memory.set_bit_from_addr(IF, 1);
                } 

            }
            break;}
        case V_BLANK:
        {
            // cout<< "VBLANK" << endl;
            if (this->clock >= 456){
                this->clock -= 456;
                this->line++;
                if (this->line > 153){
                    this->line = 0;
                    GPU_modes = OAM_SCAN;
                    this->memory.clear_bit_from_addr(STAT, 0);
                    this->memory.set_bit_from_addr(STAT, 1);
                    if (this->memory.get_bit_from_addr(STAT, 5)) this->memory.set_bit_from_addr(IF, 1);

                }
                this->update_LY();
            }
        break;}
        case OAM_SCAN:
        {
            // cout<< "OAM" << endl;
            if (this->clock >= 80){
                this->clock -= 80;
                this->GPU_modes = DRAW;
                this->memory.set_bit_from_addr(STAT, 0);
                this->memory.set_bit_from_addr(STAT, 1);
            }
            break;}
    case DRAW:
    {
        // cout<< "Draw"<<this->clock << endl;
        if (this->clock >= 172){
            this->clock -= 172;
            this->drawScanLine();
            this->GPU_modes = H_BLANK;
            this->memory.clear_bit_from_addr(STAT, 0);
            this->memory.clear_bit_from_addr(STAT, 1);
            if (this->memory.get_bit_from_addr(STAT, 3)) this->memory.set_bit_from_addr(IF, 1);
        }
        break;}
  
    

    default:
        break;
    }

}

void GPU::update_LY(){
    this->memory.write_8_bit(0xFF44,this->line);
    if (this->line == this->memory.read_8_bit(LYC)){
        this->memory.set_bit_from_addr(STAT, 2);
        if (this->memory.get_bit_from_addr(STAT, 6)) this->memory.set_bit_from_addr(IF, 1);
    }
    else this->memory.clear_bit_from_addr(STAT, 2);
}
void GPU::drawScanLine(){
    if (this->memory.get_bit_from_addr(LCDC, 7)){
        this->drawBackground();
    }
}
void GPU::drawBackground(){
if (!this->memory.get_bit_from_addr(LCDC, 0)) {
    return;
}

// Determine the base address for the tilemap
int base_addr = this->memory.get_bit_from_addr(LCDC, 3) ? 0x9C00 : 0x9800;
std::cout << "Base address for tilemap: " << std::hex << base_addr << std::dec << std::endl;

// Determine whether to use 0x8000 tile data or signed index mode
bool use_8000 = this->memory.get_bit_from_addr(LCDC, 4);
std::cout << "Using 0x8000 tile data: " << std::boolalpha << use_8000 << std::endl;

// Default data start for unsigned tiles
bool signedIdx = false;
int data_start = 0x8000;

// Check if signed index mode is enabled
if (use_8000) {
    data_start = 0x8800;
    signedIdx = true;
}
std::cout << "Data start address: " << std::hex << data_start << std::dec << std::endl;
std::cout << "Signed index mode: " << std::boolalpha << signedIdx << std::endl;

// Get scroll registers
int bgx = this->memory.read_8_bit(SCX);
std::cout << "BGX (Scroll X): " << bgx << std::endl;

int bgy = this->memory.read_8_bit(SCY);
std::cout << "BGY (Scroll Y): " << bgy << std::endl;

// Calculate which line of the tile to render
int tileLine = ((this->line + bgy) & 7);
std::cout << "Tile line (row within tile): " << tileLine << std::endl;

// Calculate which row of tiles to render from
int tileRow = ((((bgy + this->line) / 8) | 0) & 0x1F);
std::cout << "Tile row (row in tilemap): " << tileRow << std::endl;

// Determine the first and last tiles to render
int firstTile = ((bgx / 8) | 0) + 32 * tileRow;
std::cout << "First tile index: " << firstTile << std::endl;

int lastTile = firstTile + 160 / 8 + 1;
if ((lastTile & 0x1F) < (firstTile & 0x1F)) {
    lastTile -= 32;
}
std::cout << "Last tile index: " << lastTile << std::endl;

// Calculate X position of the first tile's leftmost pixel
int x = (firstTile & 0x1F) * 8 - bgx;
std::cout << "X position of first tile's leftmost pixel: " << x << std::endl;

// Render the background tiles for the current scanline
for (int i = firstTile; i != lastTile; i++, i -= 32 * ((i & 0x1F) == 0)) {
    std::cout << "Rendering tile index: " << i << std::endl;
    // Debugging - force early exit after printing first and last tile
    std::cout << "First tile index: " << firstTile << std::endl;
    std::cout << "Last tile index: " << lastTile << std::endl;
    exit(1); // Debugging exit}

    uint8_t tileIndex = this->memory.read_8_bit(i + base_addr);

    if (signedIdx) {
        tileIndex = static_cast<int8_t>(tileIndex) + 128; // Convert to signed and adjust
    }


    const auto& tileData = readTileData(tileIndex, data_start);

    // Draw the tile line and copy it to the buffer
    drawTileLine(tileData, tileLine, x);
    // copyBGTileLine(lineBuffer, tileBuffer, x);
    x += 8;
}




}

std::vector<uint8_t> GPU::readTileData(uint8_t tileIdx, uint8_t dataStart){
    std::vector<uint8_t> tileData;
    uint16_t tileAddressStart = dataStart + (tileIdx * 0x10);

    for (uint16_t i = tileAddressStart; i < tileAddressStart + 0x10; i++) {
        tileData.push_back(this->memory.read_8_bit(i));
    }

    return tileData;
}
void GPU::drawTileLine (std::vector<uint8_t>  tileData, uint8_t line, uint8_t x){
     

    // Calculate the line to read based on vertical flip
    int l = line;

    // Each line consists of two bytes in tile data
    int byteIndex = l * 2;

    // Fetch the two bytes for the specified line
    uint8_t b1 = tileData[byteIndex];
    uint8_t b2 = tileData[byteIndex + 1];

    // Iterate over each pixel in the line
    int offset = 8; // Bit offset starts at the leftmost pixel
    for (int pixel = 0; pixel < 8; ++pixel) {
        offset--;
        uint8_t mask = (1 << offset);

        // Extract color value from the two bytes
        uint8_t colorValue = ((b1 & mask) >> offset) + ((b2 & mask) >> offset) * 2;

        // Determine the correct position in the buffer based on horizontal flip
        int p = pixel;

        // Write the color value into the tile buffer
        this->display_ctl.update(this->line, x + pixel, colorValue);
       
    }
}
