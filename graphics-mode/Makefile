CFLAGS = -std=gnu99 -ffreestanding -O2 -O0 -Wall -Wextra
OBJECTFILES = build/boot.o build/kernel.o

default:
	@i686-elf-as i386/boot.s -o build/boot.o
	@i686-elf-gcc -c kernel/kernel.c -o build/kernel.o $(CFLAGS)
	@i686-elf-gcc -T i386/linker.ld -o build/ct-os.bin -ffreestanding -O2 -nostdlib $(OBJECTFILES) -lgcc
clean:
	@rm -rf build/*.o build/*.bin *.iso build/isodir
iso:
	@mkdir -p build/isodir/boot/grub
	@cp build/ct-os.bin build/isodir/boot/ct-os.bin
	@cp i386/grub.cfg build/isodir/boot/grub/grub.cfg
	@grub-mkrescue -o ct-os.iso build/isodir
run:
	@qemu-system-i386 -cdrom ct-os.iso

full:
	@rm -rf build/*.o build/*.bin *.iso build/isodir

	@i686-elf-as i386/boot.s -o build/boot.o
	@i686-elf-gcc -c kernel/kernel.c -o build/kernel.o $(CFLAGS)
	@i686-elf-gcc -T i386/linker.ld -o build/ct-os.bin -ffreestanding -O2 -nostdlib $(OBJECTFILES) -lgcc

	@mkdir -p build/isodir/boot/grub
	@cp build/ct-os.bin build/isodir/boot/ct-os.bin
	@cp i386/grub.cfg build/isodir/boot/grub/grub.cfg
	@grub-mkrescue -o ct-os.iso build/isodir

	@qemu-system-i386 -cdrom ct-os.iso