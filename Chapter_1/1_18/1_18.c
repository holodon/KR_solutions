/*
Exercise 1-18. Write a program to remove trailing blanks
and tabs from each line of input, and to delete entirely 
blank lines.
*/

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */
#define FALSE 0
#define TRUE 1

int getLine(char s[], int lim);
int strip(char s[], int len);

/* remove trail spaces and tabs
	remove blank lines */
int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */

	while ((len = getLine(line, MAXLINE)) > 0)
	{
		if (strip(line,len))
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
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
	{
		s[i] = c;
	}
	if (c == '\n')
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}

/* strips all spaces, tabs and more than one '\n' 
 from the end of the string */
int strip(char s[], int len)
{
	if (len == 1 && s[0] == '\n')
	{
		return 0;
	}
	int nlFound = FALSE;
	for (int i = len-1; i >= 0; i--) {
		if (s[i] != ' ' && s[i] != '\t')
		{
			if (s[i] == '\n') 
			{
				nlFound = TRUE;
			} else
			{
				if (nlFound)
				{
					s[i+2] = '\n';
				}
				s[i+1] = '\0';	// terminate string
				return 1;
			}
		}
	}
	return 0;	// the whole string is tabs, spaces and '\n'
}