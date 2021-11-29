#ifndef BALTO_PARSER_H
#define BALTO_PARSER_H
#include "lexer.h"
#include "AST.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* token;
} parser_t;

parser_t* init_parser(lexer_t* lexer);

token_t* parser_eat(parser_t* parser, int type);

AST_T* parser_parse(parser_t* parser);
AST_T* parser_parse_compound(parser_t* parser);
AST_T* parser_parse_expr(parser_t* parser);
AST_T* parser_parse_id(parser_t* parser);

#endif