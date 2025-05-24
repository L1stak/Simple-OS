GCC = i686-elf-gcc
NASM = nasm
LINK = i686-elf-ld

GCCFLAGS = -m32 -c
GCCFLAGS2 = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
NASMFLAGS = -f elf32
LINKFLAGS = -m elf_i386 -T

SRCC = $(shell find . -name '*.c')
SRCASM = $(shell find . -name '*.asm')

OBJC = $(SRCC:.c=.o)
OBJASM = $(SRCASM:.asm=.o)

TARGET = kernel

all: $(TARGET)

%.o: %.c
	$(GCC) $(GCCFLAGS) $< -o $@ $(GCCFLAGS2)

%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

$(TARGET): $(OBJC) $(OBJASM)
	$(LINK) $(LINKFLAGS) link.ld -o $(TARGET) $(OBJASM) $(OBJC)


clean:
	rm -f $(OBJC) $(OBJASM) $(TARGET)
