/*
 * segment.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include "segment.h"
#include "math.h"

static void print_ph_type(int p_type) {
    printf("  p_type: ");
    switch(p_type) {
        case PT_NULL:     
            printf("Program header table entry unused");
            break;
        case PT_LOAD:     
            printf("Loadable program segment");
            break;
        case PT_DYNAMIC:  
            printf("Dynamic linking information");
            break;
        case PT_INTERP:   
            printf("Program interpreter");
            break;
        case PT_NOTE:     
            printf("Auxiliary information");
            break;
        case PT_SHLIB:    
            printf("Reserved");
            break;
        case PT_PHDR:     
            printf("Entry for header table itself");
            break;
        case PT_TLS:      
            printf("Thread-local storage segment");
            break;
        case PT_NUM:      
            printf("Number of defined types");
            break;
        case PT_LOOS:     
            printf("Start of OS-specific");
            break;
        case PT_GNU_EH_FRAME: 
            printf("GCC .eh_frame_hdr segment");
            break;
        case PT_GNU_STACK:    
            printf("Indicates stack executability");
            break;
        case PT_GNU_RELRO:    
            printf("Read-only after relocation");
            break;
        case PT_SUNWBSS:  
            printf("Sun Specific segment");
            break;
        case PT_SUNWSTACK:    
            printf("Stack segment");
            break;
        case PT_HIOS:     
            printf("End of OS-specific");
            break;
        case PT_LOPROC:   
            printf("Start of processor-specific");
            break;
        case PT_HIPROC:   
            printf("End of processor-specific");
            break;
    }
    printf("\n");
}

static void print_ph_offset(int p_offset) {
    printf("  ph_offset: 0x%016x\n", p_offset);
}

static void print_ph_vaddr(int p_vaddr) {
    printf("  ph_vaddr: 0x%016x\n", p_vaddr);
}

static void print_ph_paddr(int p_paddr) {
    printf("  ph_paddr: 0x%016x\n", p_paddr);
}

static void print_ph_filesize(int p_paddr) {
    printf("  ph_filesize: 0x%016x\n", p_paddr);
}

static void print_ph_memsize(int p_paddr) {
    printf("  ph_memsize: 0x%016x\n", p_paddr);
}

static void print_ph_flags(int p_flags) {
    printf("  ph_flags: ");
    if (p_flags & PF_R) {
        printf("Read, ");
    }
    if (p_flags & PF_W) {
        printf("Write, ");
    }
    if (p_flags & PF_X) {
        printf("Executable, ");
    }
    if (p_flags & PF_MASKOS) {
        printf("OS-specific, ");
    }
    if (p_flags & PF_MASKPROC) {
        printf("Processor-specific, ");
    }
    printf("\n");
}

static void print_ph_align(int p_align) {
    printf("  aligments: 0x%x\n", p_align);
}

void print_ph(Elf_Phdr* ph) {
    print_ph_type(ph->p_type);
    print_ph_offset(ph->p_offset);
    print_ph_vaddr(ph->p_vaddr);
    print_ph_paddr(ph->p_paddr);
    print_ph_filesize(ph->p_filesz);
    print_ph_memsize(ph->p_memsz);
    print_ph_flags(ph->p_flags);
    print_ph_align(ph->p_align);
    printf("\n");
}

Elf_Phdr *get_phdr(FILE *fp, Elf_Ehdr *ehdr){
    long restore = ftell(fp);
    Elf_Phdr *res = NULL;
    int offset = ehdr->e_phoff;
    fseek(fp, offset, SEEK_SET);

    int size = ehdr->e_phnum * ehdr->e_phentsize;
    res = malloc(size);
    if (!res) {
        fprintf(stderr, "failed to alloc for program header\n");
        exit(-1);
    }

    fread(res, ehdr->e_phentsize, ehdr->e_phnum, fp);

    fseek(fp, restore, SEEK_SET);
    return res;
}

