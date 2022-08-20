#include <stdio.h>

/*strlen: return length of s*/
int stringLen(char s[]) {
	int i = 0;
	while (s[i] != '\0'){
		++i;
	}
	return i;
}

void isLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		printf("\n%d is a leap year", year);
	}else {
		printf("\n%d is not a leap year...", year);
	}
}

/*strcat: concaternate t to end of s: s must be big enough*/
void strcat(char s[], char t[]) {
	int i, j;
	i = j = 0;
	while (s[i] != '\0') {
		i++;
	}
	while ((s[i++] = t[j++]) != '\0');
}

/*bitcount: count 1 bits in x*/
int bitCount(unsigned x) {
	int b;
	for (b = 0; x != 0; x >>= 1) {
		if (x & 01)
			b++;
	}
	return b;
}

/*Binary Search:
binarySearch: find x in v[0] <= v[1] <= ... <= v[n - 1]*/
int binarySearch(int x, int v[], int n) {
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (high - low) / 2;
		if (x, v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else //found match
			return mid;
	}
	return -1;//No match
}

int main_() {
	isLeapYear(2021);
	return 0;
}

int main__() {
	char s[] = {'f', 'p', 'g'};

	int charSize = sizeof(s) / sizeof(s[0]);
	int strSize = stringLen(s);

	printf("\nChar Szie: %d", charSize);
	printf("\nString length size: %d", strSize);
	printf("\nOutput: ");

	for (int i = 0; i < charSize; i++) {
		char x = s[i];
		printf("%c", x);
	}
	return 0;
}