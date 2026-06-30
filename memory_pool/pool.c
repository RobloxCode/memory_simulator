#include <stddef.h>
#include <stdio.h>

#define POOL_SIZE 60

typedef struct {
    int *start;
    size_t start_i;
    size_t len;
} PoolSlice;

int occupied[POOL_SIZE];
int pool[POOL_SIZE];

void _println_pool();
void _println_occupied();
size_t _get_pool_start();

void mymalloc(PoolSlice *dst, size_t size);
void pool_slice_print_info(PoolSlice ps);

int main(void) {
    _println_pool();

    PoolSlice ps = {0};
    mymalloc(&ps, 4);

    PoolSlice ps2 = {0};
    mymalloc(&ps2, 5);

    pool_slice_print_info(ps);
    pool_slice_print_info(ps2);

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

    dst->start_i = pool_start_pos;
    dst->start = (int *)pool_start_pos;
    dst->len = size;

    for (size_t i = 0; i < size; ++i) {
        occupied[pool_start_pos++] = 1;
    }
}

void pool_slice_print_info(PoolSlice ps) {
    printf("i: %zu\nlen: %zu\n", ps.start_i, ps.len);
}
