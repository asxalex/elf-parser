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

#define print_with_hex(hdr, format, member) \
    printf(format, hdr->member)

static void print_magic(Elf64_Ehdr *hdr);
static void parse_section(FILE *fp, Elf64_Ehdr *hdr);
static void print_type(Elf64_Ehdr *hdr);
static void print_machine(Elf64_Ehdr *hdr);
static void print_version(Elf64_Ehdr *hdr);
static void print_entry(Elf64_Ehdr *hdr);
static void print_phoff(Elf64_Ehdr *hdr);
static void print_shoff(Elf64_Ehdr *hdr);
static void print_flags(Elf64_Ehdr *hdr);
static void print_selfsize(Elf64_Ehdr *hdr);
static void print_phentsize(Elf64_Ehdr *hdr);
static void print_phnum(Elf64_Ehdr *hdr);
static void print_shentsize(Elf64_Ehdr *hdr);
static void print_shnum(Elf64_Ehdr *hdr);
static void print_shstrndx(Elf64_Ehdr *hdr);
void print_header(const char *);
