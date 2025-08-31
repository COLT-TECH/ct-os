[org 0x7C00]
[bits 16]

KERNEL_LOCATION equ 0x1000

; store disk number in variable
mov [BOOT_DISK], dl


xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 20

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13

; get vbe mode information
mov ax, 0x4F01
mov cx, 0x0117
mov di, 0x7E00
int 0x10

; switch to vbe mode 1024x768x16 (0x0117)
mov ax, 0x4F02
mov bx, 0x4117
int 0x10

; vbe mode switch error checking
cmp ax, 0x004F
je VBE_SUCCESS

VBE_ERROR:
    mov ax, 0x0003
    int 0x10

    mov ah, 0x0E
    mov si, vbe_err

.vbe_loop:
    cmp [si], byte 0
    je .vbe_halt

    mov al, [si]
    int 0x10

    inc si
    jmp .vbe_loop

.vbe_halt:
    hlt
    jmp $

vbe_err: db "ERROR: VESA MODE SWITCH UNSUCCESSFUL", 0

VBE_SUCCESS:

CODE_SEG equ GDT_code - GDT_Start
DATA_SEG equ GDT_data - GDT_Start

; Enter 32-Bit Protected mode
cli
lgdt [GDT_Descriptor]
; change the last bit of cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode ; far jump

hlt
jmp $

BOOT_DISK: db 0

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

start_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    jmp KERNEL_LOCATION

    hlt
    jmp $

times 510-($-$$) db 0
dw 0xAA55

