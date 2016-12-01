/*
 * segment.h
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define Elf_Phdr Elf64_Phdr


Elf_Phdr *get_phdr(FILE *fp, Elf_Ehdr *hdr);
void print_ph(Elf_Phdr* ph);

#endif /* !SEGMENT_H */
