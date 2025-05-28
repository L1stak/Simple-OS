#include "keyboard.h"
#include "../std.h"
void keyboard_IRQ(uint16_t code){

terminalClear(VGA_COLOR_BLACK);
terminalSetColor(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
print("KEYBOARD BUTTON PRESSED");



}