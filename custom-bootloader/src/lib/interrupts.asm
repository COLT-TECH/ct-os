[bits 32]

extern keyboard_interrupt_handler

global keyboard_handler_asm
keyboard_handler_asm:
    pushad
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call keyboard_interrupt_handler

    pop gs
    pop fs
    pop es
    pop ds
    popad

    mov al, 0x20
    out 0x20, al
    iret
