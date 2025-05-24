#include "../std.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


static inline uint32_t farpeekl(uint16_t sel, void* off)
{
    uint32_t ret;
    asm ( "push %%fs\n\t"
          "mov %1, %%fs\n\t"
          "mov %%fs:(%2), %0\n\t"
          "pop %%fs"
          : "=r"(ret) : "g"(sel), "r"(off) );
    return ret;

}

static inline void farpokeb(uint16_t sel, void* off, uint8_t v)
{
    asm ( "push %%fs\n\t"
          "mov %0, %%fs\n\t"
          "movb %2, %%fs:(%1)\n\t"
          "pop %%fs"
          : : "g"(sel), "r"(off), "r"(v) );
   
}

static inline void outb(uint16_t port, uint8_t val) // out asm
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* Существует кодировка outb %al, $ imm8, для постоянных номеров портов во время компиляции, которые помещаются в 8b. (Ограничение N).
 * Более широкие непосредственные константы будут усекаться во время сборки (например, ограничение «i»).
 * Кодировка outb %al, %dx является единственным вариантом для всех остальных случаев.
 * %1 расширяется до %dx, потому что порт является uint16_t. %w1 можно было бы использовать, если бы номер порта был более широким типом C */
}

static inline uint8_t inb(uint16_t port) // in  asm
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void io_wait(void) // sleep на пару микросекунд
{
    outb(0x80, 0);
}

static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

// включение / отключение прерываний
static inline unsigned long save_irqdisable(void)
{
    unsigned long flags;
    asm volatile ("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
    return flags;
}

static inline void irqrestore(unsigned long flags)
{
    asm ("push %0\n\tpopf" : : "rm"(flags) : "memory","cc");
}

static void intended_usage(void)
{
    unsigned long f = save_irqdisable();
    do_whatever_without_irqs();
    irqrestore(f);
}

static inline uint64_t rdtsc() // считывает текущее значение счётчика временных меток процессора и сохранит его в EDX:EAX. 
{
    uint64_t ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}

