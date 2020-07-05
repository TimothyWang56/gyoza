typedef enum tokenType { IDEN, OP, INT, FLT, STR, BOOL } type;

typedef struct Token {
    int line;
    type type;
    char *content;

} token;
