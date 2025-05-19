#include <gcl/core.h>

#include <stdio.h>
#include <stdlib.h>

static void __gcl_default_output_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

static void __gcl_default_free_block(void* block, int type) {
    free(block);
}
static void* __gcl_default_allocator(size_t bytes, int type) {
    return calloc(1, bytes);
}


void    (*__gcl_output_error)(const char* format, ...)  = __gcl_default_output_error;

void    (*__gcl_free_block)(void* block, int type)      = __gcl_default_free_block;
void*   (*__gcl_allocator)(size_t bytes, int type)      = __gcl_default_allocator;