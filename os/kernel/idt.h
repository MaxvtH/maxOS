#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_entry {
    uint16_t base_low;      // low 16 bits of handler address
    uint16_t selector;      // code segment selector
    uint8_t  zero;          // always zero
    uint8_t  flags;         // type and attributes
    uint16_t base_high;     // high 16 bits of handler address
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_set_gate(int n, uint32_t handler);
void idt_init();

#endif
