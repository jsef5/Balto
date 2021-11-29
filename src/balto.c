#include "include/balto.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include <stdlib.h>
void balto_compile(char* src){
    lexer_t* lexer = init_lexer(src);
    parser_t* parser = init_parser(lexer);
    // AST_T* root = parser_parse(parser);
    // printf("%d\n", root->children->size);
    token_t* tok = 0;
    while((tok = lexer_next(lexer))->type != TOKEN_EOF) {
        printf("%s\n", token_tos(tok));
    }
}

void balto_compile_file(const char* filename){
    char* src = balto_read_file(filename);
    balto_compile(src);
    free(src);
}