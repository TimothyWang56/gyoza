typedef enum TokenType { IDEN, OP, INT, FLT, STR } tokenType;

typedef struct Token {
    int line;
    tokenType type;
    char *content;

} token;
