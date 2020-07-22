CC = gcc
CFLAGS = -Wall -Wunused -Wextra -std=c99
OUT = tests

token: tokenTest/tokensTest.c ../src/lexer.c
	$(CC) $(CFLAGS) $^ -o $(OUT)

all: token

clean:
	rm -rf $(OUT)
