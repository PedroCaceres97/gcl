#ifdef __GCL_WINDOWS__

#include <internal/__windows.h>

#define NO_ORIGIN_VALUE -1

static const DWORD origins[5] = {NO_ORIGIN_VALUE, FILE_BEGIN, FILE_CURRENT, NO_ORIGIN_VALUE, FILE_END};

int __translate_open_mode(int mode, DWORD* access, DWORD* disposition) {
	if (mode == 0 || mode & gcl_invalid_mask) {
        __gcl_output_error("[gcl]: Invalid file opening mode -> %i\n", mode);
		return false;
	}
	if (mode & gcl_truncate_bit && !(mode & gcl_write_bit)) {
		__gcl_output_error("[gcl]: Truncate mode requires write bit set\n");
		return false;
	}
	
	*access = 0;
	*access |= (mode & gcl_read_bit) ? GENERIC_READ : 0;
	*access |= (mode & gcl_write_bit) ? GENERIC_WRITE : 0;

	if (mode & gcl_truncate_bit) {
		*disposition = CREATE_ALWAYS;
	} else if (mode & gcl_write_bit) {
		*disposition = OPEN_ALWAYS;
	} else {
		*disposition = OPEN_EXISTING;
	}

	return access != 0;
}
int __translate_seek_origin(int origin, DWORD* out) {
	if (origin == 0 || origin & gcl_seek_invalid_mask) {
		__gcl_output_error("[gcl]: Invalid seek origin value -> %i\n", origin);
		return false;
	}

	*out = origins[origin];
	return true;
}

void __windowfy_path(const char* path, char* buffer) {
    strcpy(buffer, path);
    char* slash = strchr(buffer, '/');
    while(slash) {
        *slash++ = '\\';
        slash = strchr(slash, '/');
    }
}

#endif // __GCL_WINDOWS__