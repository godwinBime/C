#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFFSIZE 100
#define ALLOCSIZE 1000 //size of available space
#define MAXLINES 5000 //max # of lines to be sorted
#define MAXLEN 1000 //ma length of any input line

enum {NAME, PARENS, BRACKETS};

char buf[BUFFSIZE]; //buffer for ungetch
int bufp = 0; //next free position in buf
static char allocBuf[ALLOCSIZE]; //storage for alloc
static char* allocp = allocBuf; //next free position
char* linePtr[MAXLINES]; //pointers to text lines
int leapYear(int year);
int numCmp(char* s1, char* s2);

int getch(void);
void unGetch(int);
int readLines(char* linePtr[], int nLines);
void writeLines(char* linePtr[], int nLines);
void qSort(char* linePtr[], int left, int right);
int getLine(char*, int);
char* alloc(int);
void swap(char* v[], int i, int j);
int dayOfYear(int year, int month, int day);
char* monthName(int n);

//Swap copies of values
//swap: swap value of a with value of b
void swap(int a, int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//Interchange values
//interchange: change the value of a with the value of b
void interChange(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//getInt: get next integer from input into *pn
int getInt(int* pn) {
	int c, sign;
	whhile(isspace(c = getch()))//skip white space
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		unGetch(c);//it's not a number
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		unGetch(c);
	return c;
}

/*get a (possibly pushed back) character*/
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}


/*push characters back on input*/
void ungetch(int c) {
	if (bufp >= BUFFSIZE)
		printf("ungetch: too many characters...\n");
	else
		buf[bufp++] = c;
}

//strlen: return length of string s
int strlen(char* s) {
	int n;
	for (n = 0; *s != '\0'; s++) {
		n++;
	}
	return n;
}

//another version of strlen
//strlen: return length of string s
int strlen(char* s) {
	char* p = s;
	while (*p != '\0')
		p++;
	return p - s;
}

/*Return pointer to n characters*/
char* alloc(int n) {
	if (allocBuf + ALLOCSIZE - allocp >= n) {//iy fits
		allocp += n;
		return allocp - n;//old p
	}else{
		return 0; //not enough room
	}
}

//free storage pointed to by p
void afree(char* p) {
	if (p >= allocBuf && p < allocBuf + ALLOCSIZE) {
		allocp = p;
	}
}

//strcpyA: copy t to s: array subscript version
void strcpyA(char* s, char* t) {
	int i = 0;
	while ((s[i] = t[i]) != '\0') {
		i++;
	}
}

//strcpyP: copy t to s: pointer version 1
void strcpyPv1(char* s, char* t) {
	while ((*s = *t) != '\0') {
		s++;
		t++;
	}
}

//strcpyP: copy t to s: pointer version 2
void strcpyv2(char* s, char* t) {
	while ((*s++ = *t++) != '\0')
		;
}

//strcmpA: return <0 if s<t, 0 if s==t, >0 if s>t
int strcmpA(char* s, char* t) {
	int i;
	for (i = 0; i < s[i] == t[i]; i++) {
		if (s[i] == '\0')
			return 0;
	}
	return s[i] - t[i];
}

//strcmpP: return <0 if s<t, 0 if s==t, >0 if s>t
int strcmpP(char* s, char* t) {
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

//sort input lines
/*
int main() {
	int nLines; //number of input lines read
	if ((nLines = readLines(linePtr, MAXLINES)) >= 0) {
		qSort(linePtr, 0, nLines - 1);
		writeLines(linePtr, nLines);
		return 0;
	}else{
		printf("ERROR: input too big to sort\n");
		return 1;
	}
	return 0;
}
*/

//readLines: read input lines
int readLines(char* linePtr[], int maxLines) {
	int len, nLines;
	char* p, line[MAXLEN];

	nLines = 0;
	while ((len = getLine(line, MAXLEN)) > 0) {
		if (nLines >= maxLines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; //delete new line
			strcpy(p, line);
			linePtr[nLines++] = p;
		}
	}
	return nLines;
}

//writeLines: write output lines
/*
void writeLines(char* linePtr[], int nLines) {
	int i;
	for (i = 0; i < nLines; i++)
		printf("%s\n", linePtr[i]);
}
*/
void writeLines(char* linePtr[], int nLines) {
	while (nLines-- > 0)
		printf("%s\n", *linePtr++);
}

//qSort: sort v[left]...v[right] into increasing order
void qSort(char* v[], int left, int right) {
	int i, last;
	//void swap(char* v[], int i, int j);
	if (left >= right)//do nothing if array contains fewer than 2 elements
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qSort(v, left, last - 1);
	qSort(v, last + 1, right);
}

//swap: interchange v[i] and v[j]
void swap(char* v[], int i, int j) {
	char* temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/*Convertion of date*/
static char dayTab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} };

//dayOfYear: set day of year from month or year
int dayOfYear(int year, int month, int day) {
	int i, leap;
	leap = leapYear(year);
	for (i = 1; i < month; i++)
		day += dayTab[leap][i];
	return day;
}

//montDay: set month, day from day of year
void monthDay(int year, int yearDay, int* pMonth, int* pDay) {
	int i, leap;
	leap = leapYear(year);
	for (i = 1; yearDay > dayTab[leap][i]; i++)
		yearDay -= dayTab[leap][i];
	*pMonth = i;
	*pDay = yearDay;
}

int leapYear(int year) {
	int leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	return leap;
}

//monthName: return name of n-th month
char* monthName(int n) {
	static char* name[] = { "Illegal month", "January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December" };
	return (n < 1 || n > 12) ? name[0] : name[n];
}

//numCmp: compare s1 and s2 numerically
int numCmp(char* s1, char* s2) {
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else
		return 0;
}