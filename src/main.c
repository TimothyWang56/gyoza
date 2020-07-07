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

    // make abstract syntax tree using parser
    abstractNode *root;
    returnVal = buildAST(tokens, numTokens, &root);
    
    if (!returnVal) {
        // clean up ast and maybe tokens, depending on how we're handling it
        return -1;
    }

    free(root);

    cleanTokens(&tokens, numTokens);
    return 0;
}
