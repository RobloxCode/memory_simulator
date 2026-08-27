#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
    #define WARN_UNUSED __attribute__((warn_unused_result))
#else
    #define WARN_UNUSED
#endif

/** @brief Alignment used for the arena's backing allocation. */
#define ALIGN _Alignof(max_align_t)

/** @brief Size in bytes of a single arena unit (always 1). */
#define BYTE_SIZE sizeof(int8_t)

/** @brief Default number of bytes allocated when an arena is initialized. */
#define ARENA_DEF_SIZE 1024

/**
 * @brief struct representing an Arena
 *
 * A bump/linear allocator: memory is stored in a contiguous block
 * of memory, the whole buffer is freed
 * at once rather than per-allocation.
 */
typedef struct {
    size_t len; /**< Total capacity of the arena's backing buffer, in bytes. */
    int8_t *data; /**< Pointer to the start of the backing buffer (owned by the
                     arena). */
    int8_t *pos;  /**< Pointer to the next free byte within the buffer. */
} Arena;

/**
 * @brief Initializes an arena, allocating its backing buffer.
 *
 * Allocates 'ARENA_DEF_SIZE' bytes for 'a->data', and sets 'a->pos'
 * to the start of that block of memory and 'a->len' to its capacity.
 *
 * @param a Pointer to an (uninitialized) Arena to set up.
 * @return 0 on success, non-zero on failure (e.g. allocation failure).
 * @warning Return value is marked WARN_UNUSED, callers must check it
 *          before using the arena.
 */
int arena_init(Arena *a) WARN_UNUSED;

/**
 * @brief Allocates a block of memory from the arena.
 *
 * Reserves 'nmemb * size' bytes from the arena's remaining space by
 * advancing 'a->pos', aligning as needed. Unlike malloc,
 * this memory cannot be individually freed, it's reclaimed only
 * when the whole arena is deinitialized.
 *
 * @param a     Pointer to an initialized Arena.
 * @param nmemb Number of elements to allocate.
 * @param size  Size in bytes of each element.
 * @return Pointer to the allocated block, or NULL if there isn't
 *         enough remaining space in the arena.
 */
void *arena_malloc(Arena *a, size_t nmemb, size_t size);

/**
 * @brief Frees an arena's backing buffer and invalidates it.
 *
 * Frees '(*a)->data' and sets '*a' to NULL,
 * so callers can't accidentally reuse a dangling arena pointer.
 *
 * @param a Pointer to the Arena pointer to deinitialize.
 */
void arena_deinit(Arena **a);

#endif
