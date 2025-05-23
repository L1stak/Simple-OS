#include "../std.h"

terminalVector terminalData;

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
void terminalPush(const char* str, enum vga_color color, enum vga_color background) {
    // FIXME
    terminal tmp;
    tmp.str = str;
    tmp.color = color;
    tmp.background = background;

    terminalData.data[terminalData.size++] = tmp;

    const char* terminalTmp = "";

    for (int i = 0; i < terminalData.size; i++) {
        int j = size(terminalData.data[i].str);
        const char* tmpStr = terminalData.data[i].str;
        while (size(tmpStr) != VGA_TERMINAL_WIDTH) {
            // tmpStr = terminalData.data[i].str + space;
        }

        terminalPrint(terminalData.data[i].str, terminalData.data[i].color, terminalData.data[i].background);
    }
    
}

void print(const char* str) {

}

void terminalInit() {
    terminalData.size = 0;
}