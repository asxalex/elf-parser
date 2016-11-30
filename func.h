/*
 * elf.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <sys/types.h>
#include "elf.h"
#include <stdlib.h>
#include <string.h>

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

void print_header(Elf_Ehdr *hdr);

Elf_Ehdr* get_ehdr(FILE *fp);

Elf_Shdr* get_shdr_by_name(Elf_Shdr* , int , const char *, char *);

char* get_shstrtab(FILE *fp, Elf_Ehdr* hdr, Elf_Shdr *shdr);
char* get_strtab(FILE *fp, Elf_Shdr *shdr, Elf_Ehdr *ehdr, char *s);
Elf_Shdr* get_shdr(FILE *fp, Elf_Ehdr *hdr);
void print_section(Elf_Shdr *shdr, char *shstr, char *strtab);
void print_symbol(Elf_Sym *symbol, char *strtab);
Elf_Sym* get_symbol(FILE *fp, Elf_Shdr *symtab);
Elf_Rela* get_relocation(FILE *fp, Elf_Shdr *rel);
void print_relocation_info(Elf_Rela* r, Elf_Sym* sym, char *);
