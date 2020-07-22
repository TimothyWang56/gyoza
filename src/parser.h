#ifndef PARSER_SEEN
#define PARSER_SEEN

#include "tokens.h"
#include "nodes.h"

abstractNode *buildNode(nodeType type, char *content);
void addChild(abstractNode *node, abstractNode *child);
abstractNode *buildLit(token *tokens, int numTokens, int *currToken);
abstractNode *buildVar(token *tokens, int numTokens, int *currToken);
abstractNode *buildFuncReturn(token *tokens, int numTokens, int *currToken);
abstractNode *buildFuncArg(token *tokens, int numTokens, int *currToken);
token *tokenAfterFuncCall(token *tokens, int numTokens, int currToken);
abstractNode *buildCondition(token *tokens, int numTokens, int *currToken);
abstractNode *buildIfOrIfElse(token *tokens, int numTokens, int *currToken);
int isRightAssociative(char *operator);
int operatorPrecedence(char *operator);
void addNodeToOperandStack(stackNode **operandStack, abstractNode *node);
abstractNode *buildBinary(token *tokens, int numTokens, int *currToken);
abstractNode *buildFuncCall(token *tokens, int numTokens, int *currToken);
abstractNode *buildAssignVar(token *tokens, int numTokens, int *currToken);
abstractNode *buildFuncDef(token *tokens, int numTokens, int *currToken);
abstractNode *buildBody(token *tokens, int numTokens, int *currToken);
int build(token *tokens, int numTokens, abstractNode **root);

#endif
