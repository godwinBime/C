#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100 //maximuminput line length

int getLine(char line[], int max);
int strIndex(char source[], char searchFor[]);
double atof(char s[]);



char pattern[] = "ould";


//Find all linesmatching pattern
int main_() {
	char line[MAXLINE];
	int found = 0;
	printf("Enter a phrase...: ");
	while (getLine(line, MAXLINE) > 0) {
		if (strIndex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	return found;
}

/*getLine: get line into s, return length*/
int getLine(char s[], int lim) {
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/*strIndex: return index of t in s, -1 if none*/
int strIndex(char s[], char t[]) {
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {
			if (k > 0 && t[k] == '\0')
				return i;
		}
	}
	return -1;
}

/*atof: convert string s to double*/
double atof(char s[]) {
	double val, power;
	int i, sign;
	for (i = 0; isspace(s[i]); i++)/*Skip white spaces*/
		;

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	
	if (s[i] == '.')
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

/*atoi: convert string s to integer using atof*/
int atoi(char s[]) {
	double atof(char s[]);
	return (int)atof(s);
}

int main__() {
	double sum, atof(char[]);
	char line[MAXLINE];

	int getLine(char line[], int max);

	sum = 0;
	while (getLine(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof(line));
	return 0;
}