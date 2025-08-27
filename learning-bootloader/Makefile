default:
	rm *.iso
	rm src/*.bin
	nasm -f bin src/boot.asm -o src/boot.bin
	xorriso -as mkisofs -b src/boot.bin -no-emul-boot -o boot.iso .
	qemu-system-i386 -cdrom boot.iso
	
