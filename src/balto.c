#include "include/balto.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/asm_frontend.h"
#include <stdlib.h>
void balto_compile(char* src){
    lexer_t* lexer = init_lexer(src);
    parser_t* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    char* s = asm_f(root);
    printf("%s\n", s);
}

void balto_compile_file(const char* filename){
    char* src = balto_read_file(filename);
    balto_compile(src);
    free(src);
}