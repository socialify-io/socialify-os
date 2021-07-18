#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"

void main() {
    isr_install();
    irq_install();

    clear_screen();

    kprint("SocialifyOS>");
}

void user_input(char *input) {
    if (strcmp(input, "end") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "help") == 0) {
        kprint("It's a prnak bro, nic tu kurwa nie znajdziesz, szach mat.\n");
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    } else {
        kprint("Command not found. Type \"help\" to get list of commands.");
    }
    
    kprint("\nSocialifyOS>");
}
