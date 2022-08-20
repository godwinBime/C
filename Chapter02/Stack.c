#include <stdio.h>
#include <stdlib.h> //for atof()
#include <ctype.h>

/*REEVERSE POLISH NOTATION*/

#define MAXOP 100 //max size of operand or operatoor
#define NUMBER '0' //signal that a number was found
#define MAXVAL 100 //the maximum depth of val stack
#define BUFFSIZE 100

int getTop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int c);

int sp = 0;
double val[MAXVAL];
char buf[BUFFSIZE]; //buffer for ungetch
int bufp = 0; //next free position in buf

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

/*push: push f onto value stack*/
void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	}
	else
		printf("ERROR: stack full, can't push %g\n", f);
}

/*pop: pop and return top value from stack*/
double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("ERROR: stack is empty...\n");
		return 0.0;
	}
}

/*getTop: get next operator or numeeric operand*/
int getTop(char s[]) {
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (isdigit(c))//collect integer part
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')//Collect fraction part
		while (isdigit(s[i++] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

//Reverse polish calculator
int main() {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getTop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			pudh(pop() * pop());
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
				printf("ERROR: zero division...\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("ERROR: Unknown command %s\n", s);
			break;
		}
	}
	return 0;
}