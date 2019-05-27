/*
 * (Hopefully) Safe memory allocation and deallocation
 * uses linked lists
 */

#ifndef __mem_h__
#define __mem_h__

#include <stddef.h>

struct mem_block {
        void *memory;
        size_t size;
        struct mem_block *next;
        struct mem_block *prev;
};

/*
 * Allocate memory, creates a new chain if one doesn't exist
 */
void *mem_alloc(size_t size);

/*
 * Deallocate a block of memory and stitch the list back up
 */
void mem_free(void *ptr);

/*
 * Deallocate all allocated memory
 */
void mem_free_all(void);

/*
 * Print out the current list, mainly for debugging and testing
 */
void mem_print_list(void);

#endif // __mem_h__
