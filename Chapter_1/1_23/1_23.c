/*
Exercise 1-23. Write a program to remove all comments from a C program. Don't
forget to handle quoted strings and character constants properly. C comments
don't nest.

- Ignoring the compiler warning about "comments within comments" and unused
	"test" variable - all this is on purpose.
 */

#include <stdio.h>

int main(void)
{
	// used to test this program against its own source
	char test[] = "test/* my simple test */";

	int state = 0;		/* states:
							0 - none;

						single row comment:
							1 - "/"; 2 - "//"

						multi-line comment:
							3 - "/*"; 4 - "/* .. *"
						*/
	int c = 0;
	int sQuotes = 0;				// single quotes
	int dQuotes = 0;				// double quotes
	int skipping = 0;				// skipping modus (comment body)
	int special = 0;				// backslash

	while((c = getchar()) != EOF) {

		if (!skipping)  {
			if (special) {						// backslash
				putchar(c);
				special = 0;
				continue;
			}

			if (c == '\\') {					// char after backslash
				putchar(c);
				special = 1;
				continue;
			}

			if (c == '"' && !sQuotes)			// double quote
				dQuotes = (dQuotes == 0)? 1:0;
			else if (c == '\'' && !dQuotes)		// single quote
				sQuotes = (sQuotes == 0)? 1:0;

			if (sQuotes || dQuotes) {
				putchar(c);
				continue;
			}
		}

		switch (state) {
			case 0:					// no state
				if (c == '/')
					state = 1;
				else
					putchar(c);
				break;

			case 1:					// "/" state
				if (c == '/') {
					skipping = 1;
					state = 2;
				}
				else if (c == '*') {
					skipping = 1;
					state = 3;
				} else {
					putchar('/');	// corner case
					putchar(c);
					skipping = 0;
					state = 0;
				}
				break;

			case 2:
				if (c == '\n') {	// end of line comment
					putchar('\n');
					skipping = 0;
					state = 0;
				} else {
					;				// or continue skipping
				}
				break;

			case 3:					// "/*" state
				if (c == '*') {
					state = 4;
				} else {
					;				// or continue skipping
				}
				break;

			case 4:					// "/* .. *"
				if (c == '/') {		// end of multiline comment
					skipping = 0;
					state = 0;
				} else {
					state = 3;		// or continue skipping
				}
				break;

		}

	}


	return 0;
}
