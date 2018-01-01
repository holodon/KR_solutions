/*
Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
each character in s1 that matches any character in the string s2 .
*/
#include <stdio.h>

void squeeze(char s1[], char s2[]);
int hasChar(char s[], char c);

int main(int argc, char* argv[])
{
	if (argc < 3) {
		printf("Usage: %s string1 string2\n", argv[0]);
		return -1;
	}

	squeeze(argv[1], argv[2]);
	printf("%s\n", argv[1]);

	return 0;
}

void squeeze(char s1[], char s2[])
{
	int i, j;
	i = j = 0;
	for (; s1[i] != '\0'; i++)
		if (!hasChar(s2, s1[i]))
			s1[j++] = s1[i];
	s1[j] = '\0';
}

int hasChar(char s[], char c)
{
	int i;
	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			return 1;
	return 0;
}
