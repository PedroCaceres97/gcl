#include <gcl/gcl.h>
#include <gcl/core.h>
#include <gcl/terminal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gcl_output(const char* format, ...) {
    printf(BOLD_GREEN_TEXT("Gcl Function Call!\n"));

    va_list args, copy;
    va_start(args, format);
    va_copy(copy, args);
    size_t count = vsnprintf(NULL, 0, format, copy);
    char* buffer = calloc(1, count + 1);
    vsnprintf(buffer, count + 1, format, args);
    gcl_write(gcl_stderr, BOLD_RED_TEXT(), strlen(BOLD_RED_TEXT()));
    gcl_write(gcl_stderr, buffer, count);
    gcl_write(gcl_stderr, RESET_COLOR, strlen(RESET_COLOR));

    va_end(copy);
    va_end(args);
}

void print(const char* buffer) {
    gcl_write(gcl_stdout, buffer, strlen(buffer));
}

int main() {
    gclApplication_t application = {0};
    application.enable_virtual_terminal = true;
    application.output_error = gcl_output;
    gcl_init(&application);

    print(GREEN_TEXT("Hola gcl!\n"));
    gcl_write(gcl_stdin, "hola", 4);
    gcl_read(gcl_stdout, NULL, 2);

    gcl_terminate();
    return 0;
}