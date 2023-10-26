#include "utils.h"

/* sort: sort v[left]...v[right] into increasing order */
void sort(int v[], int left, int right) {
	int i, last;

	if (left >= right)
		return;
	swap(&v[left], &v[(left + right)/2]);
	last = left;
	for (i = left+1; i <= right; i++)
		if (v[i] < v[left])
			swap(&v[++last], &v[i]);
	swap(&v[left], &v[last]);
	sort(v, left, last-1);
	sort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int *px, int *py) {
	int temp;

	temp = *px;
	*px = *py;
	*py = temp;
}

