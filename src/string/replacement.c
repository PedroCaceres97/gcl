#include <internal/__string.h>

void  gcl_strtail(char* dst, const char* tail) {
    size_t length = strlen(tail);
    char*  end = (dst + strlen(dst)) - 1;
    memcpy(end - length, tail, length + 1);
}
void  gcl_strctail(char* dst, const char* tail, char chr, int inclusive) {
    char* pos = strrchr(dst, chr);
    if (!pos) {
        return;
    }
    
    if (!inclusive) {
        pos++;
    }

    size_t length = strlen(tail);
    memcpy(pos, tail, length + 1);
}

void  gcl_strrep(char* dst, char target, char chr) {
    char* last = strchr(dst, target);
    while(last) {
        *last++ = chr;
         last = strchr(last, target);
    }
}