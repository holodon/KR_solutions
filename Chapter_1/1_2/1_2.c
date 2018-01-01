/*
Exercise 1-2. Experiment to find out what happens when prints 's argument
string contains \c, where c is some character not listed above.

- result: it wont compile with
    gcc -g -std=c99 -Wall -Wextra -pedantic-errors 1_2.c
*/

#include <stdio.h>

int main(void)
{
    printf("hello, \]");
    printf("world\o");
    printf("\n");
}
