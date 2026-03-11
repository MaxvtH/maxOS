#include "keyboard.h"
#include "kernel.h"
#include "idt.h"

extern void keyboard_isr();

// Track shift state
static int shift_held = 0;

char scancode_to_char(uint8_t scancode) {
    switch(scancode) {
        // Numbers
        case 0x02: return shift_held ? '!' : '1';
        case 0x03: return shift_held ? '@' : '2';
        case 0x04: return shift_held ? '#' : '3';
        case 0x05: return shift_held ? '$' : '4';
        case 0x06: return shift_held ? '%' : '5';
        case 0x07: return shift_held ? '^' : '6';
        case 0x08: return shift_held ? '&' : '7';
        case 0x09: return shift_held ? '*' : '8';
        case 0x0A: return shift_held ? '(' : '9';
        case 0x0B: return shift_held ? ')' : '0';
        case 0x0C: return shift_held ? '_' : '-';
        case 0x0D: return shift_held ? '+' : '=';
        // Top row
        case 0x10: return shift_held ? 'Q' : 'q';
        case 0x11: return shift_held ? 'W' : 'w';
        case 0x12: return shift_held ? 'E' : 'e';
        case 0x13: return shift_held ? 'R' : 'r';
        case 0x14: return shift_held ? 'T' : 't';
        case 0x15: return shift_held ? 'Y' : 'y';
        case 0x16: return shift_held ? 'U' : 'u';
        case 0x17: return shift_held ? 'I' : 'i';
        case 0x18: return shift_held ? 'O' : 'o';
        case 0x19: return shift_held ? 'P' : 'p';
        case 0x1A: return shift_held ? '{' : '[';
        case 0x1B: return shift_held ? '}' : ']';
        // Middle row
        case 0x1E: return shift_held ? 'A' : 'a';
        case 0x1F: return shift_held ? 'S' : 's';
        case 0x20: return shift_held ? 'D' : 'd';
        case 0x21: return shift_held ? 'F' : 'f';
        case 0x22: return shift_held ? 'G' : 'g';
        case 0x23: return shift_held ? 'H' : 'h';
        case 0x24: return shift_held ? 'J' : 'j';
        case 0x25: return shift_held ? 'K' : 'k';
        case 0x26: return shift_held ? 'L' : 'l';
        case 0x27: return shift_held ? ':' : ';';
        case 0x28: return shift_held ? '"' : '\'';
        case 0x29: return shift_held ? '~' : '`';
        case 0x2B: return shift_held ? '|' : '\\';
        // Bottom row
        case 0x2C: return shift_held ? 'Z' : 'z';
        case 0x2D: return shift_held ? 'X' : 'x';
        case 0x2E: return shift_held ? 'C' : 'c';
        case 0x2F: return shift_held ? 'V' : 'v';
        case 0x30: return shift_held ? 'B' : 'b';
        case 0x31: return shift_held ? 'N' : 'n';
        case 0x32: return shift_held ? 'M' : 'm';
        case 0x33: return shift_held ? '<' : ',';
        case 0x34: return shift_held ? '>' : '.';
        case 0x35: return shift_held ? '?' : '/';
        // Space
        case 0x39: return ' ';
        default:   return 0;
    }
}

void keyboard_handler() {
    uint8_t scancode = inb(0x60);
    outb(0x20, 0x20);

    // Left shift press/release
    if (scancode == 0x2A) { shift_held = 1; return; }
    if (scancode == 0xAA) { shift_held = 0; return; }

    // Right shift press/release
    if (scancode == 0x36) { shift_held = 1; return; }
    if (scancode == 0xB6) { shift_held = 0; return; }

    // Ignore all other key releases
    if (scancode & 0x80) return;

    // Enter
    if (scancode == 0x1C) { newline(); return; }

    // Backspace
    if (scancode == 0x0E) { backspace(); return; }

    char c = scancode_to_char(scancode);
    if (c) print_char(c);
}

void keyboard_init() {
    idt_set_gate(33, (uint32_t) keyboard_isr);
}
