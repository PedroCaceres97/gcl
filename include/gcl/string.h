#ifndef __GCL_STRING_H__
#define __GCL_STRING_H__

#include <gcl/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

char* gcl_strdupf(const char* format, ...);
char* gcl_strvdupf(const char* format, va_list args);

void  gcl_strtail(char* dst, const char* tail);
void  gcl_strctail(char* dst, const char* tail, char chr, int inclusive);

void  gcl_strrep(char* dst, char target, char chr);

#ifdef __cplusplus
}
#endif

#endif // __GCL_STRING_H__