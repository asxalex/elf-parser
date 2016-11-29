/*
 * elf.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <sys/types.h>
#include <elf.h>
#include <stdlib.h>

#define Elf_Shdr Elf64_Shdr
#define Elf_Ehdr Elf64_Ehdr

#define print_with_hex(hdr, format, member) \
    printf(format, hdr->member)

void print_header(const char *);
