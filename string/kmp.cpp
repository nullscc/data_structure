// kmp算法，由于很多参考书都是字符串的第0个index是长度，所以实现略有不同
// 参考了下博客: https://blog.csdn.net/dark_cy/article/details/88698736

#include<stdio.h>
#include<string.h>
#include"../common.h"

// NOTE: 得到next数值的过程仍然看作一个逐步模式匹配的过程
void get_next(char *p, int *next) {	// 这里取到的next值和书本上差1
	int i=0, j=-1;
	int len_p = strlen(p);
	
	next[0] = -1;
	while (i < len_p) {		// 注意理解为什么下标i没有越界
		if(j == -1 || p[i] == p[j]) {
			i++; j++;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
}

void get_nextval(char *p, int *next) {	// 这里取到的next值和书本上差1
	int i=0, j=-1;
	int len_p = strlen(p);
	
	next[0] = -1;
	while (i < len_p) {
		if(j == -1 || p[i] == p[j]) {
			i++; j++;
			if (p[i] == p[j])  next[i] = next[j];		// NOTE: 这里的的优化原因在于:next数组表示当某个数与当前next值不匹配，那么就代表需要回退到某个点，如果模式值相等，那么这次比较也无意义了，直接回退到不相等的点，减少比较次数
			else next[i] = j;
		} else {
			j = next[j];
		}
	}
}

int kmp(char *s, char *p) {
	int next[255] = {0};
	get_next(p, next);
	// get_nextval(p, next);
	
	// DEBUG
	// int tmp;
	// for(tmp=0; tmp<10; tmp++) {
	// 	printf("next[%d] = %d\n", tmp, next[tmp]);
	// }

	int len_p = strlen(p);
	int len_s = strlen(s);

	int i=0, j=0;
	while(j < len_p && i < len_s) {
		if (j==-1 || s[i] == p[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
	if (j>=len_p) return i - len_p;
	else return -1;

}

int main() {
	// char s[] = "abcdadabadca";
	// char p[] = "abad";
	char s[] = "aaabaaaab";
	char p[] = "aaaab";
	printf("kmp of p:%s and s:%s, index:%d\n", p, s, kmp(s, p));

	return 0;
}
