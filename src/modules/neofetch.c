#include "std.h"

void color0() {
    terminalSetColor(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
}
void color1() {
    terminalSetColor(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
}


void neofetch() {
    color0();
    print("    /\\          "); color1(); print("OS: GovnoOS\n"); color0();  
    print("   ( /)         "); color1(); print("Kernel: GovnoKernel\n"); color0();
    print("  (/  /)        "); color1(); print("CPU: i686\n"); color0();
    print(" (__/__/)       "); color1(); print("RAM: 512MB\n"); color0(); //Да, я не умею юзать %d
    print("(_/__/__/)      "); color1(); print("Resolution: "); print(int_to_char(VGA_TERMINAL_WIDTH)); print("x"); print(int_to_char(VGA_TERMINAL_HEIGHT)); print("\n"); color0();
}