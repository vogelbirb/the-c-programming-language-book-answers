#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

enum VarMode {
    READ,
    WRITE,
};

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char s[]);
double peek(void);
void duplicate(void);
void swap(void);
void clear(void);

/* reverse Polish calculator */
int main() {
    int type;
    double op2, op1;
    char s[MAXOP];
    // 0-25 represent A-Z
    // Could be a hashmap, but not there yet
    double vars[26] = {0};
    enum VarMode var_mode = READ;
    int var = 'A';
    
    double most_recent = 0.0;
    

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                if (var == READ) {
                    vars[var] = peek();
                }
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if (op2 == 0.0) {
                    printf("error: zero divisor\n");
                } else if (op1 < 0 || op2 < 0) {
                    printf("error: negative operand\n");
                } else {
                    push((int)op1 % (int)op2);
                }
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
                break;
            case 'n':
                push(sin(pop()));
                break;
            case 'o':
                push(cos(pop()));
                break;
            case 'x':
                push(exp(pop()));
                break;
            case '^':
                op2 = pop();
                op1 = pop();
                if (op1 == 0.0 || op2 <= 0 || (op1 < 0 && op2 != (float)((int)op2))) {
                    printf("error: domain error\n");
                } else {
                    push(pow(op1, op2));
                }
                break;
            case '\n':
                printf("\t%.8g\n", peek());
                most_recent = peek();
                break;
            case 'w':
                var_mode = WRITE;
                break;
            case '&':
                printf("\t%.8g\n", most_recent);
                break;
            default:
                if (isupper(type)) {
                    var_mode = READ;
                    var = type - 'A';
                    if (var_mode == READ) {
                        push(vars[var]);
                    }
                } else {
                    printf("error: unknown command %s\n", s);
                }
                break;
        }
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double peek(void) {
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
    
}

void duplicate(void) {
    if (sp > 0) {
        val[sp++] = val[sp - 1];
    }
    else {
        printf("error: stack empty\n");
    }
}

void swap(void) {
    double temp;
    if (sp > 0) {
        temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    }
    else {
        printf("error: stack empty\n");
    }
    
}

void clear(void) {
    sp = 0;
}


/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;
    static int ungetched_c = -1;

    bool should_ungetch = ungetched_c >= 0;
    while ((s[0] = c = should_ungetch ? ungetched_c : getch()) == ' ' || c == '\t') {
        should_ungetch = should_ungetch ? false : should_ungetch; 
    }
    
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c; /* not a number */
    }
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
        ;
    s[i] = '\0';
    if (c != EOF)
        ungetched_c = c;
    return NUMBER;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[]) {
    for (int i = strlen(s) - 1; i >= 0; i--) {
        // ungetch is better because of the error handling it already has
        ungetch(s[i]);
    }
}