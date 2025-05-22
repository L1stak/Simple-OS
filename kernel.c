#include <stdbool.h>
#include "src/modules/terminal/std.h"

void kernelMain(void) {
    terminalPrint("Hello!",VGA_COLOR_RED, VGA_COLOR_NONE);
    terminalPrint("C + NASM = <3",VGA_COLOR_LIGHT_RED, VGA_COLOR_BLUE);
}
