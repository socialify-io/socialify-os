#include "users.h"
#include "../../drivers/screen.h"
#include "../../libc/string.h"

#define COMMAND_LENGTH 4

/**
 * User command struct : user <operation> -[attributes]
 */
void users_command_handler(char *command) {
    /**
     * Getting amount of given parameters
     */
    int amount_of_operations = 0;
    int amount_of_attributes = 0;
    int i = 0;

    while (command[i] != '\0') {
        if (command[i] == ' ' && command[i+1] != ' ' && command[i+1] != '\0') {
            if (command[i+1] == '-') {
                amount_of_attributes++;
            } else {
                amount_of_operations++;
            }
        }
        i++;
    }

    /**
     * Getting given parameters
     */
    char operations[amount_of_operations][256];
    char attributes[amount_of_attributes][256];

    int actual_number_of_operation = 0;
    int actual_number_of_attribute = 0;

    i = COMMAND_LENGTH;
    
    while (command[i] != '\0') {
        if (command[i] == ' ' && command[i+1] != ' ' && command[i+1] != '\0') {
            if (command[i+1] == '-') {
                int j = 0;
                i+=2;
                while (command[i] != ' ' && command[i] != '\0') {
                    attributes[actual_number_of_attribute][j] = command[i];
                    i++;
                    j++;
                }
                actual_number_of_attribute++;
            } else {
                int j = 0;
                i++;
                while (command[i] != ' ' && command[i] != '\0') {
                    operations[actual_number_of_operation][j] = command[i];
                    i++;
                    j++;
                }
                actual_number_of_operation++;
            }
        } else i++;
    }
}
