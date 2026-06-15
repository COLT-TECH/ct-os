CC     = i686-elf-gcc
CXX    = i686-elf-g++
AS     = nasm
LD     = i686-elf-ld
OBJCPY = i686-elf-objcopy

CFLAGS   = -ffreestanding -std=c11 -O2 -m32 -g -Wall
CPPFLAGS = -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -nostdlib -std=c++11 -O2 -m32 -g -Wall

KERNEL       = src/kernel.cpp
KERNEL_ENTRY = src/boot/kernel_entry.asm
BOOTLOADER   = src/boot/boot.asm

USB = /dev/sda

COBJ   = "build/svga.o" "build/interrupts.o" "build/interrupt_asm.o" "build/io.o" "build/keyboard_isr.o" "build/font8x8.o" "build/font8x16.o" "build/cursor.o"
CPPOBJ = "build/button.o" "build/button_manager.o"

default:
	@# GENERAL CODE
	@$(CC) $(CFLAGS) -c src/graphics/svga.c -o build/svga.o
	@$(CC) $(CFLAGS) -c src/lib/io.c -o build/io.o
	
	@# INPUT
	@$(CC) $(CFLAGS) -c src/input/GUI/cursor.c -o build/cursor.o

	@# INTERRUPTS CODE
	@$(CC) $(CFLAGS) -c src/interrupts/interrupts.c -o build/interrupts.o
	@$(AS) -f elf32 src/interrupts/interrupts.asm -o build/interrupt_asm.o
	@$(CC) $(CFLAGS) -c src/interrupts/ISR/keyboard_isr.c -o build/keyboard_isr.o

	@# FONTS
	@$(CC) $(CFLAGS) -c src/fonts/font8x8.c -o build/font8x8.o
	@$(CC) $(CFLAGS) -c src/fonts/font8x16.c -o build/font8x16.o
	
	@# C++
	@$(CXX) $(CPPFLAGS) -c src/input/GUI/button.cpp -o build/button.o
	@$(CXX) $(CPPFLAGS) -c src/input/GUI/button_manager.cpp -o build/button_manager.o

	@# KERNEL
	@$(CXX) $(CPPFLAGS) -c $(KERNEL) -o build/kernel.o

	@$(AS) -f elf32 $(KERNEL_ENTRY) -o build/kernel_entry.o
	
	@$(LD) -T src/boot/linker.ld -o "build/kernel.elf" "build/kernel_entry.o" "build/kernel.o" $(COBJ) $(CPPOBJ)

	@$(OBJCPY) -O binary build/kernel.elf build/kernel.bin
	
	@# BOOTLOADER
	@$(AS) $(BOOTLOADER) -f bin -o build/bootloader.bin
	
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
	@make clean
	@make
	@cat build/bootloader.bin build/kernel.bin > build/full.bin
	@$(AS) src/boot/zeros.asm -f bin -o build/zeros.bin
	@cat build/full.bin build/zeros.bin > build/qemu.bin
	
	@rm build/full.bin build/zeros.bin

	@qemu-system-x86_64 -vga std -drive format=raw,file="build/qemu.bin",index=0,if=floppy, -m 128M

git-acp:
	@git add *
	@git commit -m "."
	@git push
