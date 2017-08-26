/*
Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1
*/

#include <stdio.h>

int main(void) {
	int c;
	int b;

	while (1) {
		c = getchar();
		b = (c != EOF);
		printf("%d\n",b);
		/* it prints twice the 1's because the input is like:
		 * (char + newline) */

		if (c == EOF) {
			break;
		}
	}
}
