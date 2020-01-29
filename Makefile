CC = i386-elf-gcc
CFLAGS = -Wall -pedantic -ffreestanding
LD = i386-elf-ld
ASM = nasm
DISASM = ndisasm

KERNEL_OFFSET = 0x1000


all: run

run: os-image.bin
	qemu-system-i386 --drive file=$<,format=raw,if=floppy

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

bootsect.bin: boot/bootsect.asm
	$(ASM) $< -f bin -o $@

kernel.bin: kernel_entry.o kernel.o
	$(LD) $^ --Ttext $(KERNEL_OFFSET) --oformat binary -o $@

kernel_entry.o: boot/kernel_entry.asm
	$(ASM) $< -f elf -o $@

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	$(DISASM) -b 32 $< > $@

clean:
	rm *.bin *.o *.dis
