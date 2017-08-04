#include <stdio.h>
/* copy input to output; 2nd version  */
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
