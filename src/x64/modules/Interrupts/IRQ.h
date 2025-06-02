#pragma once
#include <stdint.h>
#include "../std.h"
#define IDT_MAX_DESCRIPTORS 256
void idt_init(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);


