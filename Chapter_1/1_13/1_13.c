/*
Exercise 1-13. Write a program to print a histogram of the lengths of 
words in its input. It is easy to draw the histogram with the bars
horizontal; a vertical orientation is more challenging.
*/

#include <stdio.h>

#define MAX 11
#define TRUE 1
#define FALSE 0
int lengths[MAX];	// we ignore lengths[0] so max length is MAX-1
int currWordLen = 0;

void update();

/* outputs a hystogram of the input words length;
	words with length > MAX gets showed as length MAX
	test file included:
	cat test | ./a.out */
int main(void) {
	int c;
	int inword = FALSE;

	while ((c = getchar()) != EOF) {

		// not-char
		if (c <= ' ' || c > '~') {
			if (inword) {
				update();
			}
			inword = FALSE;

		// char
		} else {
			inword = TRUE;
			currWordLen++;
		}
	}
	if (currWordLen > 0) {
		update();
	}
	
	printf("\n");

// vertical output version

	int biggest = 0;
	for (int i = 1; i < MAX; i++) {
		if (lengths[i] > biggest) {
			biggest = lengths[i];
		}
	}

	for (int i = biggest; i > 0; i--) {
		for (int k = 1; k < MAX; k++) {
			if (lengths[k] >= i) {
				printf(" o ");
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}

	for (int i = 1; i < MAX; i++) {
		printf("---");
	}
	printf("\n");
	for (int i = 1; i < MAX; i++) {
		printf("%2d ",i);
	}

	printf("\n");

// horizontal output version	
/*
	for (int i = 1; i < MAX; i++) {
		printf("%2d:",i);
		for (int k = 0; k < lengths[i]; k++) 
		{
			printf("-");
		}
		printf("\n");
	}
*/
	return 0;
}

void update() {
	if (currWordLen > (MAX-2)) {
		lengths[MAX-1]++;
	} else {
		lengths[currWordLen]++;
	}
	currWordLen = 0;
}

