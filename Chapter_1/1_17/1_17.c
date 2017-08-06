#include <stdio.h>
#define MAXLINE 10 /* maximum input line length
						reduced to 10 for testing purposes */

int getLine(char s[], int lim);

/* print the lines bigger than some value */
int main(void)
{
	int len;	/* current line length */
	int moreThan;	/* minimum length to print */
	char line[MAXLINE];	/* current input line */

	moreThan = 5;	/* easier to test than with 80 */
	while ((len = getLine(line, MAXLINE)) > 0)
	{
		if (len > moreThan)
		{
			printf("%s\n",line);
		}
	}
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
