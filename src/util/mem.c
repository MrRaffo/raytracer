#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // strerror
#include <errno.h>

#include <util/mem.h>
#include <util/log.h>

struct mem_block *mem_list = NULL;
struct mem_block *mem_top = NULL;
static size_t mem_requested = 0;
static size_t mem_total = 0;
static int mem_requests = 0;


/*
 * Allocates memory, aborts program if unsuccessful
 */
void *_checked_malloc(size_t size)
{
        void *ptr = malloc(size);
        if (ptr == NULL) {
                log_err("Unable to allocate memory!\n");
                fprintf(stderr, "%s\n", strerror(errno));
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
                mem_top = mem_list;
                mem_ptr = mem_list->memory;
        } else {
                // traverse mem_list to get to last entry
                mem_top->next = _create_mem_block(size);
                mem_top->next->prev = mem_top;
                mem_top->next->next = NULL;
                mem_ptr = mem_top->next->memory;
                mem_top = mem_top->next;
        }

        mem_requested += size;
        mem_total += size + sizeof(struct mem_block);
        mem_requests++;

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
        
        mem_requested -= mblock->size;
        mem_total -= (mblock->size + sizeof(struct mem_block));
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

/*
 * Show the amount of memory currently in use
 */
void mem_print(void)
{
        log_msg("[MEM USE] %ld (%ld KB)", mem_requested, mem_requested / 1024);
        log_msg("[MEM TOT] %ld (%ld KB)", mem_total, mem_total / 1024);
        log_msg("[MEM REQ] %d successful alloc requests", mem_requests);
}

