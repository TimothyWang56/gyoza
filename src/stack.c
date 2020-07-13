// https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
// C program for linked list implementation of stack 
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "nodes.h"

stackNode *newStack() {
    return newNode(NULL);
}

stackNode *newNode(abstractNode *data) {
    stackNode *node = malloc(sizeof(stackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

int isEmpty(stackNode *root) {
    return (root->data == NULL);
}

void push(stackNode **root, abstractNode *data) {
    stackNode* node = newNode(data);
    node->next = *root;
    *root = node;
    printf("%s pushed to stack\n", data->content);
}

abstractNode *pop(stackNode **root) {
    if (isEmpty(*root))
        return NULL;
    stackNode* temp = *root;
    *root = (*root)->next;
    abstractNode *popped = temp->data;
    // if 
    // free(temp);

    printf("%s popped from stack\n", popped->content);
    return popped;
}

abstractNode *peek(stackNode* root) {
    if (isEmpty(root))
        return NULL;
    return root->data;
}
