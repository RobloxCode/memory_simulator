#include "arena.h"

#include <stdio.h>
#include <stdlib.h>

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
