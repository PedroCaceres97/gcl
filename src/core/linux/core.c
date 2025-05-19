#include <gcl/core.h>

#ifdef __GCL_LINUX__

#include <unistd.h>

struct gclFile_t {
    size_t size;
	gcl_open_bit mode;
	const char* filename;
	int fd;
};

static struct gclFile_t __gcl_stdin = {.size = 0, .mode = gcl_read_bit, .filename = "stdin", -1};
static struct gclFile_t __gcl_stdout = {.size = 0, .mode = gcl_write_bit, .filename = "stdout", -1};
static struct gclFile_t __gcl_stderr = {.size = 0, .mode = gcl_write_bit, .filename = "stderr", -1};

gclFile const gcl_stdin = &__gcl_stdin;
gclFile const gcl_stdout = &__gcl_stdout;
gclFile const gcl_stderr = &__gcl_stderr;

void    gcl_init() {
    gcl_stdin->handle = 0;
    gcl_stdout->handle = 1;
    gcl_stderr->handle = 2;
}

size_t  gcl_read(gclFile file, char* buffer, size_t bufsz) {
    if (bufsz == 0) {
        return 0;
    }

    if ((file->mode & gcl_read_bit) == 0) {
        __gcl_output_error("[gcl]: file \"%s\" its not readable\n", file->filename);
        return -1;
    }

    return (size_t)read(file->fd, buffer, bufsz)
}
size_t  gcl_write(gclFile file, const char* buffer, size_t bufsz) {
    if (bufsz == 0) {
        return 0;
    }

    if ((file->mode & gcl_write_bit) == 0) {
        __gcl_output_error("[gcl]: file \"%s\" its not writable\n", file->filename);
        return -1;
    }

    return (size_t)write(file->fd, buffer, bufsz);
}

gclFile gcl_open(const char* filename, gcl_open_bit mode) {

}
int     gcl_close(gclFile file) {

}

size_t  gcl_seek(gclFile file, size_t offset, gcl_seek_bit origin) {

}
size_t  gcl_tell(gclFile file) {

}

// stdin functions
void    gcl_flush() {

}
void    gcl_ignore() {

}

#endif // __GCL_LINUX__