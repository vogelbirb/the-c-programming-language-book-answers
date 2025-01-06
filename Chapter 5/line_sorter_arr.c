#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

size_t _getline(char *s, const int lim) {
    size_t count = 0;
    while ((*s = getchar()) != EOF && *s != '\n' && count < lim - 2) {
        count++;
        s++;
    }
    if (*s =='\n') {
        *s++ = '\n';
        count++;
    }
    *s = '\0';
    return count;
}

#define MAXLEN 1000 /* max length of any input line */
/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *linebuff)
{
    size_t len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = linebuff) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            linebuff += len;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

#define BUFF_LEN 500
int main(void) {
   char *lineptr[MAXLINES]; /* pointers to text lines */
   int nlines; /* number of input lines read */
   
   // Not sure how much faster this is
   char linebuff[BUFF_LEN] = {0};

   if ((nlines = readlines(lineptr, MAXLINES, linebuff)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    } 
    return 0;
}