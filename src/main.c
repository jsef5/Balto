#include "include/balto.h"
#include "include/macros.h"
#include <stdio.h>
int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Usage: %s <infile>\n", argv[0]);
        return 1;
    }
    balto_compile_file(argv[1]);
    return 0;
}