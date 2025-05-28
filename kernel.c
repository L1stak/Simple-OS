#include "src/modules/std.h"
#include "src/modules/math.h"
#include "src/modules/shell/shell.h"


void kernelMain(void) {
    terminalInit();
    terminalClear(VGA_COLOR_BLACK);

    _shell_print_("govnofetch");
    neofetch();
    terminalSetColor(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    print("\nC + NASM = <3");
}
