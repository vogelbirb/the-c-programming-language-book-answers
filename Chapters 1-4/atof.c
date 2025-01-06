#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define LINE_LEN 100

double atof(char s[]);
int _getline(char s[], int limit);

int main() {
    char line[] = "";
    _getline(line, LINE_LEN);
    printf("%.4f\n", atof(line));
    return 0;
}

int _getline(char s[], int limit) {
    int c = '\0', i = 0;
    
    for (;(c = getchar()) != EOF && c != '\n'; i++) {
        // Fix to allow long lines to be counted correctly
        if (i < limit - 1) {
            s[i] = c;
        }
    }
    if (c == '\n') {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++) /* skip white space */
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
    }
    int exponent = 0;
    int exponent_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (;isdigit(s[i]); i++) {
        exponent = 10.0 * exponent + (s[i] - '0');
    }
    printf("exponent %i\n", exponent);

    return (sign * val / power) * pow(10, exponent * exponent_sign);
}
