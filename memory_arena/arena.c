#include "arena.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void arena_init(Arena *a) {
    a->data = malloc(ARENA_DEF_SIZE * sizeof *a->data);
    if (!a->data) {
        fprintf(stderr, "Error internal malloc!\n");
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

void *arena_malloc(Arena *a, size_t nmemb, size_t size) {
    void *p = NULL;

    size_t shift_times = (size / BYTE_SIZE) * nmemb;

    if (shift_times > ARENA_DEF_SIZE) {
        fprintf(stderr, "Not enough memory!\n");
        return NULL;
    }

    p = a->pos;
    a->pos += shift_times;
    a->len += (size_t)shift_times;

    return p;
}
