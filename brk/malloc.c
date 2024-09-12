#include <unistd.h>

typedef struct s_memblock {
    unsigned int size;
    struct s_memblock *next;
    int free;
} t_memblock;

#define MEMBLOCK_SIZE sizeof(t_memblock)

void *memblock_head = NULL;

t_memblock *find_free_block(t_memblock **last, int size) {
    t_memblock *head = memblock_head;

    while (head && !(head->free && head->size >= size)) {
        *last = head;
        head = head->next;
    }
    return head;
}

t_memblock *request_block(t_memblock *last, unsigned int size) {
    t_memblock *block;
    block = sbrk(0);
    void *request = sbrk(size + MEMBLOCK_SIZE);
    if (request == (void*)-1)
        return (void*)0;
    block->size = size;
    block->next = NULL;
    block->free = 0;
    if (last)
        last->next = block;
    return block;
}

void *malloc(unsigned int size) {
    void *p = sbrk(0);
    t_memblock *last;
    t_memblock *block;
    if (!memblock_head) {
        block = request_block(NULL, size);
        if (!block)
            return (void*)0;
        memblock_head = block;
    } else {
        block = find_free_block(&last, size);
        if (!block) {
            block = request_block(last, size);
            if (!block)
                return (void*)0;
        } else
            block->free = 0;
    }
    return block + 1; // (void*)block + MEMBLOCK_SIZE
}

t_memblock *get_block_ptr(void *ptr) {
    return (t_memblock*)ptr - 1; // ptr - MEMBLOCK_SIZE
}

void free(void *ptr) {
    if (!ptr)
        return ;

    t_memblock *block = get_block_ptr(ptr);
    block->free = 0;
}

int main() {
    char *ptr = (char*)malloc(sizeof(int));
    *ptr = 'a';
    write(1, ptr, 1);
    free(ptr);
}