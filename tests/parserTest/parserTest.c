#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../minunit.h"
#include "../../src/tokens.h"
#include "../../src/stack.h"
#include "../../src/lexer.h"
#include "../../src/parser.h"

int tests_run = 0;

static char *testBuildNode() {
    nodeType type = INT_LITERAL;
    char *content = "74";

    abstractNode *node = buildNode(type, content);

    mu_assert("Error: type of node is incorrect", node->type == INT_LITERAL);
    mu_assert("Error: content of node is incorrect", !strcmp(node->content, "74"));
    mu_assert("Error: numChildren of node is incorrect", node->numChildren == 0);

    free(node->children);
    free(node);

    type = CONDITION;
    content = "";

    node = buildNode(type, content);

    mu_assert("Error: type of node is incorrect", node->type == CONDITION);
    mu_assert("Error: content of node is incorrect", !strcmp(node->content, ""));
    mu_assert("Error: numChildren of node is incorrect", node->numChildren == 1);

    free(node->children);
    free(node);

    return 0;
}

static char *testAddChild() {
    abstractNode *parent = buildNode(BODY, "Parent");
    abstractNode *child1 = buildNode(ASSIGNVAR, "First child");

    mu_assert("", parent->numChildren == 0);

    addChild(parent, child1);

    mu_assert("", parent->numChildren == 1);
    mu_assert("", !strcmp(parent->children[0]->content, "First child"));

    abstractNode *child2 = buildNode(STRING_LITERAL, "\"Second child\"");

    addChild(parent, child2);

    mu_assert("", parent->numChildren == 2);
    mu_assert("", !strcmp(parent->children[0]->content, "First child"));
    mu_assert("", !strcmp(parent->children[1]->content, "\"Second child\""));

    free(parent->children);
    free(parent);

    free(child1->children);
    free(child1);
    
    free(child2->children);
    free(child2);

    return 0;
}

static char *allTests() {
    mu_run_test(testBuildNode);
    mu_run_test(testAddChild);
    return 0;
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    char *result = allTests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("All PARSER TESTS PASSED\n");
    }
    printf("Parser tests run: %d\n", tests_run);

    return result != 0;
}