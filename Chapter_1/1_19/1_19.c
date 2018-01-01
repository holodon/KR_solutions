/*
Exercise 1-19. Write a function reverse(s) that reverses
the character string s . Use it to write a program that
reverses its input a line at a time.
*/

#include <stdio.h>

#define MAXLINE 1000

void reverse(char s[], char out[], int len);
int getLine(char s[], int lim);

/* reads the input and reverse the lines one by one
	leaving the '\n' at the end */
int main(void)
{
	char s[MAXLINE]; 	// string buffer
	char out[MAXLINE]; 	// string buffer

	int len;
	while ((len = getLine(s,MAXLINE)) > 0)
	{
		reverse(s, out, len);
		printf("%s", out);
	}

	return 0;
}

/* reverse a string
	preserving the '\n' at the end */
void reverse(char s[], char out[], int len) {
	int nl = 0;
	if (s[len - 1] == '\n') {
		nl = 1;
	}
	for (int i = 0; i < len - nl; i++)
	{
		out[i] = s[len - i - 1 - nl];
	}
	if (nl)
	{
		out[len - 1] = '\n';
	}
	out[len] = '\0';
}

/* read a line, return its length */
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
