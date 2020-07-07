typedef enum NodeType { LITERAL, BINARY, IF, BODY, ELSE, FUNCDEF, ASSIGN } nodeType;

typedef struct AbstractSyntaxTreeNode {
    nodeType type;
    int numChildren;
    abstractNode *children;

} abstractNode;
