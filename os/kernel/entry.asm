BITS 32

global _start
global keyboard_isr
extern kernel_main
extern keyboard_handler

_start:
    mov esp, 0x90000
    call kernel_main
    jmp $

keyboard_isr:
    pusha
    call keyboard_handler
    popa
    iret
