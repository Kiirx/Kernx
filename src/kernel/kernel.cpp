#include <include/kernel.hpp>

volatile struct limine_terminal_request __term = 
{
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) 
{
    for (;;) 
    {
        asm("hlt");
    }
}

extern "C" void _start(void) 
{
    // Check if we have a terminal
    if (__term.response == NULL
     || __term.response->terminal_count < 1) 
    {
        done();
    }

    init();
    printf("Kernx initialized\n");

    done();
}


