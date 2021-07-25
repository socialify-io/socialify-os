#ifndef DICT_H
#define DICT_H

struct dict_element {
    char *name;
    void *value;
};

#define dict dict_element[]

#endif