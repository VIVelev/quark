[org 0x7c00] ; tell the assembler that our offset is bootsector code

mov bx, HELLO
call print

call println

mov bx, GOODBYE
call print

call println

mov dx, 0x12fe
call print_hex

call println

jmp $


%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"

HELLO:
    db 'Hello World', 0

GOODBYE:
    db 'Goodbye World', 0

times 510-($-$$) db 0
dw 0xaa55
