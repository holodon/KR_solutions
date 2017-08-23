/*
	for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
Exercise 2-2. Write a loop equivalent to the for loop above without using && or || .
*/
#include <stdio.h>
#define MAXLINE 1000

int mgetline(char s[], int lim);

int main(void)
{
	int lim = 10;
	char c[MAXLINE];
	while (mgetline(c, lim) > 0)
		printf("%s\n",c);
	return 0;
}

int mgetline(char s[],int lim)
{
	int c, i;
	for (i=0; i < lim-1; ++i) {
		c = getchar();
		if (c != '\n')
			if (c != EOF)
				s[i] = c;
			else
				break;
		else
			break;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}