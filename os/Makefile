all: os.bin

# Assemble bootloader
boot/bootloader.bin: boot/bootloader.asm
	nasm -f bin boot/bootloader.asm -o boot/bootloader.bin

# Assemble kernel entry point
kernel/entry.o: kernel/entry.asm
	nasm -f elf32 kernel/entry.asm -o kernel/entry.o

# Compile kernel C code
kernel/kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -fno-pic -c kernel/kernel.c -o kernel/kernel.o

# Link everything into kernel binary
kernel/kernel.bin: kernel/entry.o kernel/kernel.o
	ld -m elf_i386 -Ttext 0x1000 --oformat binary kernel/entry.o kernel/kernel.o -o kernel/kernel.bin

# Stitch bootloader and kernel together
os.bin: boot/bootloader.bin kernel/kernel.bin
	cat boot/bootloader.bin kernel/kernel.bin > os.bin

clean:
	rm -f boot/*.bin kernel/*.bin kernel/*.o
