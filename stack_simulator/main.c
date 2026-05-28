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
    uint8_t *stack_origin;
    size_t stack_ptr;
    struct Allocated_bytes_arr ab_arr;
};

void stack_init(struct Stack *s);
void stack_alloc(struct Stack *s, size_t bytes, uint8_t val);
void stack_dealloc(struct Stack *s);
void stack_println(struct Stack s);
void stack_println_full(struct Stack s);

int main(void)
{
    struct Stack s;
    stack_init(&s);

    stack_dealloc(&s);

    stack_println(s);
    stack_alloc(&s, 3, 10);
    stack_alloc(&s, 1, 2);
    stack_alloc(&s, 2, 255);
    stack_alloc(&s, 2, 23);
    stack_alloc(&s, 5, 145);
    stack_alloc(&s, 3, 45);
    stack_println(s);

    stack_dealloc(&s);
    stack_dealloc(&s);
    stack_println(s);
    stack_println_full(s);

    stack_alloc(&s, 2, 255);
    stack_println(s);

    stack_println_full(s);

    stack_alloc(&s, 20, 145);

    return 0;
}

void stack_init(struct Stack *s)
{
    for (size_t i = 0; i < (size_t)STACK_BYTES; ++i) {
        s->items[i] = 0;
        s->ab_arr.bytes[i] = 0;
    }

    s->ab_arr.bytes_count = 0;

    s->stack_origin = &s->items[0];
    s->stack_ptr = 0;
}

void stack_alloc(struct Stack *s, size_t bytes, uint8_t val)
{
    if (s->stack_ptr + bytes > STACK_BYTES) {
        fprintf(stderr, "stack overflow!\n");
        return;
    }

    for (size_t i = 0; i < bytes; ++i) {
        s->items[s->stack_ptr++] = val;
    }

    s->ab_arr.bytes[s->ab_arr.bytes_count++] = bytes;
}

void stack_dealloc(struct Stack *s)
{
    if (s->stack_ptr == 0) {
        fprintf(stderr, "stack underflow!\n");
        return;
    }

    s->stack_ptr -= s->ab_arr.bytes[s->ab_arr.bytes_count - 1];
    s->ab_arr.bytes_count--;
}

void stack_println_full(struct Stack s)
{
    for (size_t i = 0; i < (size_t)STACK_BYTES; ++i) {
        printf("%d ", s.items[i]);
    }
    printf("\n");
}

void stack_println(struct Stack s)
{
    if (s.stack_ptr == 0) {
        printf("empty stack\n");
        return;
    }

    for (size_t i = 0; i < s.stack_ptr; ++i) {
        printf("%d ", s.items[i]);
    }

    printf("\n");
}
