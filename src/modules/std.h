#pragma once
#define VGA_TERMINAL_WIDTH 80
#define VGA_TERMINAL_HEIGHT 25

#include <stdbool.h>
#include <stddef.h>

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
    const char* str;
    enum vga_color color;
    enum vga_color background;
} terminal;
typedef struct {
    terminal data[100];
    int size;
} terminalVector;
extern terminalVector terminalData;



// system
// FIXME
void sleep(int seconds);

void print(const char* str);
const char* input();

int getRAM();
int size(const char* str);

// terminal
void terminalPrint(const char* str, enum vga_color color, enum vga_color background);
void terminalClear(enum vga_color background);
void terminalInit();
void terminalPush(const char* str, enum vga_color color, enum vga_color background);

// convert
const char* int_to_char(int num);