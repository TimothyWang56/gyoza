#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

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

    // tokenize using lexer
    token *tokens;
    int numTokens;
    int returnVal = tokenize(argv[1], &tokens, &numTokens);

    // if failed, clean up tokens and return error code
    if (!returnVal) {
        cleanTokens(&tokens, numTokens);
        return -1;
    }

    for (int i = 0; i < numTokens; i++) {
        printf("Line: %d, Content: %s\n", tokens[i].line, tokens[i].content);
    }

    // make abstract syntax tree using parser
    abstractNode *root;
    returnVal = build(tokens, numTokens, &root);
    
    if (!returnVal) {
        // TODO: clean up ast and maybe tokens, depending on how we're handling it
        return -1;
    }

    // TODO: free ast

    cleanTokens(&tokens, numTokens);
    return 0;
}
