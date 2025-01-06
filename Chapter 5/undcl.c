#include "common.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

/* dcl: parse a declarator */
int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

int gettoken(void) /* return next token */
{
  int c, getch(void);
  void ungetch(int);
  char *p = token;
  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

// Exercise 5-19: put parenthesis before * to parenthesize it

/* undcl: convert word descriptions to declarations */
int main() {
  int type;
  char temp[MAXTOKEN];
  bool prev_paren = false;

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
          strcat(out, token);
          prev_paren = prev_paren ? false : true;
      }
      else if (type == '*') {
        if (prev_paren) {
          prev_paren = false;
          // Crop off parenthesis that were added before
          out[strlen(out) - 2] = '\0';
          sprintf(temp, "(*%s)", out);
        } else {
          sprintf(temp, "*%s", out);
        }
        
        strcpy(out, temp);
        
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else {
        printf("invalid input at %s\n", token);
      }

    }
    printf("%s\n", temp);
  }
  return 0;
}