#include "users.h"
#include "../../drivers/screen.h"

#define COMMAND_LENGTH 5

/**
 * User command struct : user <operation> [attributes]
 */
void users_command_handler(char *input) {
    char *operation;
    int input_length = sizeof(input);

    //int i=COMMAND_LENGTH;
    int j=0;
    for (int i=COMMAND_LENGTH; i>=input_length; i++) {
        if (input[i] == ' ' || input[i] == '\0') {
            operation[j] = '\0';
            break;
        } else {
            operation[j] = input[i];
            j++;
        }
    }


    // do {
    //     operation[j] = input[i];
    //     kprint("dupa");
    //     i++;
    //     j++;
    // } while (input[i] != ' ' || input[i] != '\0');

    operation[j] = '\0';

    kprint("\nOPERATION: ");
    kprint(operation);

    // int operation_length = sizeof(operation);
    // char **attributes;
    // j=0;
    // int k=0;

    // for (int i=COMMAND_LENGTH+operation_length; i>=input_length; i++) {
    //     if (input[i] == ' ') {
    //         attributes[k][j] = '\0';
    //         kprint("\n");
    //         kprint(attributes[k]);
    //         k++;
    //     } else if (input[i] == '\0') {
    //         attributes[k][j] = '\0';
    //         break;
    //     } else {
    //         attributes[k][j] = input[i];
    //         j++;
    //     }
    // }


    // while (input[i] != '\0') {
    //     while (input[i] != ' ' || input[i] != '\0') {
    //         attributes[k][j] = input[i];
    //         i++;
    //         j++;
    //     }
    //     attributes[k][j+1] = '\0';
    //     k++;
    // }

}