#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
#define MAXLINE 1000
#define MAXOP 100
#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000

char *lineptr[MAXLINES];
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int countEscapeSequences();
void shrinkBlanks();
void printEscapeSequences();
void countLineWordChar();
void printOneWordPerLine();
void countCharacters();
void printWordLengthHistogram();
void printCharacterFrequencies();
int power(int base, int n);
void printChars();
int getchars(char line[], int maxline);
void printGt80Chars();
int getlinechar(char line[], int maxline);
void reversePolishCalculator();
void printsortedlines();
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsortchar(char *lineptr[], int left, int right);
char *alloc(int);
void afree(char *);

int main()
{
    //int number = countEscapeSequences();
    //shrinkBlanks();
    //printEscapeSequences();
    //countLineWordChar();
    //printOneWordPerLine();
    //countCharacters();
    //printWordLengthHistogram();
    //printCharacterFrequencies();
    //printChars();
    //printGt80Chars();
    //reversePolishCalculator();
    printsortedlines();
    return 0;
}

/* count blanks, tabs and lines in input */
int countEscapeSequences()
{
    int c, number;
    number = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\t' || c == '\n')
	        ++number;
    printf("%d\n", number);
    return number;
}

/* Replace more than one blanks by single blank */
void shrinkBlanks()
{
    int c, number = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
	        ++number;
        }
        else
        {
	        number = 0;
        }
        if (number <= 1)
        {
	        putchar(c);
        }
    }
}

/* Print tab and backspace */
void printEscapeSequences()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            putchar('\\');
  	        putchar('t');	    
        }
	    else if (c == '\b')
	    {
	        putchar('\\');
	        putchar('b');
	    }
	    else
	    {
	        putchar(c);
	    }
    }
}

/* count lines, words, and characters in input */
void countLineWordChar()
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
	    ++nc;
	    if (c == '\n')
	        ++nl;
	    if (c == ' ' || c == '\n' || c == '\t')
	        state = OUT;
	    else if (state == OUT) {
	        state = IN;
	        ++nw;
	    }
    }
    printf("%d %d %d\n", nl, nw, nc);
}

/* print one word per line */
void printOneWordPerLine()
{
    int c, state;
    state = OUT;
    while ((c = getchar()) != EOF)
    {
	    if (c == ' ' || c == '\n' || c == '\t') {
	        state = OUT;
	        putchar('\n');
        } else if (state == OUT) {
	        state = IN;
	        putchar(c);
	    } else {
	        putchar(c);
	    }
    }
}

/* count digits, white space, others  */
void countCharacters()
{
    int c, i, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
	    ndigit[i] = 0;
    while ((c = getchar()) != EOF)
	    if (c >= '0' && c <= '9')
	        ++ndigit[c - '0'];
    	else if (c == ' ' || c == '\n' || c == '\t')
	        ++nwhite;
    	else 
	        ++nother;
    printf("digits =");
    for (i = 0; i < 10; ++i)
	    printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
}

/* print histogram of the lengths of words */
void printWordLengthHistogram()
{
    int c, i, nc = 0, state = OUT;
    int lengths[10];
    for (i = 0; i < 10; i++)
        lengths[i] = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (nc >= 1 && nc <= 10)
            {
                ++lengths[nc - 1];
                nc = 0;
            }
        }
        else
        {
            nc++;
        }
    }
    for (i = 1; i <= 10; i++)
        printf("%2d ", i);
    printf("\n");
    for (i = 0; i < 10; i++)
        printf("%2d ", lengths[i]);
    printf("\n");
}

/* print histogram of frequencies of different characters */
void printCharacterFrequencies()
{
    int c, i, nc = 0;
    int frequencies[26];
    for (i = 0; i < 26; i++)
        frequencies[i] = 0;
    while ((c = getchar()) != EOF)
    {
        if(c >= 'a' && c <= 'z')
        {
            ++frequencies[c - 'a'];
        }
    }
    for (i = 'a'; i <= 'z'; i++)
        printf("%2c ", i);
    printf("\n");
    for (i = 0; i < 26; i++)
        printf("%2d ", frequencies[i]);
    printf("\n");
}

/* power: raise baee to n-th power; n >= 0; version 2 */
int power(int base, int n)
{
    int p;
    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}

void printChars()
{
    int len;
    int total;
    char chars[MAXLINE];

    len = getchars(chars, MAXLINE);

    if (len > 0) {
        total = len;
        printf("total=%d\n", total);
        printf("chars=\n%s", chars);
    }
}

int getchars(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF; ++i)
        s[i] = c;
    s[i] = '\0';
    return i;
}

void printGt80Chars()
{
    int len;
    char line[MAXLINE];
    while ((len = getlinechar(line, MAXLINE)) > 0)
    {
        if (len > 80)
        {
            printf("char number=%d\n", len);
            printf("chars=%s\n", line);
        }
        else
        {
            printf("less than 80 chars\n");
        }
    }
}

int getlinechar(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = '\n';
        i++;
    }
    s[i] = '\0';
    return i;
}

//void reversePolishCalculator()
//{
//    int type;
//    double op2;
//    char s[MAXOP];
//
//    while ((type = getop(s)) != EOF) {
//        switch (type) {
//            case NUMBER:
//                push(atof(s));
//                break;
//            case '+':
//                push(pop() + pop());
//                break;
//            case '*':
//                push(pop() * pop());
//                break;
//            case '-':
//                op2 = pop();
//                push(pop() - op2);
//                break;
//            case '/':
//                op2 = pop();
//                if (op2 != 0.0)
//                    push(pop() / op2);
//                else
//                    printf("error: zero divisor\n");
//                break;
//            case '\n':
//                printf("\t%.8g\n", pop());
//                break;
//            default:
//                printf("error: unknown command %s\n", s);
//                break;
//        }       
//    }
//}

void printsortedlines()
{
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsortchar(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
    } else {
        printf("error: input too big to sort\n");
    }
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getlinechar(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* qsortchar: sort v[left]...v[right] into increasing order  */
void qsortchar(char *v[], int left, int right)
{
    int i, last;
    void swap(char *[], int i, int j);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsortchar(v, left, last - 1);
    qsortchar(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
