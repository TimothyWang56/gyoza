#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../minunit.h"
#include "../../src/tokens.h"
#include "../../src/lexer.h"

int tests_run = 0;

static char *testIsOperator() {
    mu_assert("Error: # should be an operator", isOperator('#'));
    mu_assert("Error: ( should be an operator", isOperator('('));
    mu_assert("Error: ) should be an operator", isOperator(')'));
    mu_assert("Error: { should be an operator", isOperator('{'));
    mu_assert("Error: } should be an operator", isOperator('}'));
    mu_assert("Error: / should be an operator", isOperator('/'));
    mu_assert("Error: ? should be an operator", isOperator('?'));
    mu_assert("Error: + should be an operator", isOperator('+'));
    mu_assert("Error: - should be an operator", isOperator('-'));
    mu_assert("Error: * should be an operator", isOperator('*'));
    mu_assert("Error: = should be an operator", isOperator('='));
    mu_assert("Error: ! should be an operator", isOperator('!'));
    mu_assert("Error: , should be an operator", isOperator(','));
    mu_assert("Error: < should be an operator", isOperator('<'));
    mu_assert("Error: > should be an operator", isOperator('>'));
    mu_assert("Error: ^ should be an operator", isOperator('^'));
    mu_assert("Error: \% should be an operator", isOperator('%'));
    mu_assert("Error: & should be an operator", isOperator('&'));
    mu_assert("Error: | should be an operator", isOperator('|'));

    return 0;
}

static char *testCopyContent() {
    char *currContent = "This is a test";
    char *content;
    copyContent(&content, &currContent);
    mu_assert("Error: content and currContent are not the same", !strcmp(content, currContent));
    
    currContent = "This is test number 2";
    copyContent(&content, &currContent);
    mu_assert("Error: content and currContent are not the same", !strcmp(content, currContent));

    return 0;
}

static char *testResetValues() {
    char *currContent = malloc((strlen("This is a test") + 1) * sizeof(char));
    strcpy(currContent, "This is a test");
    int currCharacterNumber = 5;
    int lineLength = strlen(currContent);
    resetValues(&currContent, lineLength, &currCharacterNumber);
    mu_assert("Error: currContent should be an empty string", !strcmp("", currContent));
    mu_assert("Error: currCharNumber should be 0", currCharacterNumber == 0);
    free(currContent);

    currContent = malloc((strlen("This is test number 2") + 1) * sizeof(char));
    strcpy(currContent, "This is test number 2");
    currCharacterNumber = 10;
    lineLength = strlen(currContent);
    resetValues(&currContent, lineLength, &currCharacterNumber);
    mu_assert("Error: currContent should be an empty string", !strcmp("", currContent));
    mu_assert("Error: currCharNumber should be 0", currCharacterNumber == 0);
    free(currContent);

    return 0;
}

static char *testCreateAndStoreToken() {
    int lineNumber = 3;
    int numLineTokens = 0;
    tokenType type = STR;
    char *content = "\"This is a test token.\"";
    token *lineTokens = malloc(sizeof(token) * 1);

    createAndStoreToken(lineNumber, type, &content, &lineTokens, &numLineTokens);
    mu_assert("Error: token 1 line number is incorrect", lineTokens[0].line == 3);
    mu_assert("Error: token 1 content is incorrect", !strcmp(lineTokens[0].content, "\"This is a test token.\""));
    mu_assert("Error: token 1 type is incorrect", lineTokens[0].type == STR);

    token *temp = realloc(lineTokens, sizeof(token) * 3);
    lineTokens = temp;
    content = "\"This is a second test token\"";

    createAndStoreToken(lineNumber, type, &content, &lineTokens, &numLineTokens);
    mu_assert("Error: token 1 line number is incorrect", lineTokens[0].line == 3);
    mu_assert("Error: token 1 content is incorrect", !strcmp(lineTokens[0].content, "\"This is a test token.\""));
    mu_assert("Error: token 1 type is incorrect", lineTokens[0].type == STR);
    mu_assert("Error: token 2 line number is incorrect", lineTokens[1].line == 3);
    mu_assert("Error: token 2 content is incorrect", !strcmp(lineTokens[1].content, "\"This is a second test token\""));
    mu_assert("Error: token 2 type is incorrect", lineTokens[1].type == STR);

    content = "4.0";
    type = FLT;
    lineNumber = 5;

    createAndStoreToken(lineNumber, type, &content, &lineTokens, &numLineTokens);
    mu_assert("Error: token 1 line number is incorrect", lineTokens[0].line == 3);
    mu_assert("Error: token 1 content is incorrect", !strcmp(lineTokens[0].content, "\"This is a test token.\""));
    mu_assert("Error: token 1 type is incorrect", lineTokens[0].type == STR);
    mu_assert("Error: token 2 line number is incorrect", lineTokens[1].line == 3);
    mu_assert("Error: token 2 content is incorrect", !strcmp(lineTokens[1].content, "\"This is a second test token\""));
    mu_assert("Error: token 2 type is incorrect", lineTokens[1].type == STR);
    mu_assert("Error: token 3 line number is incorrect", lineTokens[2].line == 5);
    mu_assert("Error: token 3 content is incorrect", !strcmp(lineTokens[2].content, "4.0"));
    mu_assert("Error: token 3 type is incorrect", lineTokens[2].type == FLT);

    free(lineTokens);

    return 0;
}

static char *testTokenizeLine() {
    char line[] = "count = 5";
    int lineNumber = 1;
    int numLineTokens = 0;
    int maxLineCapacity = 10;
    token *lineTokens = malloc(sizeof(token) * maxLineCapacity);

    tokenizeLine(line, lineNumber, &numLineTokens, &lineTokens, &maxLineCapacity);

    mu_assert("Error: numLineTokens is incorrect", numLineTokens == 3);
    mu_assert("Error: token 1 line number is incorrect", lineTokens[0].line == 1);
    mu_assert("Error: token 1 content is incorrect", !strcmp(lineTokens[0].content, "count"));
    mu_assert("Error: token 1 type is incorrect", lineTokens[0].type == IDEN);
    mu_assert("Error: token 2 line number is incorrect", lineTokens[1].line == 1);
    mu_assert("Error: token 2 content is incorrect", !strcmp(lineTokens[1].content, "="));
    mu_assert("Error: token 2 type is incorrect", lineTokens[1].type == OP);
    mu_assert("Error: token 3 line number is incorrect", lineTokens[2].line == 1);
    mu_assert("Error: token 3 content is incorrect", !strcmp(lineTokens[2].content, "5"));
    mu_assert("Error: token 3 type is incorrect", lineTokens[2].type == INT);

    for (int i = 0; i < numLineTokens; i++) {
        free(lineTokens[i].content);
    }

    free(lineTokens);

    return 0;
}

static char *testTokenize() {
    char *fileName = "tokenTest/test1.txt";
    token *tokens;
    int numTokens = 0;

    tokenize(fileName, &tokens, &numTokens);

    mu_assert("Error: numLineTokens is incorrect", numTokens == 5);
    mu_assert("Error: token 1 line number is incorrect", tokens[0].line == 1);
    mu_assert("Error: token 1 content is incorrect", !strcmp(tokens[0].content, "#"));
    mu_assert("Error: token 1 type is incorrect", tokens[0].type == OP);
    mu_assert("Error: token 2 line number is incorrect", tokens[1].line == 1);
    mu_assert("Error: token 2 content is incorrect", !strcmp(tokens[1].content, "int"));
    mu_assert("Error: token 2 type is incorrect", tokens[1].type == IDEN);
    mu_assert("Error: token 3 line number is incorrect", tokens[2].line == 2);
    mu_assert("Error: token 3 content is incorrect", !strcmp(tokens[2].content, "count"));
    mu_assert("Error: token 3 type is incorrect", tokens[2].type == IDEN);
    mu_assert("Error: token 4 line number is incorrect", tokens[3].line == 2);
    mu_assert("Error: token 4 content is incorrect", !strcmp(tokens[3].content, "="));
    mu_assert("Error: token 4 type is incorrect", tokens[3].type == OP);
    mu_assert("Error: token 5 line number is incorrect", tokens[4].line == 2);
    mu_assert("Error: token 5 content is incorrect", !strcmp(tokens[4].content, "5"));
    mu_assert("Error: token 5 type is incorrect", tokens[4].type == INT);

    for (int i = 0; i < numTokens; i++) {
        free(tokens[i].content);
    }

    free(tokens);

    fileName = "tokenTest/test2.txt";
    numTokens = 0;

    tokenize(fileName, &tokens, &numTokens);

    mu_assert("Error: numLineTokens is incorrect", numTokens == 21);
    mu_assert("Error: token 1 line number is incorrect", tokens[0].line == 1);
    mu_assert("Error: token 1 content is incorrect", !strcmp(tokens[0].content, "("));
    mu_assert("Error: token 1 type is incorrect", tokens[0].type == OP);
    mu_assert("Error: token 7 line number is incorrect", tokens[6].line == 1);
    mu_assert("Error: token 7 content is incorrect", !strcmp(tokens[6].content, "{"));
    mu_assert("Error: token 7 type is incorrect", tokens[6].type == OP);
    mu_assert("Error: token 8 line number is incorrect", tokens[7].line == 2);
    mu_assert("Error: token 8 content is incorrect", !strcmp(tokens[7].content, "print"));
    mu_assert("Error: token 8 type is incorrect", tokens[7].type == IDEN);
    mu_assert("Error: token 11 line number is incorrect", tokens[10].line == 2);
    mu_assert("Error: token 11 content is incorrect", !strcmp(tokens[10].content, ")"));
    mu_assert("Error: token 11 type is incorrect", tokens[10].type == OP);
    mu_assert("Error: token 12 line number is incorrect", tokens[11].line == 3);
    mu_assert("Error: token 12 content is incorrect", !strcmp(tokens[11].content, "}"));
    mu_assert("Error: token 12 type is incorrect", tokens[11].type == OP);
    mu_assert("Error: token 16 line number is incorrect", tokens[15].line == 3);
    mu_assert("Error: token 16 content is incorrect", !strcmp(tokens[15].content, "{"));
    mu_assert("Error: token 16 type is incorrect", tokens[15].type == OP);
    mu_assert("Error: token 17 line number is incorrect", tokens[16].line == 4);
    mu_assert("Error: token 17 content is incorrect", !strcmp(tokens[16].content, "print"));
    mu_assert("Error: token 17 type is incorrect", tokens[16].type == IDEN);
    mu_assert("Error: token 20 line number is incorrect", tokens[19].line == 4);
    mu_assert("Error: token 20 content is incorrect", !strcmp(tokens[19].content, ")"));
    mu_assert("Error: token 20 type is incorrect", tokens[19].type == OP);
    mu_assert("Error: token 21 line number is incorrect", tokens[20].line == 5);
    mu_assert("Error: token 21 content is incorrect", !strcmp(tokens[20].content, "}"));
    mu_assert("Error: token 21 type is incorrect", tokens[20].type == OP);

    for (int i = 0; i < numTokens; i++) {
        free(tokens[i].content);
    }

    free(tokens);

    return 0;
}

static char *allTests() {
    mu_run_test(testIsOperator);
    mu_run_test(testCopyContent);
    mu_run_test(testResetValues);
    mu_run_test(testCreateAndStoreToken);
    mu_run_test(testTokenizeLine);
    mu_run_test(testTokenize);
    return 0;
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    char *result = allTests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("All TOKENS TESTS PASSED\n");
    }
    printf("Tokens tests run: %d\n", tests_run);

    return result != 0;
}