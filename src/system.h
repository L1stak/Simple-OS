#pragma once
#if PLATFORM == x86  // бита
#include "x86/modules/std.h"
#include "modules/math.h"
#include "modules/shell/shell.h"
#include "modules/vector.h"

#include "modules/Interrupts/IRQ.h"
#include "modules/GDT/gdt.h"

#elif PLATFORM == x64

#include "x64/modules/std.h" // 64 бита
#include "modules/math.h"
#include "modules/shell/shell.h"
#include "modules/vector.h"

#include "modules/Interrupts/IRQ.h"
#include "modules/GDT/gdt.h"
#endif
void modules_init() {

    heap_init();
    terminalInit();
    terminalClear(VGA_COLOR_BLACK);
    init_gdt();
    idt_init();
}