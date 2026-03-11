#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

#define VGA_ADDRESS        0xB8000
#define VGA_WHITE_ON_BLACK 0x0F
#define SCREEN_WIDTH       80
#define SCREEN_HEIGHT      25

void print(const char* str);
void print_char(char c);
void newline();
void backspace();
void clear_screen();

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

#endif
