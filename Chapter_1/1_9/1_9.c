#include <stdio.h>

int main(void) {
	int c;
	int blank = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (!blank) {
				putchar(c);
				blank = 1;
			}
		} else {
			putchar(c);
			blank = 0;
		}
	}
	printf("\n");
}