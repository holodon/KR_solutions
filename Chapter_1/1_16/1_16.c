#include <stdio.h>
#define MAXLINE 10 /* maximum input line length
						reduced to 10 for testing purposes */

int getLine(char s[], int lim);
void copy(char to[], char from[]);

/* print the longest input */
int main(void)
{
	int len;	/* current line length */
	int max;	/* maximum length seen so far */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */

	max = 0;
	while ((len = getLine(line, MAXLINE)) > 0)
	{
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	printf("Longest line was: %d characters\n",max);
	if (max > 0)	/* there was a line */
	{
		printf("%s", longest);
	}
	printf("\n");
	return 0;
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim)
{
	int c, i;
	for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
	{
		if (i < lim-1)
		{
			s[i] = c;
		}
	}
	if (i >= lim)
	{
		s[lim] = '\0';
		return i;
	}
	if (c == '\n')
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}
/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
	{
		i++;
	}
}