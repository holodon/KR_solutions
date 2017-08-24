/*
Exercise 2-5. Write the function any(s1,s2) , which returns the first location in a string s1
where any character from the string s2 occurs, or -1 if s1 contains no characters from s2 .
*/
#include <stdio.h>

int any(char s1[], char s2[]);
int hasChar(char s[], char c);

int main(int argc, char* argv[]) 
{
	if (argc < 3) {
		printf("Usage: %s string1 string2\n", argv[0]);
		return -1;
	}

	printf("%d\n", any(argv[1], argv[2]));

	return 0;
}

int any(char s1[], char s2[])
{
	int i = 0;
	for (; s1[i] != '\0'; i++)
		if (hasChar(s2, s1[i]))
			return i;
	return -1;
}

int hasChar(char s[], char c)
{
	int i = 0;
	while(s[i] != '\0')
		if (s[i++] == c)
			return 1;
	return 0;
}
