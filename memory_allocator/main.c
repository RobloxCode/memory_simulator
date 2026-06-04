#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MEMORY_CAP 64

typedef struct {
    char *id;
    size_t mem_units_total;
    size_t mem_units_count;
} Process;

typedef struct {
    int8_t ocupied;
    char *proc_id;
} ProcessState;

ProcessState memory[MEMORY_CAP];

void init_memory();
void println_memory();

void allocate_process(char *proc_id, size_t mem_units);
void deallocate_process(const char *proc_id);

int main(void) {
    init_memory();

    println_memory();
    allocate_process("firefox", 2);
    allocate_process("discord", 4);
    allocate_process("terminal", 5);
    println_memory();

    deallocate_process("firefox");
    println_memory();

    allocate_process("minecraft", 5);
    println_memory();

    return 0;
}

void allocate_process(char *proc_id, size_t mem_units) {
    Process p = {.mem_units_total = mem_units,
                 .mem_units_count = mem_units,
                 .id = proc_id};

    for (size_t i = 0; i < MEMORY_CAP; ++i) {
        if (p.mem_units_count == 0) {
            break;
        }

        if (!memory[i].ocupied) {
            memory[i].proc_id = p.id;
            memory[i].ocupied = 1;
            p.mem_units_count--;
        }
    }
}

void deallocate_process(const char *proc_id) {
    for (size_t i = 0; i < MEMORY_CAP; ++i) {
        if (strcmp(memory[i].proc_id, proc_id) == 0) {
            memory[i].ocupied = 0;
            memory[i].proc_id = "";
        }
    }
}

void init_memory() {
    for (size_t i = 0; i < MEMORY_CAP; ++i) {
        memory[i].proc_id = "";
    }
}

void println_memory() {
    for (size_t i = 0; i < MEMORY_CAP; ++i) {
        printf("i: %zu, id: %s\n", i, memory[i].proc_id);
    }
    printf("\n");
}
