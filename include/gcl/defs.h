#ifndef __GCL_DEFS_H__
#define __GCL_DEFS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef __GCL_GCC__

#define __constructor__(level) __attribute__((constructor(level)))
#define __destructor__(level) __attribute__((destructor(level)))

#endif // __GCL_GCC__

#endif // __GCL_DEFS_H__
