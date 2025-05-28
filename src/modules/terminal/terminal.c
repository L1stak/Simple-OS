#include "../shell/shell.h"

size_t terminalRow;
size_t terminalColumn;
enum vga_color terminalColor;
uint16_t* terminalBuffer = (uint16_t*)0xb8000;

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminalInit() {
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;
	
	for (size_t y = 0; y < VGA_TERMINAL_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_TERMINAL_WIDTH; x++) {
			const size_t index = y * VGA_TERMINAL_WIDTH + x;
			terminalBuffer[index] = ' ' | terminalColor << 8;
		}
	}
}
void terminalSetColor(enum vga_color color, enum vga_color background) {
	terminalColor = color | background << 4;
}
void terminalPutentryat(char c, enum vga_color color, size_t x, size_t y) 
{
	const size_t index = y * VGA_TERMINAL_WIDTH + x;
	terminalBuffer[index] = c | color << 8;
}
void terminalPutchar(char c) {
	terminalPutentryat(c, terminalColor, terminalColumn, terminalRow);
	if (++terminalColumn == VGA_TERMINAL_WIDTH) {
		terminalColumn = 0;
		if (++terminalRow == VGA_TERMINAL_HEIGHT)
			terminalRow = 0;
	}
}
void terminalWrite(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminalPutchar(data[i]);
}
void print(const char* data) {
	char tmp[255];
	int size = 0;
	int i = 0;
	while (data[i] != '\0') {
		if (data[i] != '\n') {
			tmp[size] = data[i];
			size++;
		} else {
			tmp[size + 1] = '\0';
			terminalWrite(tmp, strlen(tmp));
			terminalRow++;
			terminalColumn = 0;
			size = 0;
			memClear(tmp, 255);
		}
		i++;
	}
	if (tmp[0] != '\0') {
		terminalWrite(tmp, strlen(tmp));
		size = 0;
		memClear(tmp, 255);
	}
}
void terminalSetCursor(size_t row, size_t column) {
	terminalRow = (row > VGA_TERMINAL_HEIGHT) ? VGA_TERMINAL_HEIGHT : (row < 0) ? 0 : row;
	terminalColumn = (column > VGA_TERMINAL_WIDTH) ? VGA_TERMINAL_WIDTH : (column < 0) ? 0 : column;
}
size_t getTerminalRow() {
	return terminalRow;
}
size_t getTerminalColumn() {
	return terminalColumn;
}
enum vga_color getTerminalColor() {
	return terminalColor;
}


// На всякий случай
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
