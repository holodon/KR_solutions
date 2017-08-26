/*
Exercise 3-1. Our binary search makes two tests inside the loop,
when one would suffice (at the price of more tests outside.) 
Write a version with only one test inside the loop and measure
the difference in run-time.
*/

#include <stdio.h>

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main(void)
{
	int x = -1;
	int max = 10000;
	int arr[max];
	int i,k;

	for (i = 0; i < max; i++)
		arr[i] = i*2;

	printf("Position: %d\n", binsearch2(x, arr, max));

	for (i = 0; i < 10000; i++)
		for (k = 0; k < 10000; k++)
			// change below to test runtime
			binsearch2(x, arr, max);

	return 0;
}

int binsearch(int x, int v[], int n) {
    int low, mid, high;
    
    low = 0;
    high = n - 1;
    while ( low <= high ) {
        mid = (low+high) / 2;
        if ( x < v[mid] )
            high = mid - 1;
        else if ( x > v[mid] )
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

// if the value is in the array, then btnsearch is quicker,
// otherwise both are similar
int binsearch2(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;

	mid = (low + high)/2;

	while (low <= high) {

		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;

		mid = (low+high)/2;
	}

	return (v[mid] == x)? mid: -1;
}
