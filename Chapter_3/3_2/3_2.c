/*
Exercise 3-2. Write a function escape(s,t) that converts characters like 
newline and tab into visible escape sequences like \n and \t as it copies the 
string t to s . Use a switch . Write a function for the other direction as 
well, converting escape sequences into the real characters.
*/

#include <stdio.h>
#define MAX 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);


int main(void)
{
    int i = 0;
    char s[MAX];
    char t[MAX];

    while((s[i] = getchar()) != EOF && i < MAX)
        i++;

    s[i] = '\0';

    escape(s, t);
    printf("%s", t);
    printf("\n\n");
    unescape(s, t);
    printf("%s", s);

    return 0;
}


void escape(char s[], char t[])
{
    int i, j;
    i = j = 0;
    while(s[i]) {
        switch(s[i]) {
            case '\n':
                if (j + 2 == MAX)
                    break;
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                if (j + 2 == MAX)
                    break;
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
                break;
        }
        i++;
        if (j == MAX) {
            t[j - 1] = '\0';
            break;
        }
    }
}


void unescape(char s[], char t[])
{
    int i, j;
    int inSeq = 0;  // watcher for '\'
    i = j = 0;
    while(t[i]) {
        switch(t[i]) {
            case '\\':
                if (inSeq)
                    s[j++] = '\\';
                else
                    inSeq = 1;
                break;
            case 'n':
                if (inSeq) {
                    inSeq = 0;
                    s[j++] = '\n';
                } else
                    s[j++] = 'n';
                break;
            case 't':
                if (inSeq) {
                    inSeq = 0;
                    s[j++] = '\t';
                } else
                    s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
        i++;
    }
}
