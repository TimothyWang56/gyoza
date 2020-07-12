#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "tokens.h"

// headers for functions to fix compile errors (implicit declarations)
abstractNode *buildFuncCall(token *tokens, int numTokens, int *currToken);
abstractNode *buildBody(token *tokens, int numTokens, int *currToken);

// Outline for AST Structure

// *DONE*
// LITERAL  will have the literal as it's content and no children. int, float, str are all literals.
//      this will be split into NUM_LITERAL and STRING_LITERAL

// *TODO*
// BINARY will have one of the binary operators (+, -, /, *, >, <, >=, <=, ==, !=, &&, ||) in content, and children[0] and children[1] will be 
//      the arguments for the binary operator. They could be a VAR, LITERAL, FUNCCALL, or BINARY

// *IN PROGRESS*
// IF will have a CONDITION in children[0] and BODY in children[1]. nothing in content

// *IN PROGRESS*
// IFELSE will have a CONDITION in children[0], BODY in children[1], and BODY in children[2]. nothing in content

// *IN PROGRESS*
// CONDITION will 1 child (children[0]) thats a VAR (true or false, which is in the global env, or maybe a var that is equal to true or false)
//      or BINARY (+, -, /, *, >, <, >=, <=, ==, !=, &&, ||) or FUNCCALL that returns a boolean. nothing in content

// *IN PROGRESS*
// BODY will have array of children, where each child is some sort of statment. Im guessing content won't be used in this case
//      children can include IF, IFELSE, ASSIGNVAR, FUNCDEF, FUNCCALL

// *IN PROGRESS*
// FUNCDEF will have func name as content, FUNCARG as children[0], children[1],..., and BODY as children[1]

// *DONE*
// FUNCARG will have type as content and VAR as children[0]

// *DONE*
// FUNCRETURN will have type as content, and no children

// *IN PROGRESS*
// FUNCCALL will have function name as content, and each child will be an argument (in order). These arguments can be
//      LITERAL, BINARY, FUNCCALL, VAR

// *IN PROGRESS*
// ASSIGNVAR will have type (int, float, boolean, string, etc.) as content. VAR is children[0] and children[1] can be FUNCCALL, LITERAL, BINARY, VAR

// *DONE*
// VAR will have name as content, and no children

abstractNode *buildNode(nodeType type, char *content) {
    abstractNode *node = malloc(sizeof(abstractNode));
    // TODO: double check malloc was successful
    node->type = type;
    node->content = content;
    int numChildren;
    switch (type) {
        case FUNCRETURN :
        case INT_LITERAL :
        case FLOAT_LITERAL :
        case STRING_LITERAL :
        case VAR :
            numChildren = 0;
            break;
        case FUNCARG:
        case CONDITION :
            numChildren = 1;
            break;
        case BINARY :
        case IF :
        
        case ASSIGNVAR :
            numChildren = 2;
            break;
        case IFELSE :
            numChildren = 3;
            break;
        case BODY :
        case FUNCCALL :
        case FUNCDEF :
            numChildren = 0;
            break;
        default:
        // figure out the default case here? maybe error
            numChildren = 0;
    }

    node->numChildren = numChildren;
    // TODO: double check that this is malloc'ing the correct amount
    node->children = malloc(sizeof(abstractNode*) * numChildren);
    return node;
}

void printAST(abstractNode *node, char* currLeadSpace, char* leadSpaceIncrement) {
    char *type;
    switch (node->type) {
        case INT_LITERAL:
            type = "INT_LITERAL";
            break;
        case FLOAT_LITERAL:
            type = "FLOAT_LITERAL";
            break;
        case STRING_LITERAL:
            type = "STRING_LITERAL";
            break;
        case BINARY:
            type = "BINARY";
            break;
        case IF:
            type = "IF";
            break;
        case IFELSE:
            type = "IFELSE";
            break;
        case CONDITION:
            type = "CONDITION";
            break;
        case BODY:
            type = "BODY";
            break;
        case FUNCDEF:
            type = "FUNCDEF";
            break;
        case FUNCCALL:
            type = "FUNCCALL";
            break;
        case ASSIGNVAR:
            type = "ASSIGNVAR";
            break;
        case VAR:
            type = "VAR";
            break;
        case FUNCARG:
            type = "FUNCARG";
            break;
        case FUNCRETURN:
            type = "FUNCRETURN";
            break;
    }
    
    printf("%sType: %s\n", currLeadSpace, type);
    printf("%sContent: %s\n", currLeadSpace, node->content);
    printf("%sNum Children: %d\n", currLeadSpace, node->numChildren);
    printf("%s--------------\n", currLeadSpace);
    for (int i = 0; i < node->numChildren; i++) {
        char *newLeadSpace = malloc(strlen(currLeadSpace) + strlen(leadSpaceIncrement) + 1);
        strcpy(newLeadSpace, currLeadSpace);
        strcat(newLeadSpace, leadSpaceIncrement);
        printAST(node->children[i], newLeadSpace, leadSpaceIncrement);
    }
}

// only used for abstract nodes with arbitrary number of children, BODY and FUNCCALL
// will add 1 child and realloc for more space
void addChild(abstractNode *node, abstractNode *child) {
    int index = node->numChildren;
    (node->numChildren)++;
    abstractNode **temp = realloc(node->children, sizeof(abstractNode*) * (node->numChildren));
    if (temp == NULL) {
        // figure out how to error
    } else {
        node->children = temp;
        (node->children)[index] = child;
    }
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

abstractNode *buildFuncReturn(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildFuncReturn\n");
        return NULL;
    }
    if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#")) {
        (*currToken)++;
        if (tokens[*currToken].type == IDEN) {
            abstractNode *node = buildNode(FUNCRETURN, tokens[*currToken].content);
            (*currToken)++;
            return node;
        } else {
            printf("ERROR - line %d: expected an identifier at the beginning of this line\n", tokens[*currToken].line);
            return NULL;
        }
    } else {
        printf("ERROR: expected # for func return\n");
        return NULL;
    }
}

abstractNode *buildFuncArg(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildFuncArg\n");
        return NULL;
    }

    if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#")) {
        (*currToken)++;
        abstractNode *node;
        if (tokens[*currToken].type == IDEN) {
            node = buildNode(FUNCARG, tokens[*currToken].content);
            (*currToken)++;
            if (tokens [*currToken].type == IDEN) {
                abstractNode *child = buildVar(tokens, numTokens, currToken);
                node->children[0] = child;
                return node;
            } else {
                printf("ERROR: expected 2nd iden after #\n");
                return NULL;
            }
        } else {
            printf("ERROR: expected iden after #\n");
            return NULL;
        }
    } else {
        printf("ERROR: func arg starts with #\n");
        return NULL;
    }
}

// determines token after a function call is closed.
token *tokenAfterFuncCall(token *tokens, int numTokens, int currToken) {
    if (currToken < numTokens) {
        if (tokens[currToken].type == IDEN) {
            currToken++;
            if (tokens[currToken].type == OP &&
                !strcmp(tokens[currToken].content, "(")) {
                currToken++;
                int openParens = 1;
                int closeParens = 0;
                while (currToken < numTokens) {
                    if (tokens[currToken].type == OP) {
                        if (!strcmp(tokens[currToken].content, "(")) {
                            openParens++;
                        } else if (!strcmp(tokens[currToken].content, ")")) {
                            closeParens++;
                        }
                    }

                    currToken++;
                    if (openParens == closeParens) {
                        break;
                    }
                }

                if (openParens == closeParens) {
                    return &tokens[currToken];
                }
            }
        }
    }
    return NULL;
}

abstractNode *buildCondition(token *tokens, int numTokens, int *currToken) {
    //TODO: maybe check for already defined keywords like true, false, print, etc?
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildCondition\n");
        return NULL;
    }

    abstractNode *node = buildNode(CONDITION, "");

    // TODO: maybe check for surrounding ( ) and ignore them (currently we don't support that)
    if (tokens[*currToken].type == IDEN) {
        if (tokens[(*currToken) + 1].type == OP && !strcmp(tokens[(*currToken) + 1].content, "?")) {
            abstractNode *varChild = buildVar(tokens, numTokens, currToken);
            node->children[0] = varChild;
            return node;
        } else {
            token *t = tokenAfterFuncCall(tokens, numTokens, *currToken);
            if ((*t).type == OP && !strcmp((*t).content, "?")) {
                abstractNode *funcChild = buildFuncCall(tokens, numTokens, currToken);
                node->children[0] = funcChild;
                return node;
            } else {
                // either BINARY or error
                return NULL;
            }
        }
    } else {
        // either BINARY or error
        return NULL;
    }
}

abstractNode *buildIfOrIfElse(token *tokens, int numTokens, int *currToken) {
    //TODO: maybe check for already defined keywords like true, false, print, etc?
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildIfOrElse\n");
        return NULL;
    }

    abstractNode *node;
    abstractNode *condition = buildCondition(tokens, numTokens, currToken);

    if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "?") &&
        tokens[(*currToken) + 1].type == OP && !strcmp(tokens[(*currToken) + 1].content, "{")) {
        *currToken = (*currToken) + 2;
        abstractNode *bodyChild = buildBody(tokens, numTokens, currToken);
        if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "}")) {
            (*currToken)++;
            // this is the IFELSE case
            if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "/")) {
                (*currToken)++;
                node = buildNode(IFELSE, "");
                abstractNode *elseChild = buildIfOrIfElse(tokens, numTokens, currToken);
                node->children[0] = condition;
                node->children[1] = bodyChild;
                node->children[2] = elseChild;
                return node;
            // this is the IF case
            } else {
                node = buildNode(IF, "");
                node->children[0] = condition;
                node->children[1] = bodyChild;
                return node;
            }
        } else {
            printf("ERROR: expected closing bracket }\n");
            return NULL;
        }
    } else {
        printf("ERROR: expected a ? and { after condition\n");
        return NULL;
    }
}

abstractNode *buildFuncCall(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildFuncCall\n");
        return NULL;
    }

    abstractNode *node;
    if (tokens[*currToken].type == IDEN) {
        node = buildNode(FUNCCALL, tokens[*currToken].content);
        (*currToken)++;
        if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "(")) {
            (*currToken)++;
            int funcCallClosed = 0;
            while (*currToken < numTokens) {
                // arguments can be LITERAL, FUNCCALL, BINARY, or VAR

                // VAR case
                if (tokens[*currToken].type == IDEN &&
                    tokens[(*currToken) + 1].type == OP &&
                    (!strcmp(tokens[(*currToken) + 1].content, ",") ||
                    !strcmp(tokens[(*currToken) + 1].content, ")"))) {
                    abstractNode *child = buildVar(tokens, numTokens, currToken);
                    addChild(node, child);
                // LITERAL case
                } else if ((tokens[*currToken].type == STR ||
                    tokens[*currToken].type == FLT ||
                    tokens[*currToken].type == INT) &&
                    tokens[(*currToken) + 1].type == OP &&
                    (!strcmp(tokens[(*currToken) + 1].content, ",") ||
                    !strcmp(tokens[(*currToken) + 1].content, ")"))) {
                    abstractNode *child = buildLit(tokens, numTokens, currToken);
                    addChild(node, child);
                } else {
                    // FUNCCALL or BINARY case
                    if (tokens[*currToken].type == IDEN &&
                        tokens[(*currToken) + 1].type == OP &&
                        !strcmp(tokens[(*currToken) + 1].content, "(")) {
                        token *t = tokenAfterFuncCall(tokens, numTokens, *currToken);
                        // FUNCCALL case
                        if (!strcmp((*t).content, ")") || !strcmp((*t).content, ",")) {
                            abstractNode *child = buildFuncCall(tokens, numTokens, currToken);
                            addChild(node, child);
                        // must be BINARY case or ERROR
                        } else {

                        }
                    // at this point, must be BINARY case or ERROR
                    } else {

                    }
                }

                if (tokens[(*currToken)].type == OP) {
                    if (!strcmp(tokens[*currToken].content, ")")) {
                        funcCallClosed = 1;
                        (*currToken)++;
                        break;
                    } else if (!strcmp(tokens[*currToken].content, ",")) {
                        (*currToken)++;
                    } else {
                        printf("ERROR: expected , or )");
                        break;
                    }
                } else {
                    printf("ERROR - line %d: \n", tokens[*currToken].line);
                    return NULL;
                }
            }

            if (funcCallClosed) {
                return node;
            } else {
                printf("ERROR: error in function call\n");
                return NULL;
            }

        } else {
            printf("ERROR - line %d: expected a '(' after the function name\n", tokens[*currToken].line);
            return NULL;
        }
    } else {
        printf("ERROR - line %d: expected an identifier for a function call\n", tokens[*currToken].line);
        return NULL;
    }
}

abstractNode *buildAssignVar(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildAssignVar\n");
        return NULL;
    }

    abstractNode *node;
    if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#")) {
        // have better checking to make sure this is all the same line
        
        (*currToken)++;
        if (tokens[*currToken].type == IDEN) {
            char *content = tokens[*currToken].content;
            if (!strcmp(content, "int") ||
                !strcmp(content, "float") ||
                !strcmp(content, "string") ||
                !strcmp(content, "boolean")) {
                node = buildNode(ASSIGNVAR, content);
                (*currToken)++;
                int currLine = tokens[*currToken].line;
                abstractNode *varChild = buildVar(tokens, numTokens, currToken);
                node->children[0] = varChild;
                if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "=")) {
                    (*currToken)++;
                    // TODO: handle function calls, vars, binaries in addition to literals
                    // LITERAL case
                    if ((tokens[*currToken].type == INT ||
                        tokens[*currToken].type == FLT ||
                        tokens[*currToken].type == STR) &&
                        (tokens[(*currToken) + 1].line != currLine)) {
                        abstractNode *litChild = buildLit(tokens, numTokens, currToken);
                        node->children[1] = litChild;
                        return node;
                    // VAR case
                    } else if (tokens[*currToken].type == IDEN &&
                        (tokens[(*currToken) + 1].line != currLine)) {
                        abstractNode *varChild = buildVar(tokens, numTokens, currToken);
                        node->children[1] = varChild;
                        return node;
                    // either FUNCCALL or BINARY case
                    } else {
                        if (tokens[*currToken].type == IDEN &&
                            tokens[(*currToken) + 1].type == OP &&
                            !strcmp(tokens[(*currToken) + 1].content, "(")) {
                            token *t = tokenAfterFuncCall(tokens, numTokens, *currToken);
                            // FUNCCALL case
                            if ((*t).line != currLine) {
                                abstractNode *child = buildFuncCall(tokens, numTokens, currToken);
                                node->children[1] = child;
                                return node;
                            // must be BINARY case or ERROR
                            } else {
                                return NULL;
                            }
                        // at this point, must be BINARY case or ERROR
                        } else {
                            return NULL;
                        }
                    }
                    
                } else {
                    printf("ERROR - line %d: expected '=' after identifier\n", tokens[*currToken].line);
                    return NULL;
                }
            } else {
                printf("type not supported!!\n");
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

abstractNode *buildFuncDef(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildAssignVar\n");
        return NULL;
    }

    abstractNode *node = buildNode(FUNCDEF, "");

    // this is the case of when there are no input arguments
    if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#") &&
        tokens[(*currToken) + 1].type == OP && !strcmp(tokens[(*currToken) + 1].content, "#")) {
        *currToken = *currToken + 1;
        if (tokens[(*currToken) + 1].type == IDEN) {
            abstractNode *funcReturn = buildFuncReturn(tokens, numTokens, currToken);
            addChild(node, funcReturn);
        } else {
            printf("ERROR: return type of function not recognized\n");
            return NULL;
        }
    // this is the case when there is at least 1 input
    } else {
        int foundOutput = 0;
        while (!foundOutput) {
            if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#") &&
                tokens[(*currToken) + 1].type == IDEN) {
                int currentLine = tokens[*currToken].line;
                if (tokens[(*currToken) + 2].line == currentLine &&
                    tokens[(*currToken) + 2].type == IDEN) {
                    abstractNode *funcArgChild = buildFuncArg(tokens, numTokens, currToken);
                    addChild(node, funcArgChild);
                // this is the output case
                } else {
                    abstractNode *funcReturn = buildFuncReturn(tokens, numTokens, currToken);
                    addChild(node, funcReturn);
                    foundOutput = 1;
                }
            } else {
                printf("ERROR: malformed input/output for func definition\n");
                return NULL;
            }
        }
    }

    if (tokens[*currToken].type == IDEN) {
        node->content = tokens[*currToken].content;
        (*currToken)++;
        if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "=")) {
            (*currToken)++;
            if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "{")) {
                (*currToken)++;
                abstractNode *bodyChild = buildBody(tokens, numTokens, currToken);
                addChild(node, bodyChild);
                if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "}")) {
                    (*currToken)++;
                    return node;
                } else {
                    printf("ERROR: expected } after function body\n");
                    return NULL;
                }
            } else {
                printf("ERROR: expected { after function name and = in func definition\n");
                return NULL;
            }
        } else {
            printf("ERROR: expected = after function name in func definition\n");
            return NULL;
        }
    } else {
        printf("ERROR: should have function name after type definitions\n");
        return NULL;
    }

}

abstractNode *buildBody(token *tokens, int numTokens, int *currToken) {
    if (*currToken >= numTokens) {
        // TODO: figure out a good way to handle this error;
        printf("ERROR: currToken >= numTokens in buildAssignVar\n");
        return NULL;
    }

    abstractNode *node = buildNode(BODY, "");

    if (node == NULL) {
        //handle error here
        return NULL;
    }

    while (*currToken < numTokens) {
        // determine what kind of NodeType we're making?
        // either IF, IFELSE, ASSIGNVAR, FUNCDEF, FUNCCALL
        if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "}")) {
            printf("closing bracket found\n");
            break;
        } else if (tokens[*currToken].type == OP && !strcmp(tokens[*currToken].content, "#")) {
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
                    abstractNode *child = buildFuncDef(tokens, numTokens, currToken);
                    addChild(node, child);
                } else if (tokens[temp].type == IDEN) {
                    abstractNode *child = buildAssignVar(tokens, numTokens, currToken);
                    addChild(node, child);
                } else {
                    printf("ERROR - line %d: expected assignment or another # line after line %d\n", currLine, currLine);
                    return NULL;
                }
            } else {
                printf("ERROR - line %d: expected a line with content immediately after %d\n", currLine, currLine);
                return NULL;
            }

            
        } else if (tokens[*currToken].type == IDEN &&
            tokens[(*currToken) + 1].type == OP &&
            !strcmp(tokens[(*currToken) + 1].content, "(")) {
            token *t = tokenAfterFuncCall(tokens, numTokens, *currToken);
            // FUNCCALL case
            if ((*t).line != tokens[*currToken].line) {
                abstractNode *child = buildFuncCall(tokens, numTokens, currToken);
                addChild(node, child);
            // must be BINARY case or ERROR
            } else {
                return NULL;
            }
        // currently this IF/IFELSE check doesn't take into account BINARYS
        } else if ((tokens[*currToken].type == IDEN &&
            tokens[(*currToken) + 1].type == OP &&
            !strcmp(tokens[(*currToken) + 1].content, "?")) ||
            !strcmp(tokenAfterFuncCall(tokens, numTokens, *currToken)->content, "?")) {
            abstractNode *child = buildIfOrIfElse(tokens, numTokens, currToken);
            addChild(node, child);
        } else {
            printf("case not handled yet\n");
            break;
        }
    }

    return node;
}

int build(token *tokens, int numTokens, abstractNode **root) {
    int currToken = 0;
    *root = buildBody(tokens, numTokens, &currToken);

    // no leftover tokens
    if (currToken == numTokens) {
        printAST(*root, "", "     ");
    } else {
        printf("ERROR: leftover tokens?\n");
        return 0;
    }
    
    // TODO: ERROR check *root isn't null
    return 1;
}
