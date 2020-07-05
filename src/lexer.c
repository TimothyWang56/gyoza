#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum tokenType { IDEN, OP, INT, FLT, STR, BOOL } type;

typedef struct Token {
    int line;
    type type;
    char *content;

} token;

void tokenizeLine(char line[], int lineNumber, int *numLineTokens, token **lineTokens, int *maxLineCapacity) {
    int lineLength = strlen(line);
    // strip of \n if line has it at the end
    if (lineLength > 0 && line[lineLength - 1] == '\n') {
        line[lineLength - 1] = 0;
        lineLength = strlen(line);
    }

    // realloc if length of line tokens is too small. lineLength serves as an upperbound
    // to the number of tokens we can have
    if (*maxLineCapacity < lineLength) {
        printf("reallocing lineTokens... old capacity: %d tokens, new capacity: %d tokens\n", *maxLineCapacity, lineLength);
        token *temp = realloc(*lineTokens, lineLength * sizeof(token));
        *maxLineCapacity = lineLength;
        if (temp == NULL) {
            // handle error when realloc isn't successful
        } else {
            *lineTokens = temp;
        }
    }

    // reset numLineTokens back to 0
    *numLineTokens = 0;
    
    char *currContent = malloc(lineLength * sizeof(char));
    int currCharacterNumber = 0;

    for (int i = 0; line[i] != '\0';) {
        char currChar = line[i];

        // check for string
        if (currChar == '"') {
            currContent[currCharacterNumber] = '"';
            currCharacterNumber++;
            for (int j = i + 1; line[j] != '\0'; j++) {
                currContent[currCharacterNumber] = line[j];
                currCharacterNumber++;
                //TODO: figure out escape characters
                if (line[j] == '"') {
                    //TODO: should it be strlen(currContent) or strlen(currContent) + 1?
                    char *content = malloc(strlen(currContent) + 1);
                    strcpy(content, currContent);
                    token t = {
                        .line = lineNumber,
                        .type = STR,
                        .content = content,
                    };

                    (*lineTokens)[*numLineTokens] = t;
                    (*numLineTokens)++;
                    
                    memset(currContent, 0, lineLength * sizeof(char));
                    currCharacterNumber = 0;
                    i = j + 1;
                    break;
                }
            }
        } else {
            i++;
        }
    }

    free(currContent);
}

// NOTE: whatever calls this functino must free tokens and the contents of the tokens after using them
token* tokenize(char* fileName) {
    FILE* file = fopen(fileName, "r");
    char line[256];
    int lineNumber = 1;
    
    int defaultSize = 10;
    int maxCapacity = defaultSize;
    token *tokens = malloc(sizeof(token) * maxCapacity);
    int numTokens = 0;

    int defaultLineTokensSize = 10;
    int maxLineCapacity = defaultLineTokensSize;
    token *lineTokens = malloc(sizeof(token) * maxLineCapacity);
    int numLineTokens = 0;

    // read file line by line
    while (fgets(line, sizeof(line), file)) {
        // numLineTokens, lineTokens, and maxLineCapacity will be changed from tokenizeLine call.
        // numLineTokens will be the number of tokens in the line.
        // lineTokens will contain exactly numLineTokens number of tokens.
        // maxLineCapacity is the max number of tokens in a line, and will be increased if necessary.
        tokenizeLine(line, lineNumber, &numLineTokens, &lineTokens, &maxLineCapacity);
        // loop over all line tokens to add them into tokens array.
        for (int i = 0; i < numLineTokens; i++) {
            if (numTokens >= maxCapacity) {
                printf("reallocing tokens... old size: %d, new size: %d\n", maxCapacity, maxCapacity * 2);
                maxCapacity *= 2;
                token *temp = realloc(tokens, sizeof(token) * maxCapacity);
                if (temp == NULL) {
                    // handle error when realloc isn't successful
                } else {
                    tokens = temp;
                }
            }

            tokens[numTokens] = lineTokens[i];
            numTokens++;
        }

        lineNumber++;
    }

    // print out all the tokens, for testing purposes
    for (int i = 0; i < numTokens; i++) {
        printf("Token: %d, Line: %d, Type: %d, Content: %s\n", i + 1, tokens[i].line, tokens[i].type, tokens[i].content);
    }

    free(lineTokens);
    fclose(file);

    return tokens;
}

int main() {
    tokenize("example.txt");
    return 0;
}
