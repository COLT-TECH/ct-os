[org 0x7C00]
[bits 16]

start:
    jmp main


print:
    pusha
    mov ah, 0x0E

.print_loop:
    cmp [si], byte 0
    je .print_ret

    mov al, [si]
    int 0x10
    inc si
    
    jmp .print_loop

.print_ret:
    popa
    ret


main:
    ; setup data segments
    mov ax, 0
    mov ds, ax
    mov es, ax

    ; setup stack
    mov ss, ax
    mov sp, 0x7C00 ; stack grows downward from where our program is loaded in memory (0x7C00)
    
    mov si, msg
    call print

halt:
    cli
    hlt

msg: db 'Booted!', 0

times 510-($-$$) db 0
dw 0xAA55
