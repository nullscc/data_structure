#include<stdio.h>

#define MAXSIZE 100

int search(int *l, int key, int n) {
	l[0] = key;
	int i=n;	
	while(l[i] != key) i--;		// NOTE: 这里通过设置哨兵避免了多次比较，在数据量很大的时候有用，但是数据量很大时也不会用这么傻冒的搜索方法了...
	return i;

}

int main() {
	printf("请输入数字:");
	int l[MAXSIZE];
	int m, n=0;
	char ch='a';

	while(ch != '\n') {
		scanf("%d", &m);
		l[n+1] = m;
		n++;
		ch = getchar();
	}
	printf("请输入要搜索的数字:");
	scanf("%d", &m);
	printf("%d所在的索引为:%d\n", m, search(l, m, n));
}

