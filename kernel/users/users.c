#include "users.h"
#include "../../drivers/screen.h"
#include "../../libc/string.h"
#include "../../libc/mem.h"
#include "../../libc/bool.h"

#define COMMAND_LENGTH 4

/* Declaration of private functions */
void user_command_handler(char operation[], char attributes[][256]);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * User command struct : user <operation> -[attributes]
 */
void users_command_parser(char *command) {
    /**
     * Getting amount of given attributes an getting an operation
     */
    bool isOperation = false;
    char operation[256] = { 0 };
    
    int amount_of_attributes = 0;
    int i = COMMAND_LENGTH;

    while (command[i] != '\0') {
        if (command[i] == ' ' && command[i+1] != ' ' && command[i+1] != '\0') {
            if (command[i+1] == '-') {
                if (isOperation == false) {
                    kprint("Operation must be firstly defined.\n");
                    return;
                } else {
                    amount_of_attributes++;
                    i++;
                }
            } else {
                if (isOperation == false) {
                    isOperation = true;
                    i++;
                    while (command[i] != ' ' && command[i] != '\0') {
                        append(operation, command[i]);
                        i++;
                    }
                } else {
                    kprint("To many operations in command. Allowed amount of operations is 1.\n");
                    return;
                }
            }
        } else i++;
    }

    /**
     * Getting attributes
     */
    char attributes[amount_of_attributes][256];

    int actual_number_of_attribute = 0;

    i = COMMAND_LENGTH;

    while (command[i] != '\0') {
        if (command[i] == ' ' && command[i+1] != ' ' && command[i+1] != '\0') {
            if (command[i+1] == '-') {
                i+=2;
                while (command[i] != ' ' && command[i] != '\0') {
                    append(attributes[actual_number_of_attribute], command[i]);
                    i++;
                }
                actual_number_of_attribute++;
            } else i++;
        } else i++;
        
    }

    user_command_handler(operation, attributes);
    memory_set(&operation[0], 0, sizeof(operation));
    memory_set(&attributes[0][0], 0, sizeof(attributes));
}

/**********************************************************
 * Private kernel functions                               *
 **********************************************************/

void user_command_handler(char operation[], char attributes[][256]) {
    kprint("operation: ");
    kprint(operation);
    kprint("\nfirst attribute: ");
    kprint(attributes[0]);
}
