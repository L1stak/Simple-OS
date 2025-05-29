bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;магические числа
        dd 0x00                  ;флаги
        dd - (0x1BADB002 + 0x00) ;контрольная сумма. мч+ф+кс должно равняться нулю

dt_start:
  gdt_null:
  dd 0x00
  dd 0x00
  gdt_code:
  dw 0xFFFF
  dw 0x0000
  db 0x00
  db 0x9A
  db 0xCF
  db 0x00
  gdt_data:
    dw 0xFFFF
  dw 0x0000
  db 0x00
  db 0x92
  db 0xCF
  db 0x00
  gdt_end:
  gdt_descriptor:
  dw gdt_end - gdt_start - 1
  dd gdt_start

  gdt_codeSeg equ gdt_code - gdt_start
  gdt_dataSeg equ gdt_data - gdt_start
lgdt [gdt_descriptor]

global start
extern kernelMain         ;kmain определена во внешнем файле



start:
  cli    ;блокировка прерываний
  mov esp, stack_space ;указатель стека
  call kernelMain
  hlt    ;остановка процессора

section .bss
resb 8192  ;8KB на стек
stack_space:

