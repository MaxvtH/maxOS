all: os.bin

boot/bootloader.bin: boot/bootloader.asm
	nasm -f bin boot/bootloader.asm -o boot/bootloader.bin

kernel/entry.o: kernel/entry.asm
	nasm -f elf32 kernel/entry.asm -o kernel/entry.o

kernel/kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -fno-pic -c kernel/kernel.c -o kernel/kernel.o

kernel/idt.o: kernel/idt.c
	gcc -m32 -ffreestanding -fno-pic -c kernel/idt.c -o kernel/idt.o

kernel/keyboard.o: kernel/keyboard.c
	gcc -m32 -ffreestanding -fno-pic -c kernel/keyboard.c -o kernel/keyboard.o

kernel/kernel.bin: kernel/entry.o kernel/kernel.o kernel/idt.o kernel/keyboard.o
	ld -m elf_i386 -Ttext 0x1000 --oformat binary \
	kernel/entry.o kernel/kernel.o kernel/idt.o kernel/keyboard.o \
	-o kernel/kernel.bin

os.bin: boot/bootloader.bin kernel/kernel.bin
	cat boot/bootloader.bin kernel/kernel.bin > os.bin

clean:
	rm -f boot/*.bin kernel/*.bin kernel/*.o
