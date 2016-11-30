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

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "failed to open elf file [%s], quiting...\n", filename);
        exit(-1);
    }

    Elf_Ehdr *ehdr = get_ehdr(fp);
    Elf_Shdr *shdr = get_shdr(fp, ehdr);
    char *shstrtab = get_shstrtab(fp, ehdr, shdr);
    Elf_Shdr *symtab = get_shdr_by_name(shdr, ehdr->e_shnum, ".symtab", shstrtab);
    char *strtab = get_strtab(fp, shdr, ehdr, shstrtab);
    int sh_size = ehdr->e_shnum;
    
    // print header
    print_header(ehdr);
    printf("\n");

    // print section
    int i;
    for (i = 0; i < ehdr->e_shnum; i++) {
        print_section(shdr+i, shstrtab, strtab);
    }
    printf("\n");

    // print symbols
    Elf_Sym *symbols = get_symbol(fp, symtab);
    int size = symtab->sh_size / symtab->sh_entsize;
    printf(" start for dump symbols ====\n");
    for (i = 0; i < size; i++) {
        print_symbol(&symbols[i], strtab);
        printf("\n");
    }
    fclose(fp);
    free(ehdr);
    free(strtab);
    free(shstrtab);
    free(symbols);
    free(shdr);
    return 0;
}

