#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "tokens.h"

// Outline for AST Structure

// BODY will have array of children, where each child is some sort of statment. Im guessing content won't be used in this case
//      children can include IFELSE, ASSIGNVAR, FUNCDEF, FUNCCALL
// IF will have a CONDITION in children[0] and BODY in children[1]. nothing in content
// IFELSE will have a CONDITION in children[0], BODY in children[1], and BODY in children[2]. nothing in content
// CONDITION will 1 child (children[0]) thats a VAR (true or false, which is in the global env, or maybe a var that is equal to true or false)
//      or BINARY (>, <, >=, <=, ==, !=, ==) or FUNCCALL that returns a boolean. nothing in content
// BINARY will have one of the binary operators (>, <, >=, <=, ==, !=, ==) in content, and children[0] and children[1] will be 
//      the arguments for the binary operator. They could be a VAR, LITERAL, or FUNCCALL
// LITERAL will have the literal as it's content and no children. int, float, str are all literals.
// FUNCDEF will have = as content, VAR as children[0], and BODY as children[1]
// FUNCCALL will have function name as content, and each child will be an argument (in order). These arguments can be
//      LITERAL, BINARY, FUNCCALL, VAR
// ASSIGNVAR will have = as content. VAR is children[0] and children[1] can be FUNCCALL, LITERAL, BINARY
// VAR will have name as content, and no children

int buildAST(token *tokens, int numTokens, abstractNode **root) {
    *root = malloc(sizeof(*root));
    if (*root == NULL) {
        //handle error here
        return 0;
    }

    for (int i = 0; i < numTokens; i++) {
        // printf("[Line: %d, Type: %d, Content: %s]\n", tokens[i].line, tokens[i].type, tokens[i].content);
    }
    return 1;
}
