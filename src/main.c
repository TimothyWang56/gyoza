#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("ERROR: no filename specified\n");
        return -1;
    }

    token *tokens;
    int numTokens;
    tokenize(argv[1], &tokens, &numTokens);

    for (int i = 0; i < numTokens; i++) {
        printf("[Line: %d, Type: %d, Content: %s]\n", tokens[i].line, tokens[i].type, tokens[i].content);
    }

    return 0;
}
