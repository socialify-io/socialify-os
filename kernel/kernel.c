#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "shell/shell.h"

void main() {
    isr_install();
    irq_install();

    clear_screen();

    init_shell();
}
