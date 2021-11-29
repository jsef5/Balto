#include "include/asm_frontend.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* asm_f_compound(AST_T* ast) {

}
char* asm_f_assignement(AST_T* ast) {

}
char* asm_f_variable(AST_T* ast) {

}
char* asm_f_call(AST_T* ast) {

}
char* asm_f_int(AST_T* ast) {

}
char* asm_f(AST_T* ast) {
    char* val = calloc(1, sizeof(char))
    char* nval = 0;

    switch(ast->type) {
        case AST_COMPOUND: nval = asm_f_compound(ast); break;
        case AST_ASSIGNMENT: nval = asm_f_assignement(ast); break;
        case AST_VARIABLE: nval = asm_f_variable(ast); break;
        case AST_CALL: nval = asm_f_call(ast); break;
        case AST_INT: nval = asm_f_int(ast); break;
        default: printf("[ASM Frontend]: No frontend for AST of type '%d'\n", ast->type); exit(1);
    }
    val = realloc(val, (strlen(nval) + 1) * sizeof(char));
    strcat(val, nval);
    return val;
}