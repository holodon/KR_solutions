/*
Exercise 1.15. Rewrite the temperature conversion program 
of Section 1.2 to use a function for conversion.
*/

#include <stdio.h>
/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floating-point version */

float toCelsius(float fahr);

int main(void) {
	float fahr, celsius;
	float lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	/* lower limit of temperatuire scale */
	/* upper limit */
	/* step size */
	fahr = lower;
	printf("F:   C:\n");
	printf("__________\n");
	while (fahr <= upper) {
		printf("%3.0f %6.1f\n", fahr, toCelsius(fahr));
		fahr = fahr + step;
	}
}

float toCelsius(float fahr) {
	return ((5.0/9.0) * (fahr-32.0));
}
