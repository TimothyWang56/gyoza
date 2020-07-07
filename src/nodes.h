#ifndef NODES_SEEN
#define NODES_SEEN

// BINARYs are special FUNCCALLs, like +, -, /, *, >, < ==, != and use infix notation
typedef enum NodeType { LITERAL, BINARY, IF, IFELSE, CONDITION, BODY, FUNCDEF, FUNCCALL, ASSIGNVAR, VAR } nodeType;

typedef struct AbstractSyntaxTreeNode {
    nodeType type;
    char *content;
    int numChildren;
    struct AbstractSyntaxTreeNode *children;

} abstractNode;

#endif