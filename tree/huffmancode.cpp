#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"../common.h"

typedef struct {
	char data;
	int weight;
	int parent, lchild, rchild;
}HTNode, *pHTNode;

// TODO: 这里暂时用暴力方法
void select(pHTNode ht, int i, int &s1, int &s2) {
	int j;
	int min = INT_MAX;	// TODO: 用位操作来实现
	for(j=1; j<=i; j++) {
		if (ht[j].parent==0 && ht[j].weight < min) {
			min = ht[j].weight;
			s1 = j;
		}
	}

	min = INT_MAX;
	for(j=1; j<=i; j++) {
		if (j != s1 && ht[j].parent==0 && ht[j].weight < min) {
			min = ht[j].weight;
			s2 = j;
		}
	}
}

pHTNode BuildHuffTree(int *weight, char *data, int n) {
	int m = 2*n - 1;
	int i;
	pHTNode ht = (pHTNode)malloc(sizeof(HTNode)*(m+1)); // 0不用，因为要用来表示没有左右结点
	for (i=1; i<=n; i++) {
		ht[i] = {data[i-1], weight[i-1], 0, 0, 0};
	}
	for (; i<=m; i++) {
		ht[i] = {' ', 0, 0, 0, 0};
	}
	
	for(i=n+1; i<=m; i++) {
		int s1, s2;
		select(ht, i-1, s1, s2);
		ht[i].lchild = s1;
		ht[i].rchild = s2;
		ht[s1].parent = i;
		ht[s2].parent = i;
		ht[i].weight = ht[s1].weight + ht[s2].weight;
	}

	return ht;
}

typedef HTNode QElemType;

typedef struct QNode{ // 这里必须要先"证明"这个结构体名是QNode，不然在里面没法定义next
	QElemType data;
	struct QNode *next;
}QNode, *pQNode;

typedef struct {
	pQNode front;
	pQNode rear;
}Queue;

Status InitQueue(Queue &Q) {
	Q.front = (pQNode)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);

	Q.front->next = NULL;
	Q.rear = Q.front;
	return OK;
}

Status EnQueue(Queue &Q, QElemType e) {
	// NOTE: 插入不存在队列满的情况
	
	pQNode tmp = (pQNode)malloc(sizeof(QNode));
	if (!tmp) exit(OVERFLOW);

	tmp->data = e;
	tmp->next = NULL;
	
	Q.rear->next = tmp;
	Q.rear = tmp;

	return OK;
}

Status DeQueue(Queue &Q, QElemType &e) {
	if (Q.front == Q.rear) return ERROR;

	pQNode tmp = Q.front->next;
	e = tmp->data; // NOTE: 队头是空的
	Q.front->next = tmp->next;

	if (tmp == Q.rear) Q.rear = Q.front;
	free(tmp);

	return OK;
}


Status QIsEmpty(Queue &Q) {
	return Q.front == Q.rear;
}

Status LevelSearch(HTNode *ht, int n) {
	Queue Q;
	InitQueue(Q);
	int m = 2*n;
	HTNode h;

	EnQueue(Q, ht[m-1]);
	while(!QIsEmpty(Q)) {
		DeQueue(Q, h);
		printf("{weight:%d data:%c}\n", h.weight, h.data);
		if(h.lchild) EnQueue(Q, ht[h.lchild]);
		if(h.rchild) EnQueue(Q, ht[h.rchild]);
	}

	return OK;
}

// 编码就是将一串字符编码成二进制前缀码
char **HuffmanEncode(pHTNode ht, int n) {
	char **hc=(char**)malloc(sizeof(char *)*(n));;
	int m = 2*n-1;
	int i;
	char *tmp = (char *)malloc(sizeof(char)*n);
	for(i=1; i<=n; i++) {
		int start = n-1;
		int p = ht[i].parent;
		int j = i;
		while(p) {
			if (ht[p].lchild == j) {
				tmp[start] = '0';
			} else {
				tmp[start] = '1';
			}
			start--;
			j = p;
			p = ht[p].parent;
		}
		hc[i-1] = (char *)malloc(sizeof(char)*(n-1-start));
		strcpy(hc[i-1], &tmp[start+1]);
	}
	free(tmp);

	return hc;
}

char *HuffmanDecode(pHTNode ht, char**encode, int n) {
	int i;
	char *decode = (char *)malloc(sizeof(char)*n);
	for(i=0; i<n; i++) {
		int len = strlen(encode[i]);
		int j;
		int index=2*n-1;
		for(j=0; j<len; j++) {
			if(encode[i][j] == '0') {
				index = ht[index].lchild;
			} else {
				index = ht[index].rchild;
			}
		}
		decode[i] = ht[index].data;
	}

	return decode;
}

/*
数据为:
字母	编码	权重
a 		0		45
b 		101 	13
c 		100 	12
d 		111 	16
e 		1101 	9
f 		1100 	5
*/
int main() {
	int weight[6] = {45, 13, 12, 16, 9, 5};
	char data[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
	int n = 6;

	pHTNode ht = BuildHuffTree(weight, data, n);
	printf("打印Huffman树:\n");
	LevelSearch(ht, 6);
	
	char **hc = HuffmanEncode(ht, n);
	int i;
	printf("打印Huffman编码:\n");
	for(i=0; i<n; i++) {
		printf("%s\n", hc[i]);
	}
	
	char *decode = HuffmanDecode(ht, hc, n);
	printf("打印Huffman解码:\n");
	for(i=0; i<n; i++) {
		printf("%c\n", decode[i]);
	}
	return 0;
}
