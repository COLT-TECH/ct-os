[org 0x7C00]
[bits 16]

jmp main

print:
	pusha
	mov ah, 0x0E
	jmp .print_loop
.print_loop:
	mov al, [si]
	cmp al, 0
	je .print_return

	int 0x10
	inc si

	jmp .print_loop
.print_return:
	popa
	ret

newline:
	pusha
	mov ah, 0x0E
	mov al, 0x0D
	int 0x10
	mov al, 0x0A
	int 0x10
	popa
	ret


main:
	; 0 all segment registers
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov cs, ax
	
	; Setup Stack
	mov ss, ax
	mov sp, 0x7C00

	mov si, msg
	call print
	call newline

	; store disk number in variable
	mov [disk_num], dl

	; access next sector
	mov ah, 2
	mov al, 1 ; how many sectors to read
	mov ch, 0 ; cylinder number
	mov cl, 2 ; sector number
	mov dh, 0 ; head number
	mov dl, [disk_num] ; drive number
	mov es, ax ;     \/
	mov bx, 0x7E00 ; pointer to where we want to load the sector
	int 0x13
	
	jc error_cf

	cmp al, 1
	jne error_al

	mov ah, 0x0E
	mov al, es:[0x7E00]
	int 0x10
	
	jmp halt

error_cf:
	call newline
	mov si, err_cf
	call print

error_al:
	call newline
	mov si, err_al
	call print

halt:
	cli
	hlt

disk_num: db 0
msg: db "Booted!", 0
err_cf: db "ERROR CF", 0
err_al: db "ERROR AL", 0

times 510-($-$$) db 0
dw 0xAA55

; in next sector
times 511 db 'A'
times 1 db 0

