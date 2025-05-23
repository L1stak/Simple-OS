#include "../std.h"

void terminalPrint(const char* str, enum vga_color color, enum vga_color background) {
    char *vidptr = (char*)0xb8000;     //видео пямять начинается здесь
    unsigned int i = 0;
    unsigned int j = 0;

    /* в этом цикле строка записывается в видео память */
    while(str[j] != '\0') {
        /* ascii отображение */
        vidptr[i] = str[j];
        vidptr[i+1] = background << 4 | color;
        ++j;
        i = i + 2;
    }
}
void terminalClear(enum vga_color background) {
    if (background == VGA_COLOR_NONE){
    background = VGA_COLOR_BLACK;
    }

    char *vidptr = (char*)0xb8000;
    unsigned int j = 0;

    while(j < VGA_TERMINAL_WIDTH * VGA_TERMINAL_HEIGHT * 2) {
        vidptr[j] = ' ';
        vidptr[j+1] = background << 4;
        j = j + 2;
    }
}
