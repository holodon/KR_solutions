/*
Exercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit table.
*/

#include <stdio.h>
/* print Celsius-Fahrenheit table */
int main(void) {
	float fahr, celsius;
	float lower, upper, step;
	lower = -20;
	upper = 150;
	step = 10;
	/* lower limit of temperatuire scale */
	/* upper limit */
	/* step size */
	celsius = lower;
	printf(" C:   F:\n");
	printf("________\n");
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%4.0f %3.0f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
