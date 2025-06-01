#include "shellScript.h"

void _shell_print_(const char* str) {
    time* t = getTime();

    terminalSetColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    if (getTerminalColumn() != 0) {
        terminalSetCursor(getTerminalRow() + 1, 0);
    }
    print("$> ");
    terminalSetCursor(getTerminalRow(), 3);
    print(str);
    terminalSetCursor(getTerminalRow(), VGA_TERMINAL_WIDTH - 8);
    terminalSetColor(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
    print(int_to_char(t->hours)); print(":"); print(int_to_char(t->minutes)); print(":"); print(int_to_char(t->seconds));
}