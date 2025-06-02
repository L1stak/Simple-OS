bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;магические числа
        dd 0x00                  ;флаги
        dd - (0x1BADB002 + 0x00) ;контрольная сумма. мч+ф+кс должно равняться нулю



global start
extern kernelMain         ;kmain определена во внешнем файле



start:
  cli    ;блокировка прерываний
  mov esp, stack_space ;указатель стека
  call kernelMain
  ;lgdt [gdt_descriptor]
  hlt    ;остановка процессора
 ; sti

section .bss
resb 8192  ;8KB на стек
stack_space:

