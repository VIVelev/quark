print_string:
    pusha

; keep this in mind:
; while (string[i] != 0) { print string[i]; i++ }

print_string_loop:
    mov al, [bx]
    cmp al, 0
    je print_string_done

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp print_string_loop

print_string_done:
    popa
    ret

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a  ; newline char
    int 0x10
    mov al, 0x0d  ; carriage return
    int 0x10
    
    popa
    ret
