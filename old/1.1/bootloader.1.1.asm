BITS 16
ORG 0x7C00

start:
    mov si, message
    call print
    call prompt

hang:
    jmp hang

; Print a string (SI = address of string)
print:
    lodsb
    or al, al
    jz done
    mov ah, 0x0E
    int 0x10
    jmp print
done:
    ret

; Wait for keypress and print it, then loop
prompt:
    mov si, prompt_str
    call print          ; print "> "

.loop:
    mov ah, 0x00
    int 0x16            ; wait for a keypress, character goes into AL

    cmp al, 0x0D        ; did user press Enter?
    je .newline         ; if yes, go to new line

    mov ah, 0x0E
    int 0x10            ; print the character

    jmp .loop           ; wait for next key

.newline:
    mov ah, 0x0E
    mov al, 0x0D        ; carriage return
    int 0x10
    mov al, 0x0A        ; line feed
    int 0x10

    jmp prompt          ; show "> " again

message     db 'Hello from maxOS!', 0x0D, 0x0A, 0
prompt_str  db '> ', 0

TIMES 510-($-$$) db 0
DW 0xAA55
