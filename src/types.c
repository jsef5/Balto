#include "include/types.h"
#include <string.h>
int typename_toi(const char* name){
    int t = 0;
    size_t len = strlen(name);
    for(unsigned int i = 0; i < len; i++) {
        t += name[i];
    }
    return t;
}