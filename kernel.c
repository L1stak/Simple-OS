#include "src/modules/std.h"

void kernelMain(void) {
    terminalInit();
    terminalClear(VGA_COLOR_BLACK);

    terminalSetColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    print("$ govnofetch\n");
    neofetch();
    terminalSetColor(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    print("\nC + NASM = <3");
}
