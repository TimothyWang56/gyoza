#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "tokens.h"

// Outline for AST Structure

// LITERAL will have the literal as it's content and no children. int, float, str are all literals.
//      this will be split into NUM_LITERAL and STRING_LITERAL
// BINARY will have one of the binary operators (+, -, /, *, >, <, >=, <=, ==, !=, &&, ||) in content, and children[0] and children[1] will be 
//      the arguments for the binary operator. They could be a VAR, LITERAL, or FUNCCALL
// IF will have a CONDITION in children[0] and BODY in children[1]. nothing in content
// IFELSE will have a CONDITION in children[0], BODY in children[1], and BODY in children[2]. nothing in content
// CONDITION will 1 child (children[0]) thats a VAR (true or false, which is in the global env, or maybe a var that is equal to true or false)
//      or BINARY (+, -, /, *, >, <, >=, <=, ==, !=, &&, ||) or FUNCCALL that returns a boolean. nothing in content
// BODY will have array of children, where each child is some sort of statment. Im guessing content won't be used in this case
//      children can include IFELSE, ASSIGNVAR, FUNCDEF, FUNCCALL
// FUNCDEF will have = as content, VAR as children[0], and BODY as children[1]
// FUNCCALL will have function name as content, and each child will be an argument (in order). These arguments can be
//      LITERAL, BINARY, FUNCCALL, VAR
// ASSIGNVAR will have = as content. VAR is children[0] and children[1] can be FUNCCALL, LITERAL, BINARY
// VAR will have name as content, and no children

void buildNode(abstractNode **node, nodeType type, char *content) {
    *node = malloc(sizeof(abstractNode));
    (*node)->type = type;
    (*node)->content = content;
    int numChildren;
    switch (type) {
        case INT_LITERAL :
        case FLOAT_LITERAL :
        case STRING_LITERAL :
        case VAR :
            numChildren = 0;
            break;
        case CONDITION :
            numChildren = 1;
            break;
        case BINARY :
        case IF :
        case FUNCDEF :
        case ASSIGNVAR :
            numChildren = 2;
            break;
        case IFELSE :
            numChildren = 3;
            break;
        case BODY :
        case FUNCCALL :
        // 10 is abitrary here, since BODY and FUNCCALL can have any number of children. Maybe figure out a better way to handle this?
            numChildren = 10;
            break;
        default:
        // figure out the default case here? maybe error
            numChildren = 10;
    }

    (*node)->numChildren = numChildren;
    (*node)->children = malloc(sizeof(abstractNode) * numChildren);
}

// NOTE: have an int passed around that tells which token number we're on

abstractNode *buildBody(token *tokens, int numTokens, int *currToken) {
    abstractNode *root;
    buildNode(&root, BODY, "");

    if (root == NULL) {
        //handle error here
        return 0;
    }

    while (*currToken < numTokens) {
        // determine what kind of NodeType we're making?
        (*currToken)++;
    }
    // abstractNode *currNode = (*root);

    for (int i = 0; i < numTokens; i++) {
        printf("[Line: %d, Type: %d, Content: %s]\n", tokens[i].line, tokens[i].type, tokens[i].content);
        // if (tokens[i])
    }

    return root;
}

int build(token *tokens, int numTokens, abstractNode **root) {
    int currToken = 0;
    *root = buildBody(tokens, numTokens, &currToken);
    return 1;
}
