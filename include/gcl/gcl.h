#ifndef __GCL_MAIN_H__
#define __GCL_MAIN_H__

#include <gcl/defs.h>

typedef struct {
    int enable_virtual_terminal;
    int clear_terminal_on_exit;
    int reset_terminal_color_on_exit;
    void (*output_error)(const char* format, ...);
    void (*free_block)(void* block, int type);
    void* (*allocator)(size_t bytes, int type);
} gclApplication_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
    This functions allows the usage of the gcl_std files.
    Without calling it, any attempt of using those files will throw an error.
    Unless a weird error happens in the Windows OS, 
*/
void    gcl_init(gclApplication_t* application);

/*
    Should be called before the end of the program execution if
    enable_virtual_terminal was set to true in gclApplication_t.
    It only has sense to do on windows, but to keep crossplatform platform this function
    does nothing on linux
*/
void    gcl_terminate();

#ifdef __cplusplus
}
#endif

#endif // __GCL_MAIN_H__