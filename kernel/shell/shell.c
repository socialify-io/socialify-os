#include "shell.h"
#include "../../drivers/screen.h"
#include "../../libc/string.h"
#include "../../libc/mem.h"
#include "../users/users.h"

void init_shell() {
    kprint("SocialifyOS>");
}

void user_input(char *input) {
    char *input_command;
    int input_length = sizeof(input);

    for (int i=0; i<=input_length; i++) {
        if (input[i] == ' ' || input[i] == '\0') {
            input_command[i] = '\0';
            break;
        } else {
            input_command[i] = input[i];
        }
    }

    if (strcmp(input, "end") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "help") == 0) {
        kprint("It's a prnak bro, nic tu kurwa nie znajdziesz, szach mat.\n");
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    } else if (strcmp(input_command, "user") == 0) {
        users_command_handler(input);
    } else {
        kprint("Command not found. Type \"help\" to get list of commands.");
    }
    
    kprint("\nSocialifyOS>");
}