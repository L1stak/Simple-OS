#include <stdbool.h>
#include "src/modules/terminal/std.h"

void kernelMain(void) {
    terminalClear(VGA_COLOR_CYAN);
    terminalPrint("C + NASM = <3", VGA_COLOR_RED, VGA_COLOR_GREEN);
}
