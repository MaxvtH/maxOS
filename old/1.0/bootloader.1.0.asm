BITS 16                     ; We start in 16-bit real mode
ORG 0x7C00                  ; BIOS loads us at this memory address

start:
    mov si, message         ; Point SI register to our message
    call print              ; Call the print routine

hang:
    jmp hang                ; Loop forever so the CPU doesn't wander off

print:
    lodsb                   ; Load next character from SI into AL
    or al, al               ; Check if character is 0 (end of string)
    jz done                 ; If zero, we're done
    mov ah, 0x0E            ; BIOS teletype function
    int 0x10                ; Call BIOS to print the character
    jmp print               ; Next character

done:
    ret

message db 'Hello from maxOS!', 0    ; Our message, 0 = end of string

TIMES 510-($-$$) db 0       ; Pad with zeros to 510 bytes
DW 0xAA55                   ; Boot signature, BIOS needs this to recognize us
