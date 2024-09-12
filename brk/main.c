#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("Initial program break: %p\n", sbrk(0));
    int *ptr = malloc(1024);
    printf("program break after malloc: %p\n", sbrk(0));
    free(ptr);
    printf("program break after free: %p\n", sbrk(0));
}