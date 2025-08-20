[org 0x7C00]
[bits 16]

mov bx, string

input:
   mov ah, 0
   int 0x16

   cmp ah, 0x1C
   je setupPrint

   mov ah, 0x0E
   int 0x10

   mov [bx], al
   inc bx
   jmp input

setupPrint:
   call newline

   mov byte [bx], 0
   mov bx, string
   mov ah, 0x0E

print:
   mov al, [bx]
   cmp al, 0
   je halt

   int 0x10
   inc bx
   jmp print

newline:
   mov ah, 0x0E
   mov al, 0x0D      ; Carriage return
   int 0x10
   mov al, 0x0A      ; Line feed
   int 0x10
   ret

halt:
   hlt

string:
   times 100 db 0

times 510 - ($-$$) db 0
dw 0xAA55
