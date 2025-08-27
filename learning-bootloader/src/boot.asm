[org 0x7C00]
[bits 16]

; store disk number in variable
mov [BOOT_DISK], dl

CODE_SEG equ GDT_code - GDT_Start
DATA_SEG equ GDT_data - GDT_Start

; Enter 32-Bit Protected mode
cli
lgdt [GDT_Descriptor]
; change the last bit of cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

hlt
jmp $


; GDT
GDT_Start:
    GDT_null:
        dd 0x0
        dd 0x0 
    GDT_code:
        dw word 0xFFFF ; Limit
        dw 0x0 ; 16 bits +
        db 0x0 ; 8 bits = 24 bits of the base
        db 0b10011010 ; pres, priv, type, and type flags
        db 0b11001111
        db 0x0 ; last 8 bits of the base 24 + 8 = 32 bits
    GDT_data:
        dw word 0xFFFF
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0
GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1 ; size
    dd GDT_Start ; start

; END OF 16-BIT CODE

[bits 32]

; Functions
clear_screen:
    pusha
    mov ebx, 0xB8000
    mov al, ' '
    mov ah, 0x0F
.clear_loop:
    cmp ebx, 0xB8000+2000
    je .clear_return

    mov [ebx], ax

    times 2 inc ebx
    jmp .clear_loop
.clear_return:
    popa
    ret

print:
    pusha
    mov ebx, 0xB8000
    mov ah, 0x0F
.print_loop:
    mov al, [si]
    cmp al, 0
    je .print_return

    mov [ebx], ax

    inc si
    times 2 inc ebx

    jmp .print_loop
.print_return:
    popa
    ret



start_protected_mode:
    call clear_screen
    
    mov si, msg
    call print

    hlt
    jmp $



BOOT_DISK: db 0

msg: db "Successfully switched to 32-bit protected mode!", 0

times 510-($-$$) db 0
dw 0xAA55

