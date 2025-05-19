#ifndef __GCL_WINDOWS_H__
#define __GCL_WINDOWS_H__

#ifdef __GCL_WINDOWS__

#include <direct.h>
#include <windows.h>

#define __GCL_ALLOW_WRAPPERS_VIEW__
#include <gcl/wrappers.h>
#include <gcl/gcl.h>

struct gclFile_t {
    int mode;
    size_t os_size;
    char filename[512];
    HANDLE handle;
};

int __translate_open_mode(int mode, DWORD* access, DWORD* disposition);
int __translate_seek_origin(int origin, DWORD* out);
void __windowfy_path(const char* path, char* buffer);

#endif // __GCL_WINDOWS__

#endif // __GCL_WINDOWS_H__