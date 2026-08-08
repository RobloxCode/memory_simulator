CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wconversion -pedantic -g \
         -fsanitize=address -fno-omit-frame-pointer

SRC = arena.c
OUT = a

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT)

.PHONY: clean
