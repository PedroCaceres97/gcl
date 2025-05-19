#ifndef __GCL_WRAPPERS_H__
#define __GCL_WRAPPERS_H__

#ifdef __GCL_ALLOW_WRAPPERS_VIEW__

#include <gcl/core.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void (*__gcl_free_block)(void* block, int type);
extern void* (*__gcl_allocator)(size_t bytes, int type);

extern void (*__gcl_output_error)(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif // __GCL_ALLOW_WRAPPERS_VIEW_H__

#endif // __GCL_WRAPPERS_H__