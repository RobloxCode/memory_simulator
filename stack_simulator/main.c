#include <stddef.h>
#include <stdio.h>

#define STACK_NUM_BYTES 26

struct Stack {
    int items[STACK_NUM_BYTES];
    unsigned int stack_origin;
    unsigned int stack_ptr;

    int bytes_allocated[STACK_NUM_BYTES];
    unsigned int bytes_allocated_pos;
};

void stack_init(struct Stack *s);
void stack_alloc(struct Stack *s, unsigned int bytes, int value);
void stack_dealloc(struct Stack *s);
void stack_println(const struct Stack s);

int main(void)
{
    struct Stack stack = {0};
    stack_init(&stack);

    stack_println(stack);

    stack_alloc(&stack, 2, 10);
    stack_println(stack);

    stack_alloc(&stack, 1, 3);
    stack_println(stack);

    stack_alloc(&stack, 4, 345);
    stack_println(stack);

    stack_dealloc(&stack);
    stack_println(stack);

    stack_alloc(&stack, 3, 3);
    stack_println(stack);

    return 0;
}

void stack_init(struct Stack *s)
{
    for (size_t i = 0; i < (size_t)STACK_NUM_BYTES; ++i) {
        s->items[i] = 0;
        s->bytes_allocated[i] = 0;
    }

    s->stack_origin = (unsigned int)0;
    s->stack_ptr = (unsigned int)0;
    s->bytes_allocated_pos = 0;
}

void stack_alloc(struct Stack *s, unsigned int bytes, int value)
{
    for (size_t i = 0; i < (size_t)bytes; ++i) {
        s->items[s->stack_ptr++] = value;
    }

    s->bytes_allocated[s->bytes_allocated_pos++] = bytes;
}

void stack_dealloc(struct Stack *s)
{
    printf("stakc ptr: %d\n", s->stack_ptr);
    printf("stakc bytes pos: %d\n", s->bytes_allocated_pos);
    for (size_t i = s->stack_ptr; i < s->bytes_allocated_pos; ++i) {
        s->items[i] = 0;
    }
}

void stack_println(const struct Stack s)
{
    for (size_t i = 0; i < (size_t)STACK_NUM_BYTES; ++i) {
        printf("%d ", s.items[i]);
    }
    printf("\n");
}
