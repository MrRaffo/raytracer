#include <stdio.h>
#include <stdlib.h>

#include <util/mem.h>
#include <util/log.h>

struct mem_block *mem_list = NULL;

/*
 * Allocates memory, aborts program if unsuccessful
 */
void *_checked_malloc(size_t size)
{
        void *ptr = malloc(size);
        if (ptr == NULL) {
                log_err("Unable to allocate memory!\n");
                mem_free_all();
                exit(1);
        }

        return ptr;
}

/*
 * Creates a new mem_block entry to mem_block list and allocates the
 * desired amount of memory
 */
struct mem_block *_create_mem_block(size_t size)
{
        struct mem_block *ptr = (struct mem_block *)_checked_malloc(sizeof(struct mem_block));

        ptr->next = NULL;
        ptr->prev = NULL;
        ptr->memory = _checked_malloc(size);
        ptr->size = size;

        return ptr;
}

/*
 * Traverses the list, looking for the mem_block entry with a 'memory'
 * pointer equal to that of the passed pointer, returns NULL on fail
 */
struct mem_block *_find_mem_block(void *ptr)
{
        struct mem_block *mblock = mem_list;
        while (mblock != NULL && mblock->memory != ptr) {
                mblock = mblock->next;
        }
        
        if (mblock == NULL) { return NULL; }
        return (mblock->memory == ptr) ? mblock : NULL;
}
 #
/*
 * Allocate memory, creates a new chain if one doesn't exist
 */
void *mem_alloc(size_t size)
{
        void *mem_ptr = NULL;

        // create the linked list if it doesn't exist
        if (mem_list == NULL) {
                mem_list = _create_mem_block(size);
                mem_ptr = mem_list->memory;
        } else {
                // traverse mem_list to get to last entry
                struct mem_block *ptr = mem_list;
                while (ptr->next != NULL) {
                        ptr = ptr->next;
                }
                
                ptr->next = _create_mem_block(size);
                ptr->next->prev = ptr;
                mem_ptr = ptr->next->memory;
        }

        return mem_ptr;
}

/*
 * Returns the size of the memory alloc request, note this is NOT necessarily
 * the size of the memory buffer created by malloc
 */
size_t mem_get_size(void *ptr)
{
        if (ptr == NULL) return 0;

        struct mem_block *mblock = _find_mem_block(ptr);
        return mblock->size;
}

/*
 * Deallocate a block of memory and stitch the list back up
 */
void mem_free(void *ptr)
{
        if (mem_list == NULL) {
                log_err("Invalid free call, no allocated memory\n");
                return;
        }

        struct mem_block *mblock = _find_mem_block(ptr);
        if (mblock == NULL) {
                log_err("Free failed, memory not found\n");
                return;
        }

        free(mblock->memory);

        if (mblock == mem_list && mblock->next != NULL) { mem_list = mblock->next; }
        if (mblock->prev != NULL) { mblock->prev->next = mblock->next; }
        if (mblock->next != NULL) { mblock->next->prev = mblock->prev; }

        free(mblock);

        return;
}

/*
 * Deallocate all allocated memory
 */
void mem_free_all(void)
{
        struct mem_block *ptr = mem_list;
        struct mem_block *next = NULL;
        while (ptr != NULL) {
                next = ptr->next;
                free(ptr->memory);
                free(ptr);
                ptr = next;
        }

        mem_list = NULL;

        return;
}

/*
 * Print out the current list, mainly for debugging and testing
 */
void mem_print_list(void)
{
        struct mem_block *ptr = mem_list;
        while (ptr != NULL) {
                log_dbg("[MEMBLK] %zu bytes", ptr->size);
                ptr = ptr->next;
        }
}
