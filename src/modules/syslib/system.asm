section .text
    global sleep

; FIXME
sleep:
    sub esp, 8              ; стек 8 байт

    mov eax, [esp + 8]
    mov [esp], eax
    mov dword [esp + 4], 0

    mov eax, 162            ; syscall nanosleep
    mov ebx, esp
    mov ecx, 0
    int 0x80

    add esp, 8              ; удаляем стек из памяти
    ret

