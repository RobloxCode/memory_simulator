#include "arena.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Arena a;
    Arena *aptr = &a;
    arena_init(&a);

    size_t nums_len = 20;
    int32_t *nums = arena_malloc(aptr, nums_len, sizeof *nums);
    if (!nums) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < nums_len; ++i) {
        nums[i] = (int32_t)i;
    }

    printf("nums\n");
    for (size_t i = 0; i < nums_len; ++i) {
        printf("%d ", nums[i]);
    }

    size_t nums2_len = 5;
    int64_t *nums2 = arena_malloc(aptr, nums2_len, sizeof *nums2);

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
