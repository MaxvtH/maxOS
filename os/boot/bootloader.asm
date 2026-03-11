BITS 16
ORG 0x7C00

start:
    mov si, message
    call print
    call load_kernel    ; load kernel before switching modes
    call switch_to_pm

; ----  Print routine ----
print:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E
    int 0x10
    jmp print
done:
    ret

; ----  Load kernel from disk ----
load_kernel:
    mov ah, 0x02        ; BIOS read sector function
    mov al, 15          ; number of sectors to read
    mov ch, 0           ; cylinder 0
    mov cl, 2           ; sector 2 (kernel starts here)
    mov dh, 0           ; head 0
    mov bx, 0x1000      ; load kernel to address 0x1000
    int 0x13            ; BIOS disk interrupt
    ret

; ---- GDT ----
gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; ----  Switch to protected mode ----
switch_to_pm:
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm

BITS 32

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp 0x1000          ; jump to kernel!

message db 'Loading maxOS...', 0x0D, 0x0A, 0

TIMES 510-($-$$) db 0
DW 0xAA55
