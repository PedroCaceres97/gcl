#ifdef __GCL_WINDOWS__

#include <gcl/terminal.h>
#include <internal/__windows.h>

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

    gcl_stdin->handle = GetStdHandle(STD_INPUT_HANDLE);
    gcl_stdout->handle = GetStdHandle(STD_OUTPUT_HANDLE);
    gcl_stderr->handle = GetStdHandle(STD_ERROR_HANDLE);

    set_wrapper(_application->output_error, __gcl_output_error)
	set_wrapper(_application->allocator, __gcl_allocator)
	set_wrapper(_application->free_block, __gcl_free_block)

	if (_application->enable_virtual_terminal) {
		GetConsoleMode(gcl_stdout->handle, &console_mode);
		SetConsoleMode(gcl_stdout->handle, console_mode | 4);
	}
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
	if (application.enable_virtual_terminal) {
		SetConsoleMode(gcl_stdout->handle, console_mode);
	}

	initialized = false;
}

#endif // __GCL_WINDOWS__