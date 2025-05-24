#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "src/modules/syslib/systemc.c"

#define PIC1 0x20 /* Базовый адрес ввода-вывода для главного PIC */
#define PIC2 0xA0 /* Базовый адрес ввода-вывода для подчиненного PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)
#define PIC_EOI 0x20 /* Код команды завершения прерывания */
/* повторно инициализирует контроллеры PIC, присвоив им заданные смещения вектора
   вместо 8h и 70h, как настроено по умолчанию */

#define ICW1_ICW4	0x01		/* Указывает на то, что ICW4 будет присутствовать */
#define ICW1_SINGLE	0x02		/* Одиночный (каскадный) режим */
#define ICW1_INTERVAL4	0x04		/* Интервал между вызовами 4 (8) */
#define ICW1_LEVEL	0x08		/* Режим срабатывания уровня (пограничный)*/
#define ICW1_INIT 0x10 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */
#define PIC_READ_IRR   0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR   0x0b    /* OCW3 irq service next CMD read */




typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // массив IDT записей с выравниванием


static idtr_t idtr; 

__attribute__((noreturn))

void exception_handler() { // фунция прерывания
    __asm__ volatile ("cli; hlt");
}


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid        = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved       = 0;
}


void PIC_sendEOI(uint8_t irq) // отправляет команду завершения прерывания
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
	
	outb(PIC1_COMMAND,PIC_EOI);
}

/*
arguments:
	offset 1 - смещение вектора для основного изображения
векторы на главном изображении становятся offset1..offset1+7
offset2 - то же самое для подчиненного изображения: offset2..offset2+7
*/

void PIC_remap(int offset1, int offset2) // PIC init
{
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // старт инициализации
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: сообщает ведущему PIC, что в IRQ2 (0000 0100) есть slave PIC
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3:  сообщает slave PIC его каскадный идентификатор (0000 0010)
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);               // ICW4: пусть PIC  использует режим 8086 (а не режим 8080)
	 io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Снимаем маску с обоих PIC.
	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 0);
}


void pic_disable(void) { // отключение PIC
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}

void IRQ_clear_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

static uint16_t __pic_get_irq_reg(int ocw3)
{
    
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}


uint16_t pic_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}


uint16_t pic_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}