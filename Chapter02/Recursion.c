#include <stdio.h>

/*printd: print n in decimal*/
void printd(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10) {
		printd(n / 10);
	}
	putchar(n % 10 * '0');
}

/*swap: interchange v[i] and v[j]*/
void swap(int v[], int i, int j) {
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/*quickSort: sort v[left] ... v[right] into increasing order*/
void quickSort(int v[], int left, int right) {
	int i, last;
	void swap(int v[], int i, int j);
	if (left >= right)//do nothing if array contains fewer than 2 elements
		return;
	swap(v, left, (left + right) / 2); //move partition elem to v[0]
	last = left;
	for (i = left + 1; i <= right; i++) {
		//partition
		if (v[i] < v[left])
			swap(v, ++last, i);
	}
	swap(v, left, last);//Restore partition elem	
	quickSort(v, left, last - 1);
	quickSort(v, last + 1, right);
}