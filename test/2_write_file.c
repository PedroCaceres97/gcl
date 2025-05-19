#include <gcl/gcl.h>
#include <gcl/core.h>
#include <gcl/terminal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fprint(gclFile file, const char* buffer) {
    gcl_write(file, buffer, strlen(buffer));
}

void print(const char* buffer) {
    gcl_write(gcl_stdout, buffer, strlen(buffer));
}

size_t file_size(gclFile file) {
    size_t size = gcl_seek(file, 0, gcl_seek_end);
    gcl_seek(file, 0, gcl_seek_begin);
    return size;
}

void print_file(gclFile file, const char* name) {
    print("Printing: ");
    print(name);
    print("\n" SET_CYAN_TEXT);

    size_t size = file_size(file);
    char* buffer = calloc(1, size);
    gcl_read(file, buffer, size);
    gcl_write(gcl_stdout, buffer, size);
    print("\n" RESET_COLOR);
}

int main() {
    gclApplication_t application = {0};
    application.enable_virtual_terminal = true;
    gcl_init(&application);

    gclFile test = gcl_open("test.txt", gcl_write_bit);

    print("Writing: test\n" SET_CYAN_TEXT);
    gcl_seek(test, 0, gcl_seek_end);
    fprint(test, "Esto es un archivo de testeo\nHolaholaholaohlaolhoa");
    gcl_close(test);
    test = gcl_open("test.txt", gcl_read_bit);
    print_file(test, "test.txt");
    gcl_close(test);

    gcl_terminate();
    return 0;
}