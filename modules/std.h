#pragma once
#define VGA_TERMINAL_WIDTH 80
#define VGA_TERMINAL_HEIGHT 25

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color {
    VGA_COLOR_BLACK = 0x0,
    VGA_COLOR_BLUE = 0x1,
    VGA_COLOR_GREEN = 0x2,
    VGA_COLOR_CYAN = 0x3,
    VGA_COLOR_RED = 0x4,
    VGA_COLOR_MAGENTA = 0x5,
    VGA_COLOR_BROWN = 0x6,
    VGA_COLOR_LIGHT_GREY = 0x7,
    VGA_COLOR_DARK_GREY = 0x8,
    VGA_COLOR_LIGHT_BLUE = 0x9,
    VGA_COLOR_LIGHT_GREEN = 0xA,
    VGA_COLOR_LIGHT_CYAN = 0xB,
    VGA_COLOR_LIGHT_RED = 0xC,
    VGA_COLOR_LIGHT_MAGENTA = 0xD,
    VGA_COLOR_LIGHT_BROWN = 0xE,
    VGA_COLOR_WHITE = 0xF,
    VGA_COLOR_NONE = 0x01E
};
typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
} time;


// fun
void neofetch();
int main();

// terminal
void terminalInit();
void terminalSetColor(enum vga_color color, enum vga_color background);
void print(const char* data);
size_t getTerminalColumn();
size_t getTerminalRow();
void terminalSetCursor(size_t row, size_t column);

void terminalPrint(const char* str, enum vga_color color, enum vga_color background);
void terminalClear(enum vga_color background);

// system
time* getTime();

// convert
const char* int_to_char(int num);
const char* double_to_char(double num);
void memClear(char* str, int size);