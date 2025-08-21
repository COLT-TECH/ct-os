org 0x7C00
bits 16

start:
   jmp main

puts:
   push si
   push ax

.loop
   lodsb
   cmp al, 0
   je .done

   mov ah, 0x0E
   mov bh, 0
   int 0x10

   jmp .loop

.done
   pop ax
   pop si
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
   call puts

   hlt

msg: db 'Hello World!', 0

times 510-($-$$) db 0
dw 0xAA55
