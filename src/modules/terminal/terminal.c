#include "std.h"

void terminalPrint(const char* str, enum vga_color color, enum vga_color background) {

    if (background == VGA_COLOR_NONE){
    background = VGA_COLOR_BLACK;
    }
char *vidptr = (char*)0xb8000;     //видео пямять начинается здесь
    unsigned int i = 0;
    unsigned int j = 0;

    /* этот цикл очищает экран*/
    while(j < 80 * 25 * 2) {
        /* пустой символ */
        vidptr[j] = ' ';
        /* байт атрибутов */
        vidptr[j+1] = background; // цвет тут. HEX ФОРМАТ!!!!        
        j = j + 2;
    }

    j = 0;

    /* в этом цикле строка записывается в видео память */
    while(str[j] != '\0') {
        /* ascii отображение */
        vidptr[i] = str[j];
        vidptr[i+1] = color;
        ++j;
        i = i + 2;
    }
}
