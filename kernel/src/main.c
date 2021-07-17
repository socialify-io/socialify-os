#include "font.h"

void render_menu() {
    screen_clear(COLOR(0, 0, 0));

    const char *name = "SocialifyOS";
    font_str(
        name,
        1,
        1,
        11 % 2 == 0 ?
            COLOR(1, 6, 2) :
            COLOR(7, 7, 3)
    );
}

void _main(u32 magic) {
    screen_init();

    while (true) {
        render_menu();
        screen_swap();
    }
}
