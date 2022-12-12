#include <include/kernel.hpp>
#include <limine.h>
#include <stddef.h>


struct limine_terminal *term;
//struct limine_framebuffer *fb;

int console_get_term_cnt() {
    if (__term.response->terminal_count > 0) {
        return __term.response->terminal_count;
    }

    return 1;
}

size_t strlen(const char *str)
{
    size_t length = 0;
    while (*str++)
        length++;
    return length;
}

void printc(const char ch) {
    char str[2] = {ch, 0};

    __term.response->write(term, str, 1);
    if (ch == '\b') {
        __term.response->write(term, " ", 1);
        __term.response->write(term, str, 1);
    }

}

void print(const char *str) {
    __term.response->write(term, str, strlen(str));
}
