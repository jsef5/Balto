#include "include/parser.h"
#include "include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
parser_t* init_parser(lexer_t* lexer){
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_next(lexer);
    return parser;
}

token_t* parser_eat(parser_t* parser, int type){
    if(parser->token->type != type) {
        printf("[Parser]: Unexpected token: '%s', was expecting: '%s'\n", token_tos(parser->token), token_type_tos(type));
        exit(1);
    }
    parser->token = lexer_next(parser->lexer);
    return parser->token;
}

AST_T* parser_parse(parser_t* parser){
    // switch(parser->token->type) {

    // }
    return parser_parse_compound(parser);
}

AST_T* parser_parse_id(parser_t* parser){
    char* val = (char*)calloc(strlen(parser->token->val) + 1, sizeof(char));
    strcpy(val, parser->token->val);
    parser_eat(parser, TOKEN_ID);
    if(parser->token->type == TOKEN_EQ) {
        parser_eat(parser, TOKEN_EQ);
        AST_T* ast = init_ast(AST_ASSIGNMENT);
        ast->name = val;
        printf("[Parser_DEBUG]: %s\n", ast->name);
        ast->val = parser_parse_expr(parser);
        return ast;
    }
    AST_T* ast = init_ast(AST_VARIABLE);
    ast->name = val;
    return ast;
}

AST_T* parser_parse_expr(parser_t* parser){
    switch(parser->token->type){
        case TOKEN_ID: return parser_parse_id(parser);
        default: {printf("[Parser]: Unexpected token '%s'\n", token_tos(parser->token));exit(1);}
    }
}

AST_T* parser_parse_compound(parser_t* parser){
    AST_T* compound = init_ast(AST_COMPOUND);
    while(parser->token->type != TOKEN_EOF) {
        list_push(compound->children, parser_parse_expr(parser));
    }
    return compound;
}
