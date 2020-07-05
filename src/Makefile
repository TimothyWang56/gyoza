CC = gcc
CFLAGS = -Wall -Wunused -Wextra -std=c99
OUT = gyoza

all: main.c lexer.c 
	$(CC) $(CFLAGS) $^ -o $(OUT)

clean:
	rm -rf $(OUT)
