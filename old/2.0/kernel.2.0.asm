BITS 32

kernel_main:
    ; Print 'MaxOS' to screen via video memory
    mov byte [0xB8000], 'M'
    mov byte [0xB8001], 0x0F
    mov byte [0xB8002], 'a'
    mov byte [0xB8003], 0x0F
    mov byte [0xB8004], 'x'
    mov byte [0xB8005], 0x0F
    mov byte [0xB8006], 'O'
    mov byte [0xB8007], 0x0F
    mov byte [0xB8008], 'S'
    mov byte [0xB8009], 0x0F

    jmp $               ; hang
