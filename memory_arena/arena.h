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

int arena_init(Arena *a) WARN_UNUSED;
void *arena_malloc(Arena *a, size_t nmemb, size_t size);
void arena_deinit(Arena **a);

#endif
