i686-elf-gcc -m32 -c kernel.c -o kc.o
i686-elf-gcc -m32 -c src/modules/terminal/terminal.c -o terminalc.o
nasm -f elf32 Boot.asm -o kasm.o
i686-elf-ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o terminalc.o
rm -rf kasm.o kc.o terminalc.o
