#pragma once
#include<stdint.h>

/*struct gdt_segment {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access_byte;
	uint8_t limit_high;
	uint8_t flags;
	uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr_struct {
	uint16_t limit;
	//unsigned int base;
	struct gdt_segment*  base;
} __attribute__((packed));

struct gdt_flag{};

void initSegment(uint8_t num, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags);
void initGdt();

extern void gdt_flush(void* gdt_ptr);*/

// Сделаем доступными наши функции из кода на ассемблере
extern void gdt_flush(uint32_t);

void init_gdt();
static void gdt_set_gate(uint32_t,uint32_t, uint32_t,uint8_t,uint8_t);


