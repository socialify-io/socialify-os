#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include "../libc/bool.h"
#include "../kernel/shell/shell.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define CAPSLOCK 0x3A

#define LSHIFT_PUSH 0x2A
#define LSHIFT_RELEASE LSHIFT_PUSH+0x80

#define RSHIFT_PUSH 0x36
#define RSHIFT_RELEASE RSHIFT_PUSH+0x80

#define LEFT_ARROW 0x4B
#define RIGHT_ARROW 0x4D

char key_buffer[256];

int user_input_actual_char;
int user_input_max_char;

bool capslock_toogle = false;

int toUpper(int ch)
{
    if(ch>='a' && ch<='z')
    return('A' + ch - 'a');
    else
    return(ch);
}

#define SC_MAX 61
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar", "Capslock", "LeftArrow", "RightArrow"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', 'E', ' ', '?', '?', '?', '?'};

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    
    if (scancode == BACKSPACE) {
        if (user_input_actual_char > 0)  {
            backspace(key_buffer);
            kprint_backspace(user_input_max_char, user_input_actual_char);
            user_input_actual_char--;
            user_input_max_char--;
        }
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
        user_input_actual_char = 0;
        user_input_max_char = 0;
    } else if (scancode == CAPSLOCK || 
            scancode == LSHIFT_PUSH ||
            scancode == LSHIFT_RELEASE ||
            scancode == RSHIFT_PUSH ||
            scancode == RSHIFT_RELEASE) {
        capslock_toogle = !capslock_toogle;
    } else if (scancode == LEFT_ARROW) {
        if (user_input_actual_char > 0)  {
            cursor_left();
            user_input_actual_char--;
        }
    } else if (scancode == RIGHT_ARROW) {
        if (user_input_actual_char < user_input_max_char)  {
            cursor_right();
            user_input_actual_char++;
        }
    } else {
        if (scancode > SC_MAX) return;
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        
        if (capslock_toogle == true) {
            letter = toUpper(letter);
        }

        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint_user(str, user_input_max_char, user_input_actual_char);
        user_input_actual_char++;
        user_input_max_char++;
    }
    UNUSED(regs);
}


void init_keyboard() {
    key_buffer[0] = '\0';
    register_interrupt_handler(IRQ1, keyboard_callback); 
}
