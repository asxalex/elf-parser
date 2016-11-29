/*
 * elf.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include "func.h"

int main(int argc, char *argv[]) {
    char *filename;
    if (argc <= 1) {
        filename = "SimpleSection.o";
    } else {
        filename = argv[1];
    }
    print_header(filename);
    return 0;
}

