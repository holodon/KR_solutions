#include <stdio.h>

int main(void)
{
	int c;

	while((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			//printf("    ");
			printf("____");	// better visibility
		} else
		{
			putchar(c);
		}
	}
	return 0;
}
