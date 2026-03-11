BITS 16
ORG 0x7C00

start:
    mov si, message
    call print

    call switch_to_pm   ; switch to protected mode

; ---- Print routine (16-bit) ----
print:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E
    int 0x10
    jmp print
done:
    ret

; ---- GDT ----
gdt_start:

gdt_null:               ; every GDT must start with a null descriptor
    dd 0x0
    dd 0x0

gdt_code:               ; code segment descriptor
    dw 0xFFFF           ; limit low
    dw 0x0              ; base low
    db 0x0              ; base middle
    db 10011010b        ; access byte
    db 11001111b        ; flags + limit high
    db 0x0              ; base high

gdt_data:               ; data segment descriptor
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b        ; access byte (data)
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size of GDT
    dd gdt_start                ; address of GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; --- -Switch to protected mode ----
switch_to_pm:
    cli                 ; disable interrupts
    lgdt [gdt_descriptor] ; tell CPU where GDT is

    mov eax, cr0
    or eax, 0x1         ; flip bit 0 of CR0
    mov cr0, eax        ; now in protected mode!

    jmp CODE_SEG:init_pm ; far jump to flush CPU pipeline

; â----  From here we are in 32-bit protected mode ----
BITS 32

init_pm:
    mov ax, DATA_SEG    ; point all segment registers to data segment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000    ; set up stack
    mov esp, ebp

    call begin_pm       ; jump to our 32-bit main

begin_pm:
    ; Print 'P' directly to video memory to prove we're in protected mode
    mov byte [0xB8000], 'P'
    mov byte [0xB8001], 0x0F    ; white on black

    jmp $               ; hang

message db 'Switching to protected mode...', 0x0D, 0x0A, 0

TIMES 510-($-$$) db 0
DW 0xAA55
