#include "users.h"
#include "../../drivers/screen.h"
#include "../../libc/string.h"
#include "../../libc/mem.h"
#include "../../libc/bool.h"
#include "../../libc/dict.h"

#define COMMAND_LENGTH 4

/* Declaration of private functions */
void user_command_handler(char operation[256], char attributes[][2][256]);

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
                } else i++;
            }
        } else i++;
    }

    /**
     * Getting attributes
     */
    char attributes[amount_of_attributes][2][256];
    int actual_number_of_attribute = 0;

    i = COMMAND_LENGTH;
    while (command[i] != '\0') {
        if (command[i] == ' ' && command[i+1] != ' ' && command[i+1] != '\0') {
            if (command[i+1] == '-') {
                i+=2;
                bool is_attribute_taken = false;
                while (true) {
                    if (is_attribute_taken == false) {
                        if (command[i] == ' ' || command[i] == '\0') {
                            is_attribute_taken = true;
                        } else {
                            append(attributes[actual_number_of_attribute][0], command[i]);
                        }
                    } else { 
                        if (command[i] == ' ' || command[i] == '\0') break;
                        else append(attributes[actual_number_of_attribute][1], command[i]);
                    }
                    i++;
                }
                actual_number_of_attribute++;
            } else i++;
        } else i++;
    }

    user_command_handler(operation, attributes);
    memory_set(&command[0], 0, sizeof(command));
    memory_set(&operation[0], 0, sizeof(operation));
    memory_set(&attributes[0][0][0], 0, sizeof(attributes));
}

/**********************************************************
 * Private kernel functions                               *
 **********************************************************/

void user_command_handler(char operation[256], char attributes[][2][256]) {
    if (strcmp(operation, "new") == 0) {
        kprint(attributes[0][1]);
    } else if (strcmp(operation, "list") == 0) {
        kprint("\nDisplaying list of users...");
    } else {
        kprint("\nOperation not recognized.");
    }
}
