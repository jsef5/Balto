#include "include/parser.h"
#include "include/list.h"
#include "include/types.h"
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
        ast->val = parser_parse_expr(parser);
        return ast;
    }
    AST_T* ast = init_ast(AST_VARIABLE);
    ast->name = val;
    if(parser->token->type == TOKEN_COLON){
        parser_eat(parser, TOKEN_COLON);
        while(parser->token->type == TOKEN_ID) {
            ast->datatype = typename_toi(parser->token->val);
            parser_eat(parser, TOKEN_ID);
            if(parser->token->type == TOKEN_LT) {
                parser_eat(parser, TOKEN_LT);
                ast->datatype += typename_toi(parser->token->val);
                parser_eat(parser, TOKEN_ID);
                parser_eat(parser, TOKEN_GT);
            }
        }
    }else {
        if(parser->token->type == TOKEN_LPAREN) {
            ast->type = AST_CALL;
            ast->val = parser_parse_list(parser);
        }
    }
    return ast;
}

AST_T* parser_parse_block(parser_t* parser) {
    parser_eat(parser, TOKEN_LBRACE);
    AST_T* ast = init_ast(AST_COMPOUND);
    while(parser->token->type != TOKEN_RBRACE) {
        list_push(ast->children, parser_parse_expr(parser));
    }
    parser_eat(parser, TOKEN_RBRACE);
    return ast;
}


AST_T* parser_parse_list(parser_t* parser) {
    parser_eat(parser, TOKEN_LPAREN);
    AST_T* ast = init_ast(AST_COMPOUND);
    list_push(ast->children, parser_parse_expr(parser));
    while(parser->token->type == TOKEN_COMMA){
        parser_eat(parser, TOKEN_COMMA);
        list_push(ast->children, parser_parse_expr(parser));
    }
    parser_eat(parser, TOKEN_RPAREN);
    if(parser->token->type == TOKEN_COLON){
        parser_eat(parser, TOKEN_COLON);
        while(parser->token->type == TOKEN_ID) {
            ast->datatype = typename_toi(parser->token->val);
            parser_eat(parser, TOKEN_ID);
            if(parser->token->type == TOKEN_LT) {
                parser_eat(parser, TOKEN_LT);
                ast->datatype += typename_toi(parser->token->val);
                parser_eat(parser, TOKEN_ID);
                parser_eat(parser, TOKEN_GT);
            }
        }
    }
    if(parser->token->type == TOKEN_RARROW){
        parser_eat(parser, TOKEN_RARROW);
        ast->type = AST_FUNCTION;
        ast->val = parser_parse_compound(parser);
    }
    return ast;
}

AST_T* parser_parse_int(parser_t* parser){
    int int_val = atoi(parser->token->val);
    parser_eat(parser, TOKEN_INT);
    AST_T* ast = init_ast(AST_INT);
    ast->int_val = int_val;
    return ast;
}

AST_T* parser_parse_expr(parser_t* parser){
    switch(parser->token->type){
        case TOKEN_ID: return parser_parse_id(parser);
        case TOKEN_LPAREN: return parser_parse_list(parser);
        case TOKEN_INT: return parser_parse_int(parser);
        default: {printf("[Parser]: Unexpected token '%s'\n", token_tos(parser->token));exit(1);}
    }
}

AST_T* parser_parse_compound(parser_t* parser){
    unsigned int should_close = 0;
    if(parser->token->type == TOKEN_LBRACE) {
        parser_eat(parser, TOKEN_LBRACE);
        should_close = 1;
    }
    AST_T* compound = init_ast(AST_COMPOUND);
    while(parser->token->type != TOKEN_EOF && parser->token->type != TOKEN_RBRACE) {
        list_push(compound->children, parser_parse_expr(parser));
        if(parser->token->type == TOKEN_SEMI) {
            parser_eat(parser, TOKEN_SEMI);
        }
    }
    if(should_close) parser_eat(parser, TOKEN_RBRACE);
    return compound;
}
