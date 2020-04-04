#ifndef PAGING_H
#define PAGING_H

#include "../cpu/interrupt/handling.h"
#include "../cpu/type.h"

/**
 * Page Struct (a.k.a.) Page Descriptor 32-bit word
 */
typedef struct {
    bool present : 1;    /* Page present in memory? */
    bool rw : 1;         /* Read-only if 0, read-write if 1 */
    bool user : 1;       /* Kernel-mode if 0, user-mode if 1 */
    bool accessed : 1;   /* Has the page been accessed since the last refresh? */
    bool dirty : 1;      /* Has the page been written to since the last refresh? */
    uint8_t unused : 7;  /* Unused and reserved bits */
    uint32_t frame : 20; /* Frame address (shifted right 12 bits) */
} page_t;

/**
 * Page Table
 */
typedef struct {
    page_t pages[1024];
} page_table_t;

/**
 * Page Directory
 */
typedef struct {
    /* Pointers to page tables. */
    page_table_t *tables[1024];

    /* Page tables' physical addresses, for loading into the CR3 register. */
    uint32_t tables_physical_addresses[1024];

    /* The current directory's physical address. Used when cloning. */
    uint32_t physical_address;

} page_directory_t;

/**
 * Paging initialization
 */
void init_paging();

/**
 * Loads a page directory into the CR3 register.
 */
void load_page_directory(page_directory_t *page_directory);

/**
 * Gets a pointer to the page required.
 */
page_t *get_page(page_directory_t *page_directory, uint32_t address, bool create_if_null);

/**
 * Page fault handler
 */
void page_fault(registers_t regs);

#endif /* PAGING_H */
