#include <stdio.h>

/*Count digits, white spaces, others*/
int countValues() {
	int c, i, nWhite, nOther, nDigits[10];
	int size = sizeof(nDigits) / sizeof(nDigits[0]);
	nWhite = nOther = 0;
	for (i = 0; i < size; i++) {
		nDigits[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		switch (c) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			nDigits[c - '0']++;
			break;

		case ' ': case '\n': case '\t':
			nWhite++;
			break;

		default:
			nOther++;
			break;
		}
	}

	printf("\nDigitd =");
	for (i = 0; i < size; i++) {
		printf("\n%d", nDigits[i]);
	}
	printf(", whilte spaces = %d other = %d\n", nWhite, nOther);
	return 0;
}