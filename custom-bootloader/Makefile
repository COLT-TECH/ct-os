CFLAGS = -ffreestanding -O0 -m32 -g

KERNEL = src/kernel.c
KERNEL_ENTRY = src/boot/kernel_entry.asm
BOOTLOADER = src/boot/boot.asm
ZEROS = src/boot/zeros.asm

USB = /dev/sda

LIBOBJ = "build/vga.o"

default:
	@i386-elf-gcc $(CFLAGS) -c src/lib/vga.c -o build/vga.o

	@i386-elf-gcc $(CFLAGS) -c $(KERNEL) -o build/kernel.o
	@nasm $(KERNEL_ENTRY) -f elf -o build/kernel_entry.o
	@i386-elf-ld -o "build/kernel.bin" -Ttext 0x1000 "build/kernel_entry.o" "build/kernel.o" $(LIBOBJ) --oformat binary

	@nasm $(BOOTLOADER) -f bin -o build/bootloader.bin
	
	@rm build/*.o

write:
	@sudo dd if=/dev/zero of=$(USB) bs=1M count=1
	@printf "o\nn\np\n1\n2048\n\na\nw\n" | sudo fdisk $(USB)

	@sudo dd if=build/bootloader.bin of=$(USB) bs=1 count=446 conv=notrunc

	@sudo dd if=build/kernel.bin of=$(USB) bs=512 seek=1 conv=notrunc

	@sudo sync

clean:
	@rm build/*.bin build/*.o

qemu:
	@cat build/bootloader.bin build/kernel.bin > build/full.bin
	@nasm $(ZEROS) -f bin -o build/zeros.bin
	@cat build/full.bin build/zeros.bin > build/os.bin

	@qemu-system-x86_64 -drive format=raw,file="build/os.bin",index=0,if=floppy, -m 128M
