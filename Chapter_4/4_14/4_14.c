/*
Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of 
type t. (Block structure will help.)
*/

#include <stdio.h>

#define swap(t,x,y) do {t = x; x = y; y = t;} while (0);

int main(void)
{
    int t, x, y;

    x = 2;
    y = 3;

    printf("x: %d, y: %d\n", x, y);
    swap(t,x,y);
    printf("x: %d, y: %d\n", x, y);

    return 0;
}
