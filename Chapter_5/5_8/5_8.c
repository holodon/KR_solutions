/*
Exercise 5-8. There is no error checking in day_of_year or month_day.
Remedy this defect.
*/

#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);
int isleap(int year);
int check_year(int year);
int check_yd(int year, int yearday);
int check_ymd(int year, int month, int day);


int main(void)
{
    printf("\n");
    int month, day, res, y, m, d, yd;

    y = 1988;
    m = 2;
    d = 29;
    res = day_of_year(y, m, d);

    if (res == -1) {
        printf("invalid input\n");
    } else
        printf("date %i %i %i  : day %i\n", y, m, d, res);


    y = 1988;
    yd = 60;
    res = month_day(y, yd, &month, &day);

    if (res == -1) {
        printf("invalid input\n");
    } else
        printf("day %i from %i: month %i day %i\n", yd, y, month, day);

    printf("\n");
    return 0;
}

static char daytab[2][13] = {
    /* start with 0 because Januar is 1 */
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    if (!check_ymd(year, month, day))
        return -1;

    int i, leap;
    /* every 4th year is a leap year (except the 100th); every 400th also */
    leap = isleap(year);
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    if (!check_yd(year, yearday))
        return -1;

    int i, leap;
    leap = isleap(year);
    for (i = 1; yearday > daytab[leap][i]; i++)
       yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;

    return 0;
}

/* check if year is leap */
int isleap(int year)
{
    /* every 4th year is a leap year (except the 100th); every 400th also */
    return ( ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0) );
}

/* check if year is valid year */
int check_year(int year)
{
    /* arbitrary limits for the sake of the excersice */
    return (1900 < year) && (year < 2100);
}

/* check if year and yearday are valid */
int check_yd(int year, int yearday)
{
    return
        check_year(year) &&
        (1 <= yearday) &&
        (yearday <= (isleap(year)? 366:365));
}

/* check if year, month and day are valid */
int check_ymd(int year, int month, int day)
{
    return
        check_year(year) &&
        (1 <= month) && (month <= 12) &&
        (1 <= day) && (day <= daytab[isleap(year)][month]);
}
