#include "new_user.h"
#include "../models/models.h"
#include "../../../drivers/screen.h"

void create_new_user(struct NewUser new_user) {
    kprint(new_user.username);
    kprint(new_user.password);
}