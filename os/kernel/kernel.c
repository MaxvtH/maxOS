#include "kernel.h"

// Current cursor position
int cursor = 0;

void clear_screen() {
    char* vga = (char*) VGA_ADDRESS;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i += 2) {
        vga[i]     = ' ';
        vga[i + 1] = VGA_WHITE_ON_BLACK;
    }
    cursor = 0;
}

void newline() {
	cursor = ((cursor / SCREEN_WIDTH) + 1) * SCREEN_WIDTH;
}

void print(const char* str) {
    char* vga = (char*) VGA_ADDRESS;
    int i = 0;
    while (str[i] != '\0') {
        vga[cursor * 2]     = str[i];
        vga[cursor * 2 + 1] = VGA_WHITE_ON_BLACK;
        cursor++;
        i++;
    }
}

void kernel_main() {
    clear_screen();
    print("Kernel loaded succesfully.");
    newline();
    print("Welcome to maxOS!");
    newline();
}
