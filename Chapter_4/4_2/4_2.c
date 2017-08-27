/*
Exercise 4-2. Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally 
signed exponent.
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>

double atof(char s[]);


int main(void)
{
    char s[] = "  -100.312e-16 ";
    double res = atof(s);
    printf("%e\n", res);
    return 0;
}


/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;
    int expsign = 1;
    int expval = 0;

    for (i = 0; isspace(s[i]); i++)
       ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i++] == '-')
            expsign = -1;
        for (expval = 0; isdigit(s[i]); i++)
            expval = 10 * expval + (s[i] - '0');
    }
    return (sign * val / power) * pow(10.0, (double) expsign * expval);
}
