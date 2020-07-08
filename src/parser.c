#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "tokens.h"

// Outline for AST Structure

// LITERAL will have the literal as it's content and no children. int, float, str are all literals.
//      this will be split into NUM_LITERAL and STRING_LITERAL
// BINARY will have one of the binary operators (+, -, /, *, >, <, >=, <=, ==, !=, &&, ||) in content, and children[0] and children[1] will be 
//      the arguments for the binary operator. They could be a VAR, LITERAL, FUNCCALL, or BINARY
// IF will have a CONDITION in children[0] and BODY in children[1]. nothing in content
// IFELSE will have a CONDITION in children[0], BODY in children[1], and BODY in children[2]. nothing in content
// CONDITION will 1 child (children[0]) thats a VAR (true or false, which is in the global env, or maybe a var that is equal to true or false)
//      or BINARY (+, -, /, *, >, <, >=, <=, ==, !=, &&, ||) or FUNCCALL that returns a boolean. nothing in content
// BODY will have array of children, where each child is some sort of statment. Im guessing content won't be used in this case
//      children can include IF, IFELSE, ASSIGNVAR, FUNCDEF, FUNCCALL
// FUNCDEF will have = as content, VAR as children[0], and BODY as children[1]
// FUNCCALL will have function name as content, and each child will be an argument (in order). These arguments can be
//      LITERAL, BINARY, FUNCCALL, VAR
// ASSIGNVAR will have type (int, float, boolean, string, etc.) as content. VAR is children[0] and children[1] can be FUNCCALL, LITERAL, BINARY
// VAR will have name as content, and no children

abstractNode *buildNode(nodeType type, char *content) {
    abstractNode *node = malloc(sizeof(abstractNode));
    // TODO: double check malloc was successful
    node->type = type;
    node->content = content;
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

    node->numChildren = numChildren;
    node->children = malloc(sizeof(abstractNode*) * numChildren);
    return node;
}

abstractNode *buildLit(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildLit\n");
        return NULL;
    }
    nodeType type;
    if (tokens[*currToken].type == INT) {
        type = INT_LITERAL;
    } else if (tokens[*currToken].type == FLT) {
        type = FLOAT_LITERAL;
    } else if (tokens[*currToken].type == STR) {
        type = STRING_LITERAL;
    } else {
        printf("ERROR - line %d: expected an identifier at the beginning of this line\n", tokens[*currToken].line);
        return NULL;
    }

    abstractNode *node = buildNode(type, tokens[*currToken].content);
    (*currToken)++;
    return node;
}


abstractNode *buildVar(token *tokens, int numTokens, int *currToken) {
    //TODO: maybe check for already defined keywords like true, false, print, etc?
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildVar\n");
        return NULL;
    }

    if (tokens[*currToken].type == IDEN) {
        abstractNode *node = buildNode(VAR, tokens[*currToken].content);
        (*currToken)++;
        return node;
    } else {
        printf("ERROR - line %d: expected an identifier at the beginning of this line\n", tokens[*currToken].line);
        return NULL;
    }
}

abstractNode *buildAssignVar(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildLit\n");
        return NULL;
    }

    abstractNode *node;
    if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#")) {
        (*currToken)++;
        if (tokens[*currToken].type == IDEN) {
            char *content = tokens[*currToken].content;
            if (!strcmp(content, "int") ||
                !strcmp(content, "float") ||
                !strcmp(content, "string") ||
                !strcmp(content, "boolean")) {
                node = buildNode(ASSIGNVAR, content);
                (*currToken)++;
                abstractNode *varChild = buildVar(tokens, numTokens, currToken);
                node->children[0] = varChild;
                if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "=")) {
                    (*currToken)++;
                    // TODO: handle function calls and binaries in addition to literals
                    // just handling literals for now
                    abstractNode *litChild = buildLit(tokens, numTokens, currToken);
                    node->children[1] = litChild;
                    return node;
                } else {
                    printf("ERROR - line %d: expected '=' after identifier\n", tokens[*currToken].line);
                    return NULL;
                }
            } else {
                printf("bad!!\n");
                return NULL;
            }
        } else {
            printf("ERROR - line %d: must have identifier like int/float/string after #\n", tokens[*currToken].line);
            return NULL;
        }
    } else {
        return NULL;
    }
}

abstractNode *buildBody(token *tokens, int numTokens, int *currToken) {
    abstractNode *node = buildNode(BODY, "");

    if (node == NULL) {
        //handle error here
        return NULL;
    }

    int currChild = 0;

    while (*currToken < numTokens) {
        // determine what kind of NodeType we're making?
        // either IF, IFELSE, ASSIGNVAR, FUNCDEF, FUNCCALL
        if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#")) {
            // either a ASSIGNVAR or FUNCDEF
            // if next line starts with a # OP, then it's a FUNCDEF. if its an IDEN it's an ASSIGNVAR. otherwise some error.
            int currLine = tokens[*currToken].line;
            int temp = *currToken;
            while (tokens[temp].line == currLine) {
                temp++;
                if (temp >= numTokens) {
                    printf("ERROR: started # definition but did not finish\n");
                    return NULL;
                }
            }
            if (tokens[temp].line == (currLine) + 1) {
                if (tokens[temp].type == OP && !strcmp(tokens[temp].content, "#")) {
                    // this is a FUNCDEF
                    printf("This is a FUNCDEF!\n");
                    return NULL;
                } else if (tokens[temp].type == IDEN) {
                    printf("This is an ASSIGNVAR!\n");
                    abstractNode *child = buildAssignVar(tokens, numTokens, currToken);
                    printf("%d, %s, %d, %s, %d, %s\n", child->type, child->content, (child->children[0])->type, (child->children[0])->content, (child->children[1])->type, (child->children[1])->content);
                    node->children[0] = child;
                    currChild++;
                } else {
                    printf("ERROR - line %d: expected assignment or another # line after line %d\n", currLine, currLine);
                    return NULL;
                }
            } else {
                printf("ERROR - line %d: expected a line with content immediately after %d\n", currLine, currLine);
                return NULL;
            }

            
        } else {
            // might be IF, IFELSE, FUNCCALL
            printf("blah\n");
            return NULL;
        }
    }

    for (int i = 0; i < numTokens; i++) {
        printf("[Line: %d, Type: %d, Content: %s]\n", tokens[i].line, tokens[i].type, tokens[i].content);
    }

    return node;
}

int build(token *tokens, int numTokens, abstractNode **root) {
    int currToken = 0;
    *root = buildBody(tokens, numTokens, &currToken);
    // TODO: ERROR check *root isn't null
    return 1;
}
