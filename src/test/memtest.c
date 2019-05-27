#include <stdio.h>
#include <util/mem.h>
#include <util/log.h>

/*
 * Tests adding and removing and destroying a chain of mem_blocks
 */
int TST_MemTest()
{
        // test freeing when no memory allocated
        mem_free(NULL);
        mem_free(1234);

        void *ptr1 = mem_alloc(1024);
        void *ptr2 = mem_alloc(2048);
        void *ptr3 = mem_alloc(4096);
        void *ptr4 = mem_alloc(8192);

        // should show the 4 entries
        log_out("Testing memory, 4 entries:\n");
        mem_print_list();

        mem_free(ptr3);
        ptr3 = NULL;    // be responsible

        // shows 3, with 4096 gone
        log_out("\nOne entry deleted:\n");
        mem_print_list();

        void *ptr5 = mem_alloc(512);
        log_out("\nNew entry added:\n");
        mem_print_list();

        // what happens if the first entry is removed?
        mem_free(ptr1);
        log_out("\nFirst entry removed:\n");
        mem_print_list();

        mem_free_all();
        log_out("\nMemory list destroyed:\n");
        mem_print_list();

        return 1;
}

int main()
{
        TST_MemTest();

        return 0;
}
