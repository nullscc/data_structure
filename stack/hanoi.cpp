#include<stdio.h>

int cnt=0;

void move(int i, char x, char z) {
	cnt++;
	printf("step %d: 圆盘 %d 从 %c -> %c\n", cnt, i, x, z);
}

void hanoi(int n, char x, char y, char z) {
	if (n==1) {
		move(n, x, z);
	} else {
		hanoi(n-1, x, z, y);
		move(n, x, z);
		hanoi(n-1, y, x, z);
	}
}

int main() {
	hanoi(7, 'A', 'B', 'C');
	return 0;
}
