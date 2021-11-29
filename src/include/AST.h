#ifndef BALTO_AST_H
#define BALTO_AST_H
#include "list.h"
typedef struct AST_STRUCT {
    enum {
        AST_COMPOUND,
        AST_FUNCTION,
        AST_CALL,
        AST_ASSIGNMENT,
        AST_TYPE_DEF,
        AST_INT,
        AST_VARIABLE,
        AST_STATEMENT,
        AST_NOOP,
    } type;

    list_t* children;
    char* name;
    struct AST_STRUCT* val;
    int datatype;
    int int_val;
} AST_T;

AST_T* init_ast(int type);
#endif