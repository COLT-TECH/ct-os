CFLAGS = -ffreestanding -std=c11 -O0 -m32 -g -Wall
CPPFLAGS = -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -nostdlib -std=c++11 -O0 -m32 -g -Wall

KERNEL = src/kernel.cpp
KERNEL_ENTRY = src/boot/kernel_entry.asm
BOOTLOADER = src/boot/boot.asm

USB = /dev/sda

COBJ = "build/svga.o" "build/interrupts.o" "build/interrupt_asm.o" "build/io.o" "build/keyboard_isr.o" "build/font8x8.o" "build/font8x16.o" "build/cursor.o"
CPPOBJ = "build/windows.o"

default:
	@# GENERAL CODE
	@i386-elf-gcc $(CFLAGS) -c src/graphics/svga.c -o build/svga.o
	@i386-elf-gcc $(CFLAGS) -c src/lib/io.c -o build/io.o
	
	@# INPUT
	@i386-elf-gcc $(CFLAGS) -c src/input/cursor.c -o build/cursor.o

	@# INTERRUPTS CODE
	@i386-elf-gcc $(CFLAGS) -c src/interrupts/interrupts.c -o build/interrupts.o
	@nasm -f elf src/interrupts/interrupts.asm -o build/interrupt_asm.o
	@i386-elf-gcc $(CFLAGS) -c src/interrupts/ISR/keyboard_isr.c -o build/keyboard_isr.o

	@# FONTS
	@i386-elf-gcc $(CFLAGS) -c src/fonts/font8x8.c -o build/font8x8.o
	@i386-elf-gcc $(CFLAGS) -c src/fonts/font8x16.c -o build/font8x16.o
	
	@# C++
	@i386-elf-g++ $(CPPFLAGS) -c src/windows/window.cpp -o build/windows.o

	@# KERNEL
	@i386-elf-g++ $(CPPFLAGS) -c $(KERNEL) -o build/kernel.o
	@nasm $(KERNEL_ENTRY) -f elf -o build/kernel_entry.o
	@i386-elf-ld -Ttext 0x1000 -o "build/kernel.elf" "build/kernel_entry.o" "build/kernel.o" $(COBJ) $(CPPOBJ)
	@i386-elf-objcopy -O binary build/kernel.elf build/kernel.bin
	
	@# BOOTLOADER
	@nasm $(BOOTLOADER) -f bin -o build/bootloader.bin
	
	@rm build/*.o

write:
	@sudo dd if=/dev/zero of=$(USB) bs=1M count=119 status=progress
	@printf "o\nn\np\n1\n2048\n\na\nw\n" | sudo fdisk $(USB)

	@sudo dd if=build/bootloader.bin of=$(USB) bs=446 count=1 conv=notrunc

	@sudo dd if=build/kernel.bin of=$(USB) bs=512 seek=1 conv=notrunc

	@sudo sync

clean:
	@rm build/*.bin

qemu:
	@make
	@cat build/bootloader.bin build/kernel.bin > build/full.bin
	@nasm src/boot/zeros.asm -f bin -o build/zeros.bin
	@cat build/full.bin build/zeros.bin > build/qemu.bin
	
	@rm build/full.bin build/zeros.bin

	@qemu-system-x86_64 -vga std -drive format=raw,file="build/qemu.bin",index=0,if=floppy, -m 128M
