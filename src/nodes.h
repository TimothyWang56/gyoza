#ifndef NODES_SEEN
#define NODES_SEEN

// BINARYs are special FUNCCALLs, like +, -, /, *, >, < ==, !=, &&, || and use infix notation
typedef enum NodeType { INT_LITERAL, FLOAT_LITERAL, STRING_LITERAL, BINARY, IF, IFELSE, CONDITION, BODY, FUNCDEF, FUNCARG, FUNCCALL, FUNCRETURN, ASSIGNVAR, VAR } nodeType;

typedef struct AbstractSyntaxTreeNode {
    nodeType type;
    char *content;
    int numChildren;
    struct AbstractSyntaxTreeNode **children;

} abstractNode;

#endif
