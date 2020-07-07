#ifndef PARSER_SEEN
#define PARSER_SEEN

#include "tokens.h"
#include "nodes.h"

int build(token *tokens, int numTokens, abstractNode **root);

#endif
