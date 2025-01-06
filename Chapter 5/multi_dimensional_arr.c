#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXLINE 100
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
    else
    buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch())) /* skip white space */
    ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    // LOL 
    if (year < 0) {
        return -1;
    }
    if (month > 12 || month < 1) {
        return -1;
    } 
    if (day < 1) {
        return - 1;
    }
    if (month % 2 == 0 && day > 31) {
        return -1;
    }
    if (month % 2 != 0 && day > 30 && month != 2) {
        return -1;
    }
    if (month == 2 && leap && day > 29) {
        return -1;
    }
    if (month == 2 && !leap && day > 28) {
        return -1;
    }
    
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    if (yearday < 1 || year < 0) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    if ((leap && yearday > 366) || (!leap && yearday > 365)) {
        *pmonth = -1;
        *pday = -1;
        return;        
    }

    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

int main(void) {
    // 0 = from day of year
    // 1 = from month and day
    printf("modes: 0 to enter day of year and year, 1 to enter year, month, and day\n");
    bool conversion = '0' - getchar();
    // skips \n
    getchar();

    int day = 0;
    int month = 0;
    int year = 0;

    if (conversion) {
        printf("year: ");
        getint(&year);
        printf("month: ");
        getint(&month);
        printf("day: ");
        getint(&day);
        printf("year day: %i\n", day_of_year(year, month, day));
    } else {
        printf("year: ");
        getint(&year);
        printf("day: ");
        getint(&day);
        month_day(year, day, &month, &day);
        printf("month: %i, day: %i\n", month, day); 
    }
}