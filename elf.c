/*
 * elf.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include "section.h"
#include "segment.h"

void dump_section_info(FILE *fp) {
    long restore = ftell(fp);
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
    printf("==== start for dump symbols ====\n");
    for (i = 0; i < size; i++) {
        print_symbol(&symbols[i], strtab);
        printf("\n");
    }

    // print relocation of text.
    printf("\ndump for text's relocation info\n");
    Elf_Shdr *rela_text = get_shdr_by_name(shdr, ehdr->e_shnum, ".rela.text", shstrtab);
    if (!rela_text) {
        printf("no [.rela.text] section found\n");
    } else {
        Elf_Rela *relocation = get_relocation(fp, rela_text);
        int size = rela_text->sh_size / rela_text->sh_entsize;
        for (i = 0; i < size; i++) {
            print_relocation_info(&(relocation[i]), symbols, strtab);
        }
    }

    free(ehdr);
    free(strtab);
    free(shstrtab);
    free(symbols);
    free(shdr);
    fseek(fp, restore, SEEK_SET);
}

void dump_segment_info(FILE *fp) {
    long restore = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    Elf_Ehdr *ehdr = get_ehdr(fp);
    Elf_Phdr *phdr = get_phdr(fp, ehdr);
    int i; 
    for (i = 0; i < ehdr->e_phnum; i++) {
        print_ph(&phdr[i]);
    }

    free(ehdr);
    free(phdr);
    fseek(fp, restore, SEEK_SET);
}


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
    dump_section_info(fp);
    dump_segment_info(fp);
    fclose(fp);
}
