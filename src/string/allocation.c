#include <internal/__string.h>

char* gcl_strvdupf(const char* format, va_list args) {
    va_list copy1, copy2;
    va_copy(copy1, args);
    va_copy(copy2, args);
    
    size_t length = vsnprintf(NULL, 0, format, copy1) + 1;
    char*  buffer = calloc(1, length);
    vsnprintf(buffer, length, format, copy2);

    va_end(copy1);
    va_end(copy2);
    return buffer;
}

char* gcl_strdupf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char* buffer = gcl_strvdupf(format, args);
    va_end(args);
    return buffer;
}