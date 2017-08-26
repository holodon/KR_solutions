/*
Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations 
like a-z in the string s1 into the equivalent complete list abc...xyz in s2 . 
Allow for letters of either case and digits, and be prepared to handle cases 
like a-b-c and a-z0-9 and -a-z . Arrange that a leading or trailing - is 
taken literally.
*/

#include <stdio.h>
#include <ctype.h>
#define MAX 1000

void expand(char s1[], char s2[]);


int main(void)
{
    int i = 0;
    char s1[MAX];
    char s2[MAX];

    while ((s1[i] = getchar()) != EOF && i < MAX)
        i++;

    s1[i] = '\0';

    expand(s1, s2);
    printf("%s\n", s2);

    return 0;
}


void expand(char s1[], char s2[])
{
    int i, j, k, c;
    i = j = k = 0;
    int inSeqNum = 0;       // digit followed by '-'
    int inSeqCh = 0;        // char followed by '-'
    int last;               // last seen char/digit

    while (s1[i]) {
        if (inSeqNum) {
            inSeqNum = 0;
            if ( isdigit(s1[i]) && (last < s1[i]) ) {
                for (k = last + 1; k <= s1[i]; k++)
                    s2[j++] = k;
                last = -1;
            } else {
                if (j + 3 >= MAX) {
                    s2[j] = '\0';
                    return;
                }
                s2[j++] = '-';
                s2[j++] = s1[i];
                last = s1[i];
            }
        } else if (inSeqCh) {
            inSeqCh = 0;
            k = tolower(last);
            c = tolower(s1[i]);
            if ( isalpha(s1[i]) && (k<c) ) {
                for (k++; k < c; k++)
                    s2[j++] = k;
                s2[j++] = s1[i];
                last = -1;
            } else {
                if (j + 3 >= MAX) {
                    s2[j] = '\0';
                    return;
                }
                s2[j++] = '-';
                s2[j++] = s1[i];
                last = s1[i];
            }
        } else if (s1[i] == '-') {
            if (isdigit(last))
                inSeqNum = 1;
            else if (isalpha(last))
                inSeqCh = 1;
            else
                s2[j++] = '-';
        } else {
            last = s1[i];
            s2[j++] = s1[i];
        }

        i++;
    }

    if (inSeqCh || inSeqNum) {
        if (j + 2 >= MAX) {
            s2[j] = '\0';
            return;
        }
        s2[j++] = last;
        s2[j++] = '-';
    }

    if (j == MAX) {
        s2[j - 1] = '\0';
        return;
    }
    s2[j] = '\0';

}
