/*
This is a test C source file to test 6_6.
*/

#include <stdio.h>

#define GREATINGS "hello there"
#define MCONST 333
#undef MCONST

int main(void)
{
    printf("%s %i\n", GREATINGS, MCONST);
}

#define WRONG "so wrong
