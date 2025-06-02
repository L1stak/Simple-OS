GCC = i686-elf-gcc
NASM = nasm
LINK = i686-elf-ld
ECHO = echo

GCCFLAGS = -m32 -c
GCCFLAGS2 = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
NASMFLAGS = -f elf32
LINKFLAGS = -m elf_i386 -T

SRCC = $(shell find . -name '*.c' ! -name "IRQ.c") 
SRCASM = $(shell find . -name '*.asm')
SRCCUSTOM = modules/Interrupts/IRQ.c

OBJC = $(SRCC:.c=.o)
OBJASM = $(SRCASM:.asm=.o)
OBJCUSTOM = $(SRCCUSTOM:.c=.o)

TARGET = kernel.elf

all: $(TARGET)


%.o: %.c
	$(GCC) $(GCCFLAGS) $< -o $@ $(GCCFLAGS2)

%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@


$(TARGET): $(OBJC) $(OBJASM)
	$(GCC) -m32 -mgeneral-regs-only -c $(SRCCUSTOM) -o $(OBJCUSTOM) $(GCCFLAGS2)
	$(LINK) $(LINKFLAGS) link.ld -o $(TARGET) $(OBJASM) $(OBJC) $(OBJCUSTOM)

run: $(TARGET)
	qemu-system-x86_64 -kernel ./kernel.elf -m 512

clean:
	rm -f $(OBJC) $(OBJCUSTOM) $(OBJASM) $(TARGET)