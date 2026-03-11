#ifndef KERNEL_H
#define KERNEL_H

// VGA text mode address
#define VGA_ADDRESS 0xB8000
#define VGA_WHITE_ON_BLACK 0x0F

// Screen info
#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 25

// Function declarations
void print(const char* str);
void clear_screen();

#endif
