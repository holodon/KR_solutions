#include <stdio.h>
/* print Fahrenheit-Celsius table */
int main(void) {
	float fahr, celsius;
	float lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	/* lower limit of temperatuire scale */
	/* upper limit */
	/* step size */
	printf("F:   C:\n");
	printf("__________\n");
	for (fahr = upper; fahr >= lower; fahr = fahr - step) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f %6.1f\n", fahr, celsius);
	} 
}
