#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE      sizeof(int8_t)
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

    int32_t *nums = arena_malloc(aptr, 2, sizeof *nums);
    if (!nums) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 2; ++i) {
        nums[i] = (int32_t)i;
    }

    for (size_t i = 0; i < 2; ++i) {
        printf("%d ", nums[i]);
    }

    arena_deinit(&aptr);
    return EXIT_SUCCESS;
}

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
