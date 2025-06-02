
global gdt_flush
gdt_flush:
    mov eax, [esp+4]        ; получаем указатель на GDT
    lgdt [eax]                ; загружаем этот указатель в специальный регистр
    
    mov ax, 0x10            ; 0x10 - это смещение в GDT для нашего сегмента данных
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush            ; 0x08 - смещение для нашего сегмента кода: дальний переход
.flush:
    ret