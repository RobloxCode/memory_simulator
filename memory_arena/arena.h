#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

#if defined(__GNUC__) || defined(__clang__)
    #define WARN_UNUSED __attribute__((warn_unused_result))
#else
    #define WARN_UNUSED
#endif

#define BYTE_SIZE      sizeof(int8_t)
#define ARENA_DEF_SIZE 1024

typedef struct {
    size_t len;
    int8_t *data;
    int8_t *pos;
} Arena;

int arena_init(Arena *a) WARN_UNUSED;
void *arena_malloc(Arena *a, size_t nmemb, size_t size);
void arena_deinit(Arena **a);

#endif
