#include <stddef.h>
#include <stdio.h>

#define POOL_SIZE 100

struct pool_slice {
    int *start;
    size_t len;
};

int occupied[POOL_SIZE];
int pool[POOL_SIZE];

void println_pool();

int main(void) {
    println_pool();

    int *start = &pool[0];

    start++;
    *start = 1;

    println_pool();

    return 0;
}

void println_pool() {
    for (size_t i = 0; i < (size_t)POOL_SIZE; ++i) {
        if (i % 10 == 0 && i != 0) {
            printf("\n");
        }
        printf("%d ", pool[i]);
    }
    printf("\n");
}
