/*
Exercise 5-5. Write versions of the library functions strncpy , strncat , and 
strncmp , which operate on at most the first n characters of their argument 
strings. For example, strncpy(s,t,n) copies at most n characters of t to s. 
Full descriptions are in Appendix B.
*/

#include <stdio.h>

void mstrncpy(char *s, char *t, int n);
void mstrncat(char *s, char *t, int n);
int mstrncmp(char *s, char *t, int n);

int main(void)
{
    char s[] = "first  string";
    char t[] = "second string";
    char bs[20];                    /* bigger string array for strcat */
    bs[0] = 'H';
    bs[1] = 'e';
    bs[2] = 'l';
    bs[3] = 'l';
    bs[4] = 'o';
    bs[5] = '!';
    bs[6] = '\0';

    printf("s : %s\n", s);
    printf("t : %s\n", t);
    printf("bs: %s\n", bs);
    printf("\n");
    
    mstrncpy(s, t, 5);
    printf("strncpy(s,t,5):\n%s\n\n", s);

    mstrncat(bs, t, 5);
    printf("strncat(bs,t,5):\n%s\n\n", bs);

    printf("strncmp('vladi', 'vlado', 4): %i\n", 
        mstrncmp("vladi", "vlado", 4));
    printf("strncmp('vladi', 'vlado', 5): %i\n", 
        mstrncmp("vladi", "vlado", 5));

    return 0;
}

/* strcpy: copy up to n chars from t to s */
void mstrncpy(char *s, char *t, int n)
{
    int i = 0;
    while ((i++ < n) && (*s++ = *t++))
        ;
    *s = '\0';                          /* terminate */
}

/* strcat: concatenate up to n chars from t to end of s; 
s must be big enough */
void mstrncat(char *s, char *t, int n)
{
    int i = 0;
    while (*s)                          /* find the end of s */
        s++;
    while ((i++ < n) && (*s++ = *t++))  /* copy up to n chars from t */
        ;
    *s = '\0';                          /* terminate */
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t 
compare up to n chars */
int mstrncmp(char *s, char *t, int n)
{
    int i = 0;
    for ( ; (i++ < n) && (*s == *t); s++, t++) {
        if ((*s == '\0') || (i == n))
            return 0;
    }
    return *s - *t;
}
