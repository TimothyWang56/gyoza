#ifndef NODES_SEEN
#define NODES_SEEN

typedef enum NodeType { LITERAL, BINARY, IF, CONDITION, BODY, ELSE, FUNCDEF, ASSIGN, VAR } nodeType;

typedef struct AbstractSyntaxTreeNode {
    nodeType type;
    char *content;
    int numChildren;
    struct AbstractSyntaxTreeNode *children;

} abstractNode;

#endif
