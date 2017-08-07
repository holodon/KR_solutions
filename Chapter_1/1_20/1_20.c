#include <stdio.h>
//#define n 8	// works too but we prefer variable

int main(void)
{
	int c;
	int col = 0;
	int n = 8;

	while((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			putchar(c);
			col = 0;
		} else if (c == '\t')
		{
			for (int i = 0; i < (n - col); i++)
			{
				putchar(' ');
				//putchar('_');	// better visibility
			}
			col = 0;
		} else
		{
			putchar(c);
			col++;
			if (col == n)
			{
				col = 0;
			}
		}
	}
	return 0;
}
