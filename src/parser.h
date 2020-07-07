#ifndef PARSER_SEEN
#define PARSER_SEEN

#include "tokens.h"
#include "nodes.h"

int buildAST(token *tokens, int numTokens, abstractNode **root);

#endif
