/*
Exercise 1-14. Write a program to print a histogram of the
frequencies of different characters in its input.
*/

#include <stdio.h>
#include <ctype.h>

void show(int array[], int size, int shift);

int main(void) {
	int c;
	int cl;
	int allChars = 25;
	int chars[allChars];
	int allInts = 10;
	int ints[allInts];
	int blanks = 0;
	int nls = 0;
	int tabs = 0;
	int rest = 0;

	for (int i = 0;  i < allChars; i++) {
		chars[i] = 0;
	}
	for (int i = 0; i < allInts; i++){
		ints[i] = 0;
	}

	while((c = getchar()) != EOF) {
		// chars:
		// 'a' = 97
		// 'z' = 122
		cl = tolower(c);
		if (cl >= 'a' &&  cl <= 'z') {
			chars[cl - 'a']++;
		}
		// ints:
		// '0' = 48
		// '9' = 57
		else if (cl >= '0' && cl <= '9') {
			ints[cl - '0']++;
		}
		// spaces
		else if (cl == ' ') {
			blanks++;
		}
		// newlines
		else if (cl == '\n') {
			nls++;
		}
		// tabs
		else if (cl == '\t') {
			tabs++;
		}
		// everything else
		else {
			rest++;
		}
	}

	printf("\n\n");
	printf("Frequencies: \n");
	printf("------------\n");

	printf("Chars (ignoring case):\n");
	show(chars, allChars, 'a');

	printf("Ints:\n");
	show(ints, allInts, '0');

	printf("Spaces: %d\n", blanks);
	printf("Tabs: %d\n",tabs);
	printf("Newlines: %d\n", nls);
	printf("Other: %d\n",rest);

	printf("------------\n");
	printf("\nDone!\n");

	return 0;
}

void show(int arr[], int size, int shift) {
	int empty = 1;

	for (int i = 0; i < size; i++) {
		if (arr[i] != 0) {
			empty = 0;
			printf("%c: %d\n",i + shift,arr[i]);
		}
	}

	if (empty) {
		printf("none\n");
	}
	printf("\n");
}
