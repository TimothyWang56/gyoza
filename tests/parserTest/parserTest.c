#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../minunit.h"
#include "../../src/tokens.h"
#include "../../src/lexer.h"

int tests_run = 0;

static char *testBuildNode() {
    return 0;
}

static char *allTests() {
    mu_run_test(testBuildNode);
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