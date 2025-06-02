#include <stddef.h>
#include "gdt.h"

#include "../std.h"
struct gdt_entry_struct {
    uint16_t limit_low;    // Младшие 16 бит смещения
     uint16_t base_low;    // Младшие 16 бит базы
    uint8_t  base_middle;    // Следующие восемь бит базы
     uint8_t  access;        // Флаг определяет уровень доступа
     uint8_t  granularity;
     uint8_t  base_high;    // старшие 8 бит базы
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;
struct gdt_ptr_struct {
    uint16_t limit;    // старшие 16 бит смещения селектора
    uint32_t base;    // адрес первой структуры gdt_entry_t
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

gdt_entry_t    gdt_entries[5];
gdt_ptr_t    gdt_ptr;


void init_gdt()
{
    print("gdt init\n");
    gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // Нулевой сегмент
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);    // Сегмент кода
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);    // Сегмент данных
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);    // Сегмент кода уровня пользовательских процессов
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);    // Сегмент данных уровня пользовательских процессов

    gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low     = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high     = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low     = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access         = access;
}

