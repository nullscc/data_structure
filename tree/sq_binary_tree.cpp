// 二叉树的顺序存储结构

#include<stdio.h>
#include<math.h>

typedef struct  {
	int pre; 	// 前面应该空多少空格
	int blank; 	// 每个元素之间应该空多少个空格

}PrintData, pPrintData[8];	// 256个元素最多8层

void get_print_data(PrintData pd[], int k, int last_blank) {
	// TODO: 没有考虑k越界的情况
	// 也没有考虑pre blank越界的情况(如果pre或者blank越界了屏幕应该也装不下了，这个程序也没有任何意义了)
	int i;
	pd[k-1].pre = 0;
	int num = pow(2, k-1);
	pd[k-1].blank = 1;
	int total = num + (num-1)*pd[k-1].blank;
	for(i=k-1; i>=1; i--) {
		pd[i-1].pre = (2*pd[i].pre + 1 + pd[i].blank) / 2;
		num = pow(2, i-1);
		if(i==1) pd[i-1].blank =0;
		else pd[i-1].blank = (total - 2*pd[i-1].pre - num) / (num-1);
	}
}

void print_blank(int num) {
	int j;
	for(j=0; j<num; j++) {
		printf(" ");
	}
}

int main() {
	int n = 0;
	char tree[255];

	printf("请输入二叉树:"); // 数据元素只接受单个字符，如果某个节点不存在则用空格

	char in;
	in = getchar();
	
	while (in != EOF) {
		tree[n] = in;
		n++;
		in = getchar();
	};

	int i;
	int s=1;
	int k=1;
	for(i=1; s<n;i++) {
		int tmp = pow(2, i);
		for(; tmp>0; tmp--) {
			s = s + 1;
		}
		k++;
	}
	printf("\n您输入的二叉树一共有%d层\n", k);
	

	pPrintData pd;
	get_print_data(pd, k, 1);
	s=0;
	for(i=1; i<=k; i++) {
		int index_start = (1-pow(2, i-1))/(1-2);
		int index_end = pow(2, i)-1;
		print_blank(pd[i-1].pre);
		for(; index_start<index_end; index_start++) {
			printf("%c", tree[index_start]);
			print_blank(pd[i-1].blank);
			s++;
			if (s>=n) break;
		}
		printf("\n");
		if (s>=n) break;
	}

	return 0;
}
