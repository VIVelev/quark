CC = i386-elf-gcc
LD = i386-elf-ld

CFLAGS = -Wall -Wextra -Werror -pedantic-errors \
	-std=c11 -nostdlib -ffreestanding -O2 -m32

ASM = nasm
DISASM = ndisasm

EMU = qemu-system-i386
FORMAT = raw
INTERFACE = floppy

KERNEL_OFFSET = 0x1000

C_SOURCES = $(shell find . -name "*.c")
HEADERS = $(shell find . -name "*.h")
OBJ = $(C_SOURCES:.c=.o cpu/interrupt/interrupt.o)


os-image.bin: boot/bootloader.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	$(EMU) --drive file=$<,format=$(FORMAT),if=$(INTERFACE)

kernel.bin: boot/kernel_entry.o $(OBJ)
	$(LD) $^ --Ttext $(KERNEL_OFFSET) --oformat binary -o $@

# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	$(DISASM) -b 32 $< > $@

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $< -f elf -o $@

%.bin: %.asm
	$(ASM) $< -f bin -o $@

clean:
	find . -name "*.bin" -type f -delete
	find . -name "*.dis" -type f -delete
	find . -name "*.o" -type f -delete
