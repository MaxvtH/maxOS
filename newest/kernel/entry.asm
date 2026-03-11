BITS 32

global _start
extern kernel_main      ; tell the linker kernel_main is in another file

_start:
    mov esp, 0x90000    ; set up stack
    call kernel_main    ; call our C kernel
    jmp $               ; hang if kernel returns
