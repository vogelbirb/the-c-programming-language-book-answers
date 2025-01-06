#include <stdio.h>
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    void *pval;
    int ival;
    double dval;
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'i':
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'o':
            ival = va_arg(ap, unsigned);
            printf("%o", ival);
            break;
        case 'x':
            ival = va_arg(ap, unsigned);
            printf("%x", ival);
            break;
        case 'X':
            ival = va_arg(ap, unsigned);
            printf("%X", ival);
            break;
        case 'u':
            ival = va_arg(ap, unsigned);
            printf("%u", ival);
            break;
        case 'c':
            ival = va_arg(ap, int);
            printf("%c", ival);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'e':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'E':
            dval = va_arg(ap, double);
            printf("%E", dval);
            break;
        case 'g':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case 'G':
            dval = va_arg(ap, double);
            printf("%G", dval);
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        case '%':
            printf("%%");
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* clean up when done */
}

int main(void) {
    minprintf("%% hello world %p\n", "hello");
    
    return 0;
}