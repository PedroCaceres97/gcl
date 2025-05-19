#ifndef __GCL_CORE_H__
#define __GCL_CORE_H__

#include <gcl/defs.h>

typedef enum {
    gcl_allocated_file
} gcl_allocator_type;

typedef enum {
    gcl_read_bit     =    1 << 0,
    gcl_write_bit    =    1 << 1,
    gcl_truncate_bit =    1 << 2,
    gcl_invalid_mask = ~((1 << 4) - 1)
} gcl_open_bit;

typedef enum {
    gcl_seek_begin 			=    1 << 0,
    gcl_seek_current		=    1 << 1,
    gcl_seek_end			=    1 << 2,
    gcl_seek_invalid_mask	= ~((1 << 3) - 1)
} gcl_seek_bit;

typedef struct gclFile_t* gclFile;

/*
    To work with these std files you need to call gcl_init()
*/
extern gclFile const gcl_stdin;
extern gclFile const gcl_stdout;
extern gclFile const gcl_stderr;

#ifdef __cplusplus
extern "C" {
#endif

size_t  gcl_read(gclFile file, char* buffer, size_t bufsz);
size_t  gcl_write(gclFile file, const char* buffer, size_t bufsz);

gclFile gcl_open(const char* filename, int mode);
int     gcl_close(gclFile file);

size_t  gcl_seek(gclFile file, size_t offset, int origin);
size_t  gcl_tell(gclFile file);

/*
    This functions returns the size of a file at the moment of the openning given by the OS,
    that means that a file size its not updated every time you write.
    To get the actual size after writing you could do gcl_seek(file, 0, gcl_seek_end) or
    close the file and reopen it.
*/
size_t  gcl_file_size(gclFile file);

/*
    These functions affect only stdin
    gcl_ignore() is the same that calling:
        gcl_read(gcl_stdin, [buffer], 1);
        gcl_flush();
*/
void    gcl_flush();
void    gcl_ignore();

#ifdef __cplusplus
}
#endif

#endif // __GCL_CORE_H__