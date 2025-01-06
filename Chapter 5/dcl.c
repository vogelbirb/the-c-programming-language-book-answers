#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
void dirdcl(void);
void dcl(void);

/* dcl: parse a declarator */
int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];
char error[100] = {0};

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

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
  int type;
  if (tokentype == '(') { /* ( dcl ) */
    dcl();
    if (tokentype != ')') {
      strcpy(error, "error: missing )\n");
    }
  } else if (tokentype == NAME) /* variable name */
    strcpy(name, token);
  else {
    strcpy(error, "error: expected name or (dcl)\n");
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

/* dcl: parse a declarator */
void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

int main(void) /* convert declaration to words */
{
  while (gettoken() != EOF) { /* 1st token on line */
    strcpy(datatype, token);  /* is the datatype */
    out[0] = '\0';
    dcl(); /* parse rest of line */
    if (tokentype != '\n') {
      strcpy(error, "syntax error\n");
    }
    if (error[0] == '\0') {
      printf("%s: %s %s\n", name, out, datatype);
    }
    if (tokentype == '\n' && error[0] != '\0') {
      printf("%s", error[0] == '\0' ? "(none)\n" : error);
      error[0] = '\0';
    }
  }
    
  return 0;
}