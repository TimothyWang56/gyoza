CC = gcc
CFLAGS = -Wall -Wunused -Wextra -std=c99
OUT = gyoza

all: main.c lexer.c parser.c stack.c
	$(CC) $(CFLAGS) $^ -o $(OUT)

debug: main.c lexer.c parser.c stack.c
	$(CC) -g $(CFLAGS) $^ -o $(OUT)

clean:
	rm -rf $(OUT)
