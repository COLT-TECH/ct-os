KERNEL = src/kernel.c
KERNEL_ENTRY = src/boot/kernel_entry.asm
BOOTLOADER = src/boot/boot.asm
ZEROS = src/boot/zeros.asm

default:
	@i386-elf-gcc -ffreestanding -m32 -g -c $(KERNEL) -o build/kernel.o
	@nasm $(KERNEL_ENTRY) -f elf -o build/kernel_entry.o
	@i386-elf-ld -o "build/full_kernel.bin" -Ttext 0x1000 "build/kernel_entry.o" "build/kernel.o" --oformat binary

	@nasm $(BOOTLOADER) -f bin -o build/boot.bin

	@cat build/boot.bin build/full_kernel.bin > build/full.bin

	@nasm $(ZEROS) -f bin -o build/zeros.bin
	@cat build/full.bin build/zeros.bin > build/os.bin

run:
	@qemu-system-x86_64 -drive format=raw,file="build/os.bin",index=0,if=floppy, -m 128M

clean:
	@rm build/*.o build/*.bin
