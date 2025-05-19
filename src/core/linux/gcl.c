#ifdef __GCL_LINUX__

#include <internal/__linux.h>

#define set_wrapper(src, dst) if (src) {dst = src;}
#define print_stdout(buffer) gcl_write(gcl_stdout, buffer, strlen(buffer))

static int initialized = false;
static DWORD console_mode = 0;
static gclApplication_t application = {0};

void    gcl_init(gclApplication_t* _application) {
	if (initialized) {
		return;
	}

    initialized = true;
	application = *_application;

    gcl_stdin->handle = 0;
    gcl_stdout->handle = 1;
    gcl_stderr->handle = 2;

    set_wrapper(_application->output_error, __gcl_output_error)
	set_wrapper(_application->allocator, __gcl_allocator)
	set_wrapper(_application->free_block, __gcl_free_block)
}
void 	gcl_terminate() {
    if (!initialized) {
        return;
    }
	if (application.reset_terminal_color_on_exit) {
		print_stdout(RESET_COLOR);
	}
	if (application.clear_terminal_on_exit) {
		print_stdout(CLEAR_SCREEN);
	}

    initialized = false;
}

#endif // __GCL_LINUX__