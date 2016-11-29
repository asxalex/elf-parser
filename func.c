/*
 * elf.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include "func.h"

static void print_magic(Elf_Ehdr *hdr) {
    printf("  Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", hdr->e_ident[i]);
    }
    printf("\n");

    printf("  Class: ");
    switch (hdr->e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
            printf("Invalid class");
            break;
        case ELFCLASS32:
            printf("ELF32");
            break;
        case ELFCLASS64:
            printf("ELF64");
            break;
    }
    printf("\n");

    printf("  Data: ");
    switch(hdr->e_ident[EI_DATA]) {
        case ELFDATANONE:
            printf("Invalid Data Encoding");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian");
            break;
    }
    printf("\n");

    printf("  Version: %d\n", hdr->e_ident[EI_VERSION]);

    printf("  OS/ABI: ");
    switch(hdr->e_ident[EI_OSABI]) {
        case ELFOSABI_NONE:
            printf("UNIX System V ABI.");
            break;
        case ELFOSABI_HPUX:       
            printf("HP-UX.");
            break;
        case ELFOSABI_NETBSD:     
            printf("NetBSD.");
            break;
        case ELFOSABI_GNU:        
            printf("Object uses GNU ELF extensions.");
            break;
        case ELFOSABI_SOLARIS:    
            printf("Sun Solaris.");
            break;
        case ELFOSABI_AIX:        
            printf("IBM AIX.");
            break;
        case ELFOSABI_IRIX:       
            printf("SGI Irix.");
            break;
        case ELFOSABI_FREEBSD:    
            printf("FreeBSD.");
            break;
        case ELFOSABI_TRU64:      
            printf("Compaq TRU64 UNIX");
            break;
        case ELFOSABI_MODESTO:    
            printf("Novell Modesto.");
            break;
        case ELFOSABI_OPENBSD:    
            printf("OpenBSD");
            break;
        case ELFOSABI_ARM_AEABI:  
            printf("ARM EAB");
            break;
        case ELFOSABI_ARM:        
            printf("AR");
            break;
        case ELFOSABI_STANDALONE: 
            printf("Standalone (embedded) applicatio");
            break;
    }
    printf("\n");

    printf("  ABI Version: %d\n", hdr->e_ident[EI_ABIVERSION]);
}

static void print_shtype(Elf_Shdr *shdr) {
   
    printf("  Section type: ");
    switch(shdr->sh_type) {
    case SHT_NULL:      
        printf("Section header table entry unused");
        break;
    case SHT_PROGBITS:      
        printf("Program data");
        break;
    case SHT_SYMTAB:    
        printf("Symbol table");
        break;
    case SHT_STRTAB:    
        printf("String table");
        break;
    case SHT_RELA:      
        printf("Relocation entries with addends");
        break;
    case SHT_HASH:      
        printf("Symbol hash table");
        break;
    case SHT_DYNAMIC:   
        printf("Dynamic linking information");
        break;
    case SHT_NOTE:      
        printf("Notes");
        break;
    case SHT_NOBITS:    
        printf("Program space with no data (bss)");
        break;
    case SHT_REL:       
        printf("Relocation entries, no addends");
        break;
    case SHT_SHLIB:     
        printf("Reserved");
        break;
    case SHT_DYNSYM:    
        printf("Dynamic linker symbol table");
        break;
    case SHT_INIT_ARRAY:    
        printf("Array of constructors");
        break;
    case SHT_FINI_ARRAY:    
        printf("Array of destructors");
        break;
    case SHT_PREINIT_ARRAY: 
        printf("Array of pre-constructors");
        break;
    case SHT_GROUP:     
        printf("Section group");
        break;
    case SHT_SYMTAB_SHNDX:  
        printf("Extended section indeces");
        break;
    case SHT_NUM:       
        printf("Number of defined types.");
        break;
    case SHT_LOOS:      
        printf("Start OS-specific.");
        break;
    case SHT_GNU_ATTRIBUTES: 
        printf("Object attributes.");
        break;
    case SHT_GNU_HASH:      
        printf("GNU-style hash table.");
        break;
    case SHT_GNU_LIBLIST:   
        printf("Prelink library list");
        break;
    case SHT_CHECKSUM:      
        printf("Checksum for DSO content.");
        break;
    case SHT_LOSUNW:    
        printf("Sun-specific low bound. ");
        break;
    case SHT_GNU_verdef:    
        printf("Version definition section. ");
        break;
    case SHT_GNU_verneed:   
        printf("Version needs section.");
        break;
    case SHT_GNU_versym:    
        printf("Version symbol table.");
        break;
    case SHT_LOPROC:    
        printf("Start of processor-specific");
        break;
    case SHT_HIPROC:    
        printf("End of processor-specific");
        break;
    case SHT_LOUSER:    
        printf("Start of application-specific");
        break;
    case SHT_HIUSER:    
        printf("End of application-specific");
        break;
    }
    printf("\n");
}

void print_shflag(Elf_Shdr *shdr) {
    printf("  Flags: \n");
    int flags = shdr->sh_flags;
    if (flags & SHF_WRITE) {
        printf("\tWritable \n");
    }
    if (flags & SHF_ALLOC) {
        printf("\tOccupies memory during execution \n");
    }
    if (flags & SHF_EXECINSTR) {
        printf("\tExecutable \n");
    }
    if (flags & SHF_MERGE) {
        printf("\tMight be merged \n");
    }
    if (flags & SHF_STRINGS) {
        printf("\tContains nul-terminated strings \n");
    }
    if (flags & SHF_INFO_LINK) {
        printf("\t`sh_info' contains SHT index \n");
    }
    if (flags & SHF_LINK_ORDER) {
        printf("\tPreserve order after combining \n");
    }
    if (flags & SHF_OS_NONCONFORMING) {
        printf("\tNon-standard OS specific handling required \n");
    }
    if (flags & SHF_GROUP) {
        printf("\tSection is member of a group.  \n");
    }
    if (flags & SHF_TLS) {
        printf("\tSection hold thread-local data.  \n");
    }
    if (flags & SHF_COMPRESSED) {
        printf("\tSection with compressed data. \n");
    }
    if (flags & SHF_MASKOS) {
        printf("\tOS-specific.  \n");
    }
    if (flags & SHF_MASKPROC) {
        printf("\tProcessor-specific \n");
    }
    if (flags & SHF_ORDERED) {
        printf("\tSpecial ordering requirement (Solaris).  \n");
    }
    if (flags & SHF_EXCLUDE) {
        printf("\tSection is excluded unless referenced or allocated (Solaris).\n");
    }
}

static void parse_each_section(FILE *fp, int sh_off, int sh_num, char *strtab, int stridx) {
    Elf_Shdr shdr;
    fseek(fp, sh_off, SEEK_SET);
    for (int i = 0; i < sh_num; i++) {
        fread(&shdr, sizeof(Elf_Shdr), 1, fp);
        if (!i) {
            continue;
        }
        printf("=== section info for [%s] ===\n", strtab + shdr.sh_name);
        printf("  Section name (string tbl index): %d\n", shdr.sh_name);
        print_shtype(&shdr);
        print_shflag(&shdr);
        printf("  Section virtual addr at execution: %d\n", shdr.sh_addr);
        printf("  Section file offset: %d\n", shdr.sh_offset);
        printf("  Section size in bytes: %d\n", shdr.sh_size);
        printf("  Link to another section: %d\n", shdr.sh_link);
        printf("  Additional section information: %d\n", shdr.sh_info);
        printf("  Section alignment: %d\n", shdr.sh_addralign);
        printf("  Entry size if section holds table: %d\n", shdr.sh_entsize);
        printf("\n");
    }
}

static void parse_section(FILE *fp, Elf_Ehdr *hdr) {
    int i;
    int stridx = hdr->e_shstrndx;
    int sh_num = hdr->e_shnum;
    int sh_off = hdr->e_shoff;
    fseek(fp, hdr->e_shoff + sizeof(Elf_Shdr) * stridx, SEEK_SET);
    Elf_Shdr shdr;
    fread(&shdr, sizeof(Elf_Shdr), 1, fp);
    char *strtab = malloc(sizeof(char) * shdr.sh_size+1);
    fseek(fp, shdr.sh_offset, SEEK_SET);
    fread(strtab, shdr.sh_size, 1, fp);
    parse_each_section(fp, sh_off, sh_num, strtab, stridx);
}

static void print_type(Elf_Ehdr *hdr) {
    printf("  Type: ");
    switch (hdr->e_type) {
        case ET_NONE:     
            printf("No file type");
            break;
        case ET_REL:      
            printf("Relocatable file");
            break;
        case ET_EXEC:     
            printf("Executable file");
            break;
        case ET_DYN:      
            printf("Shared object file");
            break;
        case ET_CORE:     
            printf("Core file");
            break;
        case ET_NUM:      
            printf("Number of defined types");
            break;
        case ET_LOOS:     
            printf("OS-specific range start");
            break;
        case ET_HIOS:     
            printf("OS-specific range end");
            break;
        case ET_LOPROC:   
            printf("Processor-specific range start");
            break;
        case ET_HIPROC:   
            printf("Processor-specific range end");
            break;
    }
    printf("\n");
}

static void print_machine(Elf_Ehdr *hdr) {
    printf("  Machine: ");
    switch(hdr->e_machine) {
        case EM_NONE:         
            printf("No machine");
            break;
        case EM_M32:         
            printf("AT&T WE 32100");
            break;
        case EM_SPARC:     
            printf("SUN SPARC");
            break;
        case EM_386:         
            printf("Intel 80386");
            break;
        case EM_68K:         
            printf("Motorola m68k family");
            break;
        case EM_88K:         
            printf("Motorola m88k family");
            break;
        case EM_IAMCU:     
            printf("Intel MCU");
            break;
        case EM_860:         
            printf("Intel 80860");
            break;
        case EM_MIPS:         
            printf("MIPS R3000 big-endian");
            break;
        case EM_S370:         
            printf("IBM System/370");
            break;
        case EM_MIPS_RS3_LE:    
            printf("MIPS R3000 little-endian");
            break;
        case EM_PARISC:    
            printf("HPPA");
            break;
        case EM_VPP500:    
            printf("Fujitsu VPP500");
            break;
        case EM_SPARC32PLUS:    
            printf("Sun's 'v8plus'");
            break;
        case EM_960:        
            printf("Intel 80960");
            break;
        case EM_PPC:        
            printf("PowerPC");
            break;
        case EM_PPC64:    
            printf("PowerPC 64-bit");
            break;
        case EM_S390:        
            printf("IBM S390");
            break;
        case EM_SPU:        
            printf("IBM SPU/SPC");
            break;
        case EM_V800:        
            printf("NEC V800 series");
            break;
        case EM_FR20:        
            printf("Fujitsu FR20");
            break;
        case EM_RH32:        
            printf("TRW RH-32");
            break;
        case EM_RCE:        
            printf("Motorola RCE");
            break;
        case EM_ARM:        
            printf("ARM");
            break;
        case EM_FAKE_ALPHA:    
            printf("Digital Alpha");
            break;
        case EM_SH:        
            printf("Hitachi SH");
            break;
        case EM_SPARCV9:    
            printf("SPARC v9 64-bit");
            break;
        case EM_TRICORE:    
            printf("Siemens Tricore");
            break;
        case EM_ARC:        
            printf("Argonaut RISC Core");
            break;
        case EM_H8_300:    
            printf("Hitachi H8/300");
            break;
        case EM_H8_300H:    
            printf("Hitachi H8/300H");
            break;
        case EM_H8S:        
            printf("Hitachi H8S");
            break;
        case EM_H8_500:    
            printf("Hitachi H8/500");
            break;
        case EM_IA_64:    
            printf("Intel Merced");
            break;
        case EM_MIPS_X:    
            printf("Stanford MIPS-X");
            break;
        case EM_COLDFIRE:    
            printf("Motorola Coldfire");
            break;
        case EM_68HC12:    
            printf("Motorola M68HC12");
            break;
        case EM_MMA:        
            printf("Fujitsu MMA Multimedia Accelerator");
            break;
        case EM_PCP:        
            printf("Siemens PCP");
            break;
        case EM_NCPU:        
            printf("Sony nCPU embeeded RISC");
            break;
        case EM_NDR1:        
            printf("Denso NDR1 microprocessor");
            break;
        case EM_STARCORE:    
            printf("Motorola Start*Core processor");
            break;
        case EM_ME16:        
            printf("Toyota ME16 processor");
            break;
        case EM_ST100:    
            printf("STMicroelectronic ST100 processor");
            break;
        case EM_TINYJ:    
            printf("Advanced Logic Corp. Tinyj emb.fam");
            break;
        case EM_X86_64:    
            printf("AMD x86-64 architecture");
            break;
        case EM_PDSP:        
            printf("Sony DSP Processor");
            break;
        case EM_PDP10:    
            printf("Digital PDP-10");
            break;
        case EM_PDP11:    
            printf("Digital PDP-11");
            break;
        case EM_FX66:        
            printf("Siemens FX66 microcontroller");
            break;
        case EM_ST9PLUS:    
            printf("STMicroelectronics ST9+ 8/16 mc");
            break;
        case EM_ST7:        
            printf("STmicroelectronics ST7 8 bit mc");
            break;
        case EM_68HC16:    
            printf("Motorola MC68HC16 microcontroller");
            break;
        case EM_68HC11:    
            printf("Motorola MC68HC11 microcontroller");
            break;
        case EM_68HC08:    
            printf("Motorola MC68HC08 microcontroller");
            break;
        case EM_68HC05:    
            printf("Motorola MC68HC05 microcontroller");
            break;
        case EM_SVX:        
            printf("Silicon Graphics SVx");
            break;
        case EM_ST19:        
            printf("STMicroelectronics ST19 8 bit mc");
            break;
        case EM_VAX:        
            printf("Digital VAX");
            break;
        case EM_CRIS:        
            printf("Axis Communications 32-bit emb.proc");
            break;
        case EM_JAVELIN:    
            printf("Infineon Technologies 32-bit emb.proc");
            break;
        case EM_FIREPATH:    
            printf("Element 14 64-bit DSP Processor");
            break;
        case EM_ZSP:        
            printf("LSI Logic 16-bit DSP Processor");
            break;
        case EM_MMIX:        
            printf("Donald Knuth's educational 64-bit proc");
            break;
        case EM_HUANY:    
            printf("Harvard University machine-independent object files");
            break;
        case EM_PRISM:    
            printf("SiTera Prism");
            break;
        case EM_AVR:        
            printf("Atmel AVR 8-bit microcontroller");
            break;
        case EM_FR30:        
            printf("Fujitsu FR30");
            break;
        case EM_D10V:        
            printf("Mitsubishi D10V");
            break;
        case EM_D30V:        
            printf("Mitsubishi D30V");
            break;
        case EM_V850:        
            printf("NEC v850");
            break;
        case EM_M32R:        
            printf("Mitsubishi M32R");
            break;
        case EM_MN10300:    
            printf("Matsushita MN10300");
            break;
        case EM_MN10200:    
            printf("Matsushita MN10200");
            break;
        case EM_PJ:        
            printf("picoJava");
            break;
        case EM_OPENRISC:    
            printf("OpenRISC 32-bit embedded processor");
            break;
        case EM_ARC_COMPACT:    
            printf("ARC International ARCompact");
            break;
        case EM_XTENSA:    
            printf("Tensilica Xtensa Architecture");
            break;
        case EM_VIDEOCORE:    
            printf("Alphamosaic VideoCore");
            break;
        case EM_TMM_GPP:    
            printf("Thompson Multimedia General Purpose Proc");
            break;
        case EM_NS32K:    
            printf("National Semi. 32000");
            break;
        case EM_TPC:        
            printf("Tenor Network TPC");
            break;
        case EM_SNP1K:    
            printf("Trebia SNP 1000");
            break;
        case EM_ST200:    
            printf("STMicroelectronics ST200");
            break;
        case EM_IP2K:        
            printf("Ubicom IP2xxx");
            break;
        case EM_MAX:        
            printf("MAX processor");
            break;
        case EM_CR:        
            printf("National Semi. CompactRISC");
            break;
        case EM_F2MC16:    
            printf("Fujitsu F2MC16");
            break;
        case EM_MSP430:    
            printf("Texas Instruments msp430");
            break;
        case EM_BLACKFIN:    
            printf("Analog Devices Blackfin DSP");
            break;
        case EM_SE_C33:    
            printf("Seiko Epson S1C33 family");
            break;
        case EM_SEP:        
            printf("Sharp embedded microprocessor");
            break;
        case EM_ARCA:        
            printf("Arca RISC");
            break;
        case EM_UNICORE:    
            printf("PKU-Unity & MPRC Peking Uni. mc series");
            break;
        case EM_EXCESS:    
            printf("eXcess configurable cpu");
            break;
        case EM_DXP:        
            printf("Icera Semi. Deep Execution Processor");
            break;
        case EM_ALTERA_NIOS2: 
            printf("Altera Nios II");
            break;
        case EM_CRX:        
            printf("National Semi. CompactRISC CRX");
            break;
        case EM_XGATE:    
            printf("Motorola XGATE");
            break;
        case EM_C166:        
            printf("Infineon C16x/XC16x");
            break;
        case EM_M16C:        
            printf("Renesas M16C");
            break;
        case EM_DSPIC30F:    
            printf("Microchip Technology dsPIC30F");
            break;
        case EM_CE:        
            printf("Freescale Communication Engine RISC");
            break;
        case EM_M32C:        
            printf("Renesas M32C");
            break;
        case EM_TSK3000:    
            printf("Altium TSK3000");
            break;
        case EM_RS08:        
            printf("Freescale RS08");
            break;
        case EM_SHARC:    
            printf("Analog Devices SHARC family");
            break;
        case EM_ECOG2:    
            printf("Cyan Technology eCOG2");
            break;
        case EM_SCORE7:    
            printf("Sunplus S+core7 RISC");
            break;
        case EM_DSP24:    
            printf("New Japan Radio (NJR) 24-bit DSP");
            break;
        case EM_VIDEOCORE3:    
            printf("Broadcom VideoCore III");
            break;
        case EM_LATTICEMICO32: 
            printf("RISC for Lattice FPGA");
            break;
        case EM_SE_C17:    
            printf("Seiko Epson C17");
            break;
        case EM_TI_C6000:    
            printf("Texas Instruments TMS320C6000 DSP");
            break;
        case EM_TI_C2000:    
            printf("Texas Instruments TMS320C2000 DSP");
            break;
        case EM_TI_C5500:    
            printf("Texas Instruments TMS320C55x DSP");
            break;
        case EM_TI_ARP32:    
            printf("Texas Instruments App. Specific RISC");
            break;
        case EM_TI_PRU:    
            printf("Texas Instruments Prog. Realtime Unit");
            break;
        case EM_MMDSP_PLUS:    
            printf("STMicroelectronics 64bit VLIW DSP");
            break;
        case EM_CYPRESS_M8C:    
            printf("Cypress M8C");
            break;
        case EM_R32C:        
            printf("Renesas R32C");
            break;
        case EM_TRIMEDIA:    
            printf("NXP Semi. TriMedia");
            break;
        case EM_QDSP6:    
            printf("QUALCOMM DSP6");
            break;
        case EM_8051:        
            printf("Intel 8051 and variants");
            break;
        case EM_STXP7X:    
            printf("STMicroelectronics STxP7x");
            break;
        case EM_NDS32:    
            printf("Andes Tech. compact code emb. RISC");
            break;
        case EM_ECOG1X:    
            printf("Cyan Technology eCOG1X");
            break;
        case EM_MAXQ30:    
            printf("Dallas Semi. MAXQ30 mc");
            break;
        case EM_XIMO16:    
            printf("New Japan Radio (NJR) 16-bit DSP");
            break;
        case EM_MANIK:    
            printf("M2000 Reconfigurable RISC");
            break;
        case EM_CRAYNV2:    
            printf("Cray NV2 vector architecture");
            break;
        case EM_RX:        
            printf("Renesas RX");
            break;
        case EM_METAG:    
            printf("Imagination Tech. META");
            break;
        case EM_MCST_ELBRUS:    
            printf("MCST Elbrus");
            break;
        case EM_ECOG16:    
            printf("Cyan Technology eCOG16");
            break;
        case EM_CR16:        
            printf("National Semi. CompactRISC CR16");
            break;
        case EM_ETPU:        
            printf("Freescale Extended Time Processing Unit");
            break;
        case EM_SLE9X:    
            printf("Infineon Tech. SLE9X");
            break;
        case EM_L10M:        
            printf("Intel L10M");
            break;
        case EM_K10M:        
            printf("Intel K10M");
            break;
        case EM_AARCH64:    
            printf("ARM AARCH64");
            break;
        case EM_AVR32:    
            printf("Amtel 32-bit microprocessor");
            break;
        case EM_STM8:        
            printf("STMicroelectronics STM8");
            break;
        case EM_TILE64:    
            printf("Tileta TILE64");
            break;
        case EM_TILEPRO:    
            printf("Tilera TILEPro");
            break;
        case EM_MICROBLAZE:    
            printf("Xilinx MicroBlaze");
            break;
        case EM_CUDA:        
            printf("NVIDIA CUDA");
            break;
        case EM_TILEGX:    
            printf("Tilera TILE-Gx");
            break;
        case EM_CLOUDSHIELD:    
            printf("CloudShield");
            break;
        case EM_COREA_1ST:    
            printf("KIPO-KAIST Core-A 1st gen.");
            break;
        case EM_COREA_2ND:    
            printf("KIPO-KAIST Core-A 2nd gen.");
            break;
        case EM_ARC_COMPACT2:    
            printf("Synopsys ARCompact V2");
            break;
        case EM_OPEN8:    
            printf("Open8 RISC");
            break;
        case EM_RL78:        
            printf("Renesas RL78");
            break;
        case EM_VIDEOCORE5:    
            printf("Broadcom VideoCore V");
            break;
        case EM_78KOR:    
            printf("Renesas 78KOR");
            break;
        case EM_56800EX:    
            printf("Freescale 56800EX DSC");
            break;
        case EM_BA1:        
            printf("Beyond BA1");
            break;
        case EM_BA2:        
            printf("Beyond BA2");
            break;
        case EM_XCORE:    
            printf("XMOS xCORE");
            break;
        case EM_MCHP_PIC:    
            printf("Microchip 8-bit PIC(r)");
            break;
        case EM_KM32:        
            printf("KM211 KM32");
            break;
        case EM_KMX32:    
            printf("KM211 KMX32");
            break;
        case EM_EMX16:    
            printf("KM211 KMX16");
            break;
        case EM_EMX8:        
            printf("KM211 KMX8");
            break;
        case EM_KVARC:    
            printf("KM211 KVARC");
            break;
        case EM_CDP:        
            printf("Paneve CDP");
            break;
        case EM_COGE:        
            printf("Cognitive Smart Memory Processor");
            break;
        case EM_COOL:        
            printf("Bluechip CoolEngine");
            break;
        case EM_NORC:        
            printf("Nanoradio Optimized RISC");
            break;
        case EM_CSR_KALIMBA:    
            printf("CSR Kalimba");
            break;
        case EM_Z80:        
            printf("Zilog Z80");
            break;
        case EM_VISIUM:    
            printf("Controls and Data Services VISIUMcore");
            break;
        case EM_FT32:        
            printf("FTDI Chip FT32");
            break;
        case EM_MOXIE:    
            printf("Moxie processor");
            break;
        case EM_AMDGPU:    
            printf("AMD GPU");
            break;
        case EM_RISCV:    
            printf("RISC-V");
            break;
        case EM_BPF:        
            printf("Linux BPF -- in-kernel virtual machine");
            break;
    }
    printf("\n");
}

#define print_with_hex(hdr, format, member) \
    printf(format, hdr->member)

static void print_version(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Version: 0x%02x\n", e_version);
}

static void print_entry(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Entry point address: 0x%x\n", e_entry);
}

static void print_phoff(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Start of program headers: %d\n", e_phoff);
}

static void print_shoff(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Start of section headers: %d\n", e_shoff);
}

static void print_flags(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Flags: 0x%02x\n", e_flags);
}

static void print_selfsize(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Size of this header: %d\n", e_ehsize);
}

static void print_phentsize(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Size of program headers: %d\n", e_phentsize);
}

static void print_phnum(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Number of program headers: %d\n", e_phnum);
}

static void print_shentsize(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Size of section headers: %d\n", e_shentsize);
}

static void print_shnum(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Number of section headers: %d\n", e_shnum);
}

static void print_shstrndx(Elf_Ehdr *hdr) {
    print_with_hex(hdr, "  Section header string table index: %d\n", e_shstrndx);
}

void print_header(const char *filename) {
    Elf_Ehdr hdr;
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "failed to open elf image file [%s]\n", filename);
        exit(-1);
    }

    fread(&hdr, sizeof(Elf_Ehdr), 1, fp);

    parse_section(fp, &hdr);

    printf("ELF Header:\n");
    print_magic(&hdr);
    print_type(&hdr);
    print_machine(&hdr);
    print_version(&hdr);
    print_entry(&hdr);
    print_phoff(&hdr);
    print_shoff(&hdr);
    print_flags(&hdr);
    print_selfsize(&hdr);
    print_phentsize(&hdr);
    print_phnum(&hdr);
    print_shentsize(&hdr);
    print_shnum(&hdr);
    print_shstrndx(&hdr);

    fclose(fp);
}
