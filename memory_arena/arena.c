#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARENA_DEF_SIZE 1024

typedef struct {
    size_t len;
    int8_t *data;
    int8_t *pos;
} Arena;

void arena_init(Arena *a);
void *arena_malloc(Arena *a, size_t nmemb, size_t size);
void arena_deinit(Arena **a);

int main(void) {
    Arena a;
    Arena *aptr = &a;
    arena_init(&a);

    arena_deinit(&aptr);
    return 0;
}

void arena_init(Arena *a) {
    a->data = malloc(ARENA_DEF_SIZE * sizeof *a->data);
    if (!a->data) {
        fprintf(stderr, "Error internal malloc\n");
        return;
    }

    a->pos = a->data;
    a->len = 0;
}

void arena_deinit(Arena **a) {
    free((*a)->data);
    (*a)->data = NULL;
    (*a)->pos = NULL;
    *a = NULL;
}
