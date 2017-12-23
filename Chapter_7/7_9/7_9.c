/*
Exercise 7-9. Functions like isupper can be implemented to save space or to
save time. Explore both possibilities.

Measuring the time to compare the function call overhead. On my pc this takes
almost 20 sec (8 + 12) for both tests.
*/

#include <stdio.h>
#include <time.h>

#define m_isupper(c) ((c) >= 'A' && (c) <= 'Z')? 1:0
int mm_isupper(char);


int main(void)
{
    clock_t start, end;
    double mtime1, mtime2, mtime3;
    int i, res;

    start = clock();
    i = 0;
    while (++i)
        res = m_isupper('g');
    end = clock();
    mtime1 = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    i = 0;
    while (++i)
        res = mm_isupper('g');
    end = clock();
    mtime2 = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Total time1: %f\n", mtime1);
    printf("Total time2: %f\n", mtime2);
    return 0;
}

int mm_isupper(char c)
{
    return (c >= 'A' && c <= 'Z');
}
