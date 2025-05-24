#include "src/modules/std.h"

void kernelMain(void) {
    //terminalClear(VGA_COLOR_DARK_GREY);
    //terminalPrint("I love C/C++ (And im debil and ne umeu pisat' code). C + NASM = <3", VGA_COLOR_LIGHT_RED, VGA_COLOR_LIGHT_GREY);
    terminalInit();

    terminalSetColor(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_CYAN);
    print("Test\n");
    terminalSetColor(VGA_COLOR_LIGHT_RED, VGA_COLOR_LIGHT_GREEN);
    print("I love C/C++\n");
}
