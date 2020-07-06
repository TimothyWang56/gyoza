#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

void cleanTokens(token **tokens, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        free((*tokens)[i].content);
    }
    free(*tokens);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("ERROR: no filename specified\n");
        return -1;
    }

    token *tokens;
    int numTokens;
    int returnVal = tokenize(argv[1], &tokens, &numTokens);

    // if failed, clean up tokens and return error code
    if (!returnVal) {
        cleanTokens(&tokens, numTokens);
        return -1;
    }

    for (int i = 0; i < numTokens; i++) {
        printf("[Line: %d, Type: %d, Content: %s]\n", tokens[i].line, tokens[i].type, tokens[i].content);
    }

    cleanTokens(&tokens, numTokens);
    return 0;
}
