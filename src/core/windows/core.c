#ifdef __GCL_WINDOWS__

#include <internal/__windows.h>

#define is_std_file(file) (file == gcl_stdin || file == gcl_stdout || file == gcl_stderr)

static struct gclFile_t __gcl_stdin = {.os_size = 0, .mode = gcl_read_bit, .filename = "stdin", INVALID_HANDLE_VALUE};
static struct gclFile_t __gcl_stdout = {.os_size = 0, .mode = gcl_write_bit, .filename = "stdout", INVALID_HANDLE_VALUE};
static struct gclFile_t __gcl_stderr = {.os_size = 0, .mode = gcl_write_bit, .filename = "stderr", INVALID_HANDLE_VALUE};

gclFile const gcl_stdin = &__gcl_stdin;
gclFile const gcl_stdout = &__gcl_stdout;
gclFile const gcl_stderr = &__gcl_stderr;

size_t  gcl_read(gclFile file, char* buffer, size_t bufsz) {
    if (bufsz == 0) {
        return 0;
    }

    if ((file->mode & gcl_read_bit) == 0) {
        __gcl_output_error("[gcl]: file \"%s\" its not readable\n", file->filename);
        return -1;
    }

    DWORD readed = 0;
    int success = ReadFile(file->handle, buffer, bufsz, &readed, NULL);
    return (success) ? (size_t)readed : -1;
}
size_t  gcl_write(gclFile file, const char* buffer, size_t bufsz) {
    if (bufsz == 0) {
        return 0;
    }

    if ((file->mode & gcl_write_bit) == 0) {
        __gcl_output_error("[gcl]: file \"%s\" its not writable\n", file->filename);
        return -1;
    }

    DWORD writed = 0;
    int success = WriteFile(file->handle, buffer, bufsz, &writed, NULL);
    return (success) ? (size_t)writed : -1;
}

gclFile gcl_open(const char* filename, int mode) {
    DWORD access = 0;
	DWORD disposition = 0;

	if (!__translate_open_mode(mode, &access, &disposition)) {
		__gcl_output_error("[gcl]: Failed to open file -> %s\n", filename);
		return NULL;
	}
	
	gclFile file = __gcl_allocator(sizeof(struct gclFile_t), gcl_allocated_file);
	file->mode   = mode;
	__windowfy_path(filename, file->filename);
	file->handle = CreateFileA(file->filename, access, 0, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file->handle == INVALID_HANDLE_VALUE) {
		__gcl_output_error("[gcl]: Failed to open file -> %s\n", filename);
		__gcl_free_block(file, gcl_allocated_file);
		return NULL;
	}

    DWORD size_high = 0;
	DWORD size_low  = GetFileSize(file->handle, &size_high);
	if (size_low == INVALID_FILE_SIZE) {
		__gcl_output_error("[gcl]: Failed to get file size -> %s\n", filename);
		__gcl_free_block(file, gcl_allocated_file);
		return NULL;
	}

#if defined(__GCL_X86__)
    file->os_size = (size_t)size_low;
#elif defined(__GCL_X86_64__)
    file->os_size = ((size_t)size_high << 32) | size_low;
#endif

	return file;
}
int     gcl_close(gclFile file) {
    if (is_std_file(file)) {
        __gcl_output_error("[gcl]: Did you really tried to close an std file?\n");
		return false;
	}
	if (!CloseHandle(file->handle)) {
		__gcl_output_error("[gcl]: Failed to close file -> %s\n", file->filename);
		return false;
	}
	__gcl_free_block(file, gcl_allocated_file);
	return true;
}

size_t  gcl_seek(gclFile file, size_t offset, int origin) {
    if (is_std_file(file)) {
		__gcl_output_error("[gcl]: Unable to seek on std file -> %s\n", file->filename);
		return -1;
	}

	DWORD MoveMethod = 0;
	if (!__translate_seek_origin(origin, &MoveMethod)) {
		__gcl_output_error("[gcl]: Invalid seek origin value -> %i\n", origin);
		return -1;
	}
	
	if (origin == gcl_seek_begin && offset < 0) {
		__gcl_output_error("[gcl]: Cant use a negative offset at the begin of the file -> %s\n", file->filename);
		return -1;
	} else if (origin == gcl_seek_end && offset > 0) {
		__gcl_output_error("[gcl]: Cant use a positive offset at the end of the file -> %s\n", file->filename);
		return -1;
	}

    #if defined(__GCL_X86_64__)

    LONG pointer_high = (LONG)(offset >> 32);
	DWORD pointer_low = SetFilePointer(file->handle, offset & ((1ull << 32) - 1), &pointer_high, MoveMethod);
	if (pointer_low == INVALID_SET_FILE_POINTER) {
		__gcl_output_error("[gcl]: Failed to set file pointer -> %s\n[gcl]: (Maybe you are offsetting too much)\n", file->filename);
		return -1;
	}
	return (size_t)(((size_t)pointer_high << 32) | pointer_low);

    #elif defined(__GCL_X86__)

    DWORD pointer_high = 0;
	DWORD pointer_low = SetFilePointer(file->handle, offset, &pointer_high, origin);
	if (pointer_low == INVALID_SET_FILE_POINTER) {
		__gcl_output_error("[gcl]: Failed to set file pointer -> %s\n[gcl]: (Maybe you are offsetting too much)\n", file->filename);
		return -1;
	}
	return pointer_low;

    #endif
}
size_t  gcl_tell(gclFile file) {
	if (is_std_file(file)) {
		__gcl_output_error("[gcl]: Unable to tell on std file -> %s\n", file->filename);
		return -1;
	}
	
    #if defined(__GCL_X86_64__)

    LONG pointer_high = 0;
	DWORD pointer_low = SetFilePointer(file->handle, 0, &pointer_high, gcl_seek_current);
	if (pointer_low == INVALID_SET_FILE_POINTER) {
		__gcl_output_error("[gcl]: Failed to set file pointer -> %s\n[gcl]: (in tell function)\n", file->filename);
		return -1;
	}
	return (size_t)(((size_t)pointer_high << 32) | pointer_low);

    #elif defined(__GCL_X86__)

    DWORD pointer_high = 0;
	DWORD pointer_low = SetFilePointer(file->handle, 0, &pointer_high, gcl_seek_current);
	if (pointer_low == INVALID_SET_FILE_POINTER) {
		__gcl_output_error("[gcl]: Failed to set file pointer -> %s\n[gcl]: (in tell function)\n", file->filename);
		return -1;
	}
	return pointer_low;

    #endif
}

// stdin functions
void    gcl_flush() {
	FlushConsoleInputBuffer(gcl_stdin->handle);
}
void    gcl_ignore() {
    char c;
    DWORD readed;
    ReadFile(gcl_stdin->handle, &c, 1 ,&readed, NULL);
    FlushConsoleInputBuffer(gcl_stdin->handle);
}

size_t gcl_file_size(gclFile file) {
	return file->os_size;
}

#endif // __GCL_WINDOWS__