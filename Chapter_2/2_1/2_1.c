/*
Exercise 2-1. Write a program to determine the ranges of char , short , int , and long
variables, both signed and unsigned , by printing appropriate values from standard headers
and by direct computation. Harder if you compute them: determine the ranges of the various
floating-point types.

This programm shows three different appproaches to increment the counter: by ++ (char and
unsigned char); by a fixed bigger value (shorts, ints and longs); and by multiplication
by float and doubles.
It can be futher optimized for speed by setting different constants for each type and
experimenting with their values.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#define ADV_S 1000
#define ADV_I 100000
#define ADV_L 100000000000000

int main(void) {
	printf("Values from limits.h:\n");

	printf("max value of char:          %d\n", CHAR_MAX);
	printf("min calue of char:          %d\n", CHAR_MIN);

	printf("max value of int:           %d\n", INT_MAX);
	printf("min value of int:           %d\n", INT_MIN);

	printf("max value of long:          %ld\n", LONG_MAX);
	printf("min value of long:          %ld\n", LONG_MIN);

	printf("max value of signed char:   %d\n", SCHAR_MAX);
	printf("min value of signed char:   %d\n", SCHAR_MIN);

	printf("max value of short:         %d\n", SHRT_MAX);
	printf("min value of short:         %d\n", SHRT_MIN);

	printf("max value of unsigned char: %d\n", UCHAR_MAX);

	printf("max value of unsigned int:  %u\n", UINT_MAX);

	printf("max value of unsigned long: %lu\n\n", ULONG_MAX);

	printf("\n\n");
	printf("Calculations: \n");
	printf("-------------\n\n");


	char done;
	short adv_s;
	int adv_i;
	long adv_l;


	// min/max char:
	char c = 0;
	char last_c;
	while ( !(c < last_c) ) {
		last_c = c;
		c++;
	}
	printf("calculated char max  : %d\n", last_c);
	printf("calculated char min  : %d\n", c);
	printf("limits.h char max    : %d\n", CHAR_MAX);
	printf("limits.h char min    : %d\n\n", CHAR_MIN);

	// min/max unsigned char:
	unsigned char uc = 0;
	unsigned char last_uc;
	while ( !(uc < last_uc) ) {
		last_uc = uc;
		uc++;
	}
	printf("calculated uchar max : %d\n", last_uc);
	printf("calculated uchar min : %d\n", uc);
	printf("limits.h uchar max   : %d\n", UCHAR_MAX);
	printf("expected uchar min   : 0\n\n");

	// min/max short:
	short s = 1;
	short last_s;
	adv_s = ADV_S;
	done = 0;
	while(!done) {
		last_s = s;
		s += adv_s;
		while (s < last_s) {
			adv_s /= 2;
			if (adv_s == 0) {
				done = 1;
				break;
			}
			s = last_s + adv_s;
		}
	}
	printf("calculated short max : %d\n", last_s);
	printf("calculated short min : %d\n", s);
	printf("limits.h short max   : %d\n", SHRT_MAX);
	printf("limits.h short min   : %d\n\n", SHRT_MIN);

	// min/max unsigned short:
	unsigned short us = 1;
	unsigned short last_us;
	adv_s = ADV_S;
	done = 0;
	while(!done) {
		last_us = us;
		us += adv_s;
		while (us < last_us) {
			adv_s /= 2;
			if (adv_s == 0) {
				done = 1;
				break;
			}
			us = last_us + adv_s;
		}
	}
	printf("calculated ushort max: %d\n", last_us);
	printf("calculated ushort min: %d\n", us);
	printf("limits.h ushort max  : %d\n", USHRT_MAX);
	printf("expected ushort min  : 0\n\n");

	// min/max int:
	int i = 1;
	int last_i;
	adv_i = ADV_I;
	done = 0;
	while(!done) {
		last_i = i;
		i += adv_i;
		while (i < last_i) {
			adv_i /= 2;
			if (adv_i == 0) {
				done = 1;
				break;
			}
			i = last_i + adv_i;
		}
	}
	printf("calculated int max   : %d\n", last_i);
	printf("calculated int min   : %d\n", i);
	printf("limits.h int max     : %d\n", INT_MAX);
	printf("limits.h int min     : %d\n\n", INT_MIN);

	// min/max long:
	long l = 1;
	long last_l;
	adv_l = ADV_L;
	done = 0;
	while(!done) {
		last_l = l;
		l += adv_l;
		while (l < last_l) {
			adv_l /= 2;
			if (adv_l == 0) {
				done = 1;
				break;
			}
			l = last_l + adv_l;
		}
	}
	printf("calculated long max  : %ld\n", last_l);
	printf("calculated long min  : %ld\n", l);
	printf("limits.h long max    : %ld\n", LONG_MAX);
	printf("limits.h long min    : %ld\n\n", LONG_MIN);

	// min/max unsigned long:
	unsigned long ul = 1;
	unsigned long last_ul;
	adv_l = ADV_L;
	done = 0;
	while(!done) {
		last_ul = ul;
		ul += adv_l;
		while (ul < last_ul) {
			adv_l /= 2;
			if (adv_l == 0) {
				done = 1;
				break;
			}
			ul = last_ul + adv_l;
		}
	}
	printf("calculated ulong max : %lu\n", last_ul);
	printf("calculated ulong min : %lu\n", ul);
	printf("limits.h ulong max   : %lu\n", ULONG_MAX);
	printf("expected ulong min   : 0\n\n");

	// max float:
	float f = 1.0;
	float last_f;
	float step = 9.0;
	while(1) {
		last_f = f;
		f *= (1.0 + step);
		while (f == INFINITY) {
			step /= 2.0;
			f  = last_f * (1.0 + step);
		}
		if (! (f > last_f) )
			break;
	}
	printf("calculated float max : %e\n", last_f);
	printf("limits.h float max   : %e\n", FLT_MAX);
	printf("diff                 : %e\n", FLT_MAX - last_f);
	printf("The expected value?  : %s\n\n", (FLT_MAX == last_f)? "yes":"no");

	// max double:
	// for this one i used some help with the double precision on my machine:
	// https://stackoverflow.com/a/45824141/6049386
	double d = 1.0;
	double last_d;
	double step_d = 9.0;
	while(1) {
		last_d = d;
		d *= (1.0 + step_d);
		while (d == INFINITY) {
			step_d /= 2.0;
			//d  = last_d * (1.0 + step_d);	// dangerous - not working everywhere
			d = last_d + step_d*last_d;
		}
		if (! (d > last_d) )
			break;
	}
	printf("calculated double max: %e\n", last_d);
	printf("limits.h double max  : %e\n", DBL_MAX);
	printf("diff                 : %e\n", DBL_MAX - last_d);
	printf("The expected value?  : %s\n\n", (DBL_MAX == last_d)? "yes":"no");

	return 0;
}