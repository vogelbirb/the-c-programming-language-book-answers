#include <stdarg.h>
#include <stdio.h>

#define MAXLINE 100

void minscanf(char *fmt, ...) {
    va_list ap;
    
    void *val;

    va_start(ap, fmt);

    for (char *p = fmt; *p; p++) {
        if (*p != '%') {
            if (!(getchar() == *p)) {
                break;
            }
            continue;
        } else {
            switch (*++p) {
            // Not sure if d and i are the same like in printf, others too
            case 'd':
                val = va_arg(ap, int *);
                scanf("%d", (int *)val);
                break;
            case 'i':
                val = va_arg(ap, int *);
                scanf("%i", (int *)val);
                break;
            case 'o':
                val = va_arg(ap, int* );
                scanf("%o", (int *)val);
                break;
            case 'u':
                val = va_arg(ap, unsigned int *);
                scanf("%u", (unsigned int *)val);
                break;
            case 'x':
                val = va_arg(ap, int *);
                scanf("%x", (int *)val);
                break;
            case 'c':
                val = va_arg(ap, char *);
                scanf("%c", (char *)val);
                break;
            case 's':
                val = va_arg(ap, char *);
                scanf("%s", (char *)val);
                break;
            case 'e':
                val = va_arg(ap, float *);
                scanf("%e", (float *)val);
                break;
            case 'f':
                val = va_arg(ap, float *);
                scanf("%f", (float *)val);
                break;
            case 'g':
                val = va_arg(ap, float *);
                scanf("%g", (float *)val);
                break;
            case '%':
                scanf("%%");
                break;
            }
        }
    }
    va_end(ap);
}

int main(void) {
    int n = 0;
    float f = 0.0;
    minscanf("%iff%f", &n, &f);
    printf("n = %i\n", n);
    printf("f = %f\n", f);
    return 0;
}