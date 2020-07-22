#ifndef LEXER_SEEN
#define LEXER_SEEN

#include "tokens.h"
int isOperator(char character);
void copyContent(char **content, char **currContent);
void resetValues(char **currContent, int lineLength, int *currCharacterNumber);
void createAndStoreToken(int lineNumber, tokenType type, char **content, token **lineTokens, int *numLineTokens);
int tokenizeLine(char line[], int lineNumber, int *numLineTokens, token **lineTokens, int *maxLineCapacity);

int tokenize(char* fileName, token **tokens, int *numTokens);

#endif
