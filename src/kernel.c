#define PLATFORM x86
#define IsKernel true
#include "system.h"


void kernelMain(void) {
    
    modules_init();
    

    _shell_print_("govnofetch");
    neofetch();
    terminalSetColor(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    print("\nC + NASM = <3\n");
    //asm("sti");
   // PIC_remap();
     for(;;) {
    asm("hlt");
 }
}
