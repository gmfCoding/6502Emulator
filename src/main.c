#include <stdio.h>
#include "6502.h"


int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    printf("Hello, World!%d", 14467);
    struct processor6502 proc = {0};
    ic6502_restart(&proc);

}