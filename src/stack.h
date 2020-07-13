#ifndef STACK_SEEN
#define STACK_SEEN

#include "nodes.h"

// A structure to represent a stack
typedef struct StackNode {
    abstractNode *data;
    struct StackNode *next;
} stackNode;

stackNode *newStack();
stackNode *newNode(abstractNode *data);
int isEmpty(stackNode *root);
void push(stackNode **root, abstractNode *data);
abstractNode *pop(stackNode **root);
abstractNode *peek(stackNode* root);

#endif
