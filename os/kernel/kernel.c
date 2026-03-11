#include "kernel.h"
#include "idt.h"
#include "keyboard.h"

int cursor = 0;

void clear_screen() {
    char* vga = (char*) VGA_ADDRESS;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i += 2) {
        vga[i]     = ' ';
        vga[i + 1] = VGA_WHITE_ON_BLACK;
    }
    cursor = 0;
}

void print_char(char c) {
    char* vga = (char*) VGA_ADDRESS;
    vga[cursor * 2]     = c;
    vga[cursor * 2 + 1] = VGA_WHITE_ON_BLACK;
    cursor++;
}

void backspace() {
    if (cursor <= 0) return;        // don't go before start
    cursor--;
    char* vga = (char*) VGA_ADDRESS;
    vga[cursor * 2]     = ' ';     // clear the character
    vga[cursor * 2 + 1] = VGA_WHITE_ON_BLACK;
}

void print(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        print_char(str[i]);
        i++;
    }
}

void newline() {
    cursor = ((cursor / SCREEN_WIDTH) + 1) * SCREEN_WIDTH;
    print("> ");
}

void kernel_main() {
    clear_screen();
    print("Welcome to maxOS!");
    newline();

    idt_init();
    keyboard_init();

    while (1) {
        __asm__ volatile ("hlt");
    }
}
