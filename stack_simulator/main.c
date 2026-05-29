#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define STACK_BYTES 26

struct Allocated_bytes_arr {
    size_t bytes[STACK_BYTES];
    size_t bytes_count;
};

struct Stack {
    uint8_t items[STACK_BYTES];
    uint8_t *stack_ptr;
    struct Allocated_bytes_arr ab_arr;
};

void stack_init(struct Stack *s);
void stack_alloc(struct Stack *s, size_t bytes, uint8_t val);
void stack_dealloc(struct Stack *s);
void stack_println(struct Stack *s);
void stack_println_full(struct Stack *s);

int main(void)
{
    struct Stack s;
    struct Stack *sptr = &s;

    stack_init(sptr);

    stack_dealloc(sptr);

    stack_println(sptr);
    stack_alloc(sptr, 3, 10);
    stack_alloc(sptr, 1, 2);
    stack_alloc(sptr, 2, 255);
    stack_alloc(sptr, 2, 23);
    stack_alloc(sptr, 5, 145);
    stack_alloc(sptr, 3, 45);
    stack_println(sptr);

    stack_dealloc(sptr);
    stack_dealloc(sptr);
    stack_println(sptr);
    stack_println_full(sptr);

    stack_alloc(sptr, 2, 255);
    stack_println(sptr);
    stack_println_full(sptr);

    stack_alloc(sptr, 20, 145);

    return 0;
}

void stack_init(struct Stack *s)
{
    for (size_t i = 0; i < (size_t)STACK_BYTES; ++i) {
        s->items[i] = 0;
        s->ab_arr.bytes[i] = 0;
    }

    s->ab_arr.bytes_count = 0;
    s->stack_ptr = s->items + STACK_BYTES - 1;
}

void stack_alloc(struct Stack *s, size_t bytes, uint8_t val)
{
    uint8_t *start = s->items + STACK_BYTES - 1;
    uint8_t *end = s->stack_ptr;
    size_t used = (size_t)(start - end);

    if (used + bytes > STACK_BYTES) {
        fprintf(stderr, "stack overflow!\n");
        return;
    }

    for (size_t i = 0; i < bytes; ++i) {
        *(s->stack_ptr) = val;
        s->stack_ptr--;
    }

    if (s->ab_arr.bytes_count >= STACK_BYTES) {
        fprintf(stderr, "stack overflow!\n");
        return;
    }

    s->ab_arr.bytes[s->ab_arr.bytes_count++] = bytes;
}

void stack_dealloc(struct Stack *s)
{
    if (s->ab_arr.bytes_count == 0) {
        fprintf(stderr, "stack underflow!\n");
        return;
    }

    size_t bytes_to_remove = s->ab_arr.bytes[s->ab_arr.bytes_count - 1];
    s->stack_ptr += bytes_to_remove;
    s->ab_arr.bytes_count--;
}

void stack_println_full(struct Stack *s)
{
    for (size_t i = 0; i < (size_t)STACK_BYTES; ++i) {
        printf("%d ", s->items[i]);
    }

    printf("\n");
}

void stack_println(struct Stack *s)
{
    uint8_t *start = s->items + STACK_BYTES - 1;
    uint8_t *end = s->stack_ptr;
    size_t len = (size_t)(start - end);

    if (len == 0) {
        printf("empty stack\n");
        return;
    }

    for (size_t i = 0; i < len; ++i) {
        printf("%d ", *start);
        start--;
    }

    printf("\n");
}
