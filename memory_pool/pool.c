#include <stddef.h>
#include <stdio.h>

#define POOL_SIZE 60

typedef struct {
    int *start;
    size_t len;
} PoolSlice;

int occupied[POOL_SIZE];
int pool[POOL_SIZE];

void _println_pool();
void _println_occupied();
size_t _get_pool_start();

void mymalloc(PoolSlice *dst, size_t size);

int main(void) {
    _println_pool();

    PoolSlice slice = {0};
    mymalloc(&slice, 4);

    _println_occupied();
    _println_pool();

    return 0;
}

void _println_pool() {
    for (size_t i = 0; i < (size_t)POOL_SIZE; ++i) {
        if (i % 10 == 0 && i != 0) {
            printf("\n");
        }
        printf("%d ", pool[i]);
    }
    printf("\n");
}

size_t _get_pool_start() {
    for (size_t i = 0; i < (size_t)POOL_SIZE; ++i) {
        if (occupied[i] == 0) {
            return i;
        }
    }
    return 0;
}

void _println_occupied() {
    printf("[ ");
    for (size_t i = 0; i < (size_t)POOL_SIZE; ++i) {
        printf("%d ", occupied[i]);
    }
    printf("]\n");
}

void mymalloc(PoolSlice *dst, size_t size) {
    size_t pool_start_pos = _get_pool_start();

    dst->start = (int *)pool_start_pos;
    dst->len = size;

    for (size_t i = 0; i < size; ++i) {
        occupied[pool_start_pos++] = 1;
    }
}
