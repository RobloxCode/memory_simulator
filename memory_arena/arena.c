#include "arena.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int arena_init(Arena *a) {
    int ret = 0;
    a->data = malloc(ARENA_DEF_SIZE * sizeof *a->data);

    if (!a->data) {
        ret = 1;
    }

    a->pos = a->data;
    a->len = 0;

    return ret;
}

void arena_deinit(Arena **a) {
    free((*a)->data);
    (*a)->data = NULL;
    (*a)->pos = NULL;
    *a = NULL;
}

void *arena_malloc(Arena *a, size_t nmemb, size_t size) {
    if (size != 0 && nmemb > SIZE_MAX / size) {
        fprintf(stderr, "Allocation size overflow!\n");
        return NULL;
    }

    size_t total = nmemb * size;

    if (total > ARENA_DEF_SIZE - a->len) {
        fprintf(stderr, "Not enough memory!\n");
        return NULL;
    }

    void *p = NULL;
    p = a->pos;
    a->pos += total;
    a->len += (size_t)total;

    return p;
}
