#ifndef BALTO_TOKEN_H
#define BALTO_TOKEN_H
typedef struct TOKEN_STRUCT {
    char* val;
    enum {
        TOKEN_ID,
        TOKEN_EQ,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_RBRACE,
        TOKEN_LBRACE,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_LT,
        TOKEN_GT,
        TOKEN_RARROW,
        TOKEN_INT,
        TOKEN_SEMI,
        TOKEN_EOF,
    } type;
} token_t;

token_t* init_token(char* val, int type);

const char* token_type_tos(int type);
char* token_tos(token_t* token);
#endif