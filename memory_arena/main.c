#include "arena.h"

#include <stdio.h>
#include <stdlib.h>

void *arena_xmalloc(Arena *a, size_t nmemb, size_t s);

int main(void) {
    Arena a;
    Arena *aptr = &a;

    if (arena_init(aptr) != 0) {
        fprintf(stderr, "Error initializing arena!\n");
        return EXIT_FAILURE;
    }

    size_t nums_len = 20;
    int32_t *nums = arena_xmalloc(aptr, nums_len, sizeof *nums);

    for (size_t i = 0; i < nums_len; ++i) {
        nums[i] = (int32_t)i;
    }

    printf("nums\n");
    for (size_t i = 0; i < nums_len; ++i) {
        printf("%d ", nums[i]);
    }

    size_t nums2_len = 5;
    int64_t *nums2 = arena_xmalloc(aptr, nums2_len, sizeof *nums2);

    for (size_t i = 0; i < nums2_len; ++i) {
        nums2[i] = (int64_t)i + 1;
    }

    printf("nums\n");
    for (size_t i = 0; i < nums2_len; ++i) {
        printf("%ld ", nums2[i]);
    }

    arena_deinit(&aptr);
    return EXIT_SUCCESS;
}

void *arena_xmalloc(Arena *a, size_t nmemb, size_t s) {
    void *nums = arena_malloc(a, nmemb, s);
    if (!nums) {
        fprintf(stderr, "malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    return nums;
}
