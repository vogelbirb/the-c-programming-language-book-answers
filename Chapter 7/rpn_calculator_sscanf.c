#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

enum VarMode {
    READ,
    WRITE,
};

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXLINE 100

int _getline(char s[], int limit);
int getop(char []);
void push(double);
double pop(void);
double peek(void);
void duplicate(void);
void swap(void);
void clear(void);
void disp_array(char arr[], int len);

char line[MAXLINE];
int ptr = 0;

/* reverse Polish calculator */
int main() {
    int type;
    double op2, op1;
    char s[MAXOP] = {0};
    // 0-25 represent A-Z
    // Could be a hashmap, but not there yet
    double vars[26] = {0};
    enum VarMode var_mode = READ;
    int var = 'A';
    
    double most_recent = 0.0;
    
    while (_getline(line, MAXLINE) != EOF) {
        ptr = 0;
        while ((type = getop(s)) != '\0') {
            switch (type) {
                case NUMBER: {
                    double n;
                    sscanf(s, "%lf", &n);
                    push(n);
                    if (var == READ) {
                        vars[var] = peek();
                    }
                    break;
                }
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
                {
                    // so the error message only appears once, I'm too lazy
                    double top = peek();
                    printf("\t%.8g\n", top);
                    most_recent = top; 
                    break;
                }
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
    else {
        printf("error: stack full, can't push %g\n", f);
    }
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
        sp++;
        val[sp] = val[sp - 2];
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
    while ((s[0] = c = line[ptr++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */
    i = 0;
    /* collect integer part */
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[ptr++]))
            ;
    }
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[ptr++]))
        ;
    s[i] = '\0';
    if (c != EOF)
        ptr--;
    return NUMBER;
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
        s[i++] = c;
    }
    s[i] = '\0';
    return (c == EOF) ? EOF : i;
}
void disp_array(char arr[], int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%c", i > 0 ? ", " : "", arr[i]);
    }
    printf("]\n");
}