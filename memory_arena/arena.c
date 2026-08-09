#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t len;
    int8_t *data;
    int8_t *pos;
} Arena;

void arena_init(Arena *a);
void *arena_malloc(Arena *a, size_t nmemb, size_t size);
void arena_deinit(Arena **a);

int main(void) {
    return 0;
}
