CC = gcc
CFLAGS = -Wall -Wunused -Wextra -std=c99

token: tokenTest/tokensTest.c ../src/lexer.c
	$(CC) $(CFLAGS) $^ -o tokenTests

parser: parserTest/parserTest.c ../src/lexer.c
	$(CC) $(CFLAGS) $^ -o parserTests

tests: token parser
	./tokenTests
	./parserTests

clean:
	rm -rf $(OUT)
