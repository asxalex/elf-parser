/*
 * elf.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef COMMON_H
#define COMMON_H

#include "elf.h"

#define Elf_Shdr Elf64_Shdr
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Sym Elf64_Sym
#define ELF_ST_BIND ELF64_ST_BIND
#define ELF_ST_TYPE ELF64_ST_TYPE
#define Elf_Rela Elf64_Rela
#define ELF_R_SYM ELF64_R_SYM
#define ELF_R_TYPE ELF64_R_TYPE

#define print_with_hex(hdr, format, member) \
    printf(format, hdr->member)

#endif
