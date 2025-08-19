mov ah, 0x0E
mov al, 'A'
int 0x10

alphabet:
   inc al ; Increment
   cmp al, 'Z' ; Compare
   je halt ; Halt if compare was equal

   int 0x10 ; print character
   jmp alphabet

halt:
   hlt

times 510 - ($-$$) db 0
dw 0xAA55
