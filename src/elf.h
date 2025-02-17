/*
 * rv32emu is freely redistributable under the MIT License. See the file
 * "LICENSE" for information on usage and redistribution of this file.
 */

#pragma once

/* A minimal ELF parser */

#include <stdint.h>

#include "io.h"
#include "map.h"
#include "riscv.h"

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;

enum {
    EI_MAG0 = 0, /* ELF magic value */
    EI_MAG1 = 1,
    EI_MAG2 = 2,
    EI_MAG3 = 3,
    EI_CLASS = 4,   /* ELF class, one of ELF_IDENT_CLASS_ */
    EI_DATA = 5,    /* Data type of the remainder of the file */
    EI_VERSION = 6, /* Version of the header, ELF_IDENT_VERSION_CURRENT */
    EI_OSABI = 7,
    EI_ABIVERSION = 8,
    EI_PAD = 9, /* nused padding */
    EI_NIDENT = 16,
};

struct Elf32_Sym {
    Elf32_Word st_name;
    Elf32_Addr st_value;
    Elf32_Word st_size;
    uint8_t st_info;
    uint8_t st_other;
    Elf32_Half st_shndx;
};

typedef struct elf_internal elf_t;

elf_t *elf_new();
void elf_delete(elf_t *e);

/* Open an ELF file from specified path */
bool elf_open(elf_t *e, const char *path);

/* Find a symbol entry */
const struct Elf32_Sym *elf_get_symbol(elf_t *e, const char *name);

/* Find symbol from a specified ELF file */
const char *elf_find_symbol(elf_t *e, uint32_t addr);

/* get the range of .data section from the ELF file */
bool elf_get_data_section_range(elf_t *e, uint32_t *start, uint32_t *end);

/* Load the ELF file into a memory abstraction */
bool elf_load(elf_t *e, riscv_t *rv, memory_t *mem);
