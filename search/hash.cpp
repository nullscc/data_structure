/* 散列表
散列函数用除数留余法
冲突用链地址法解决
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"../common.h"

#define SIZE 99

typedef struct Node {
	int key;
	int value;
	Node *next;
}Node, *pNode;

typedef struct {
	pNode l[SIZE];	// 只可以存数字吧~
	int size;

}Hash, *pHash;

int func(int m, int key) {
	return key % m;
}

Status Insert(Hash &h, int key, int value) {
	int addr = func(h.size, key);
	if(!h.l[addr]) {
		h.l[addr] = (pNode)malloc(sizeof(Node));
		h.l[addr]->next = NULL;
		h.l[addr]->value = INT_MAX;
	}
	
	pNode p = h.l[addr];
	pNode f;
	while(p) {
		if(p->key == key || p->value == INT_MAX) {
			p->value = value;
			p->key = key;
			return OK;
		}
		f = p;
		p = p->next;
	}
	pNode tmp = (pNode)malloc(sizeof(Node));
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	f->next = tmp;

	return OK;
}

Status Search(Hash &h, int key, int &value) {
	int addr = func(h.size, key);
	pNode p = h.l[addr];

	while(p) {
		if(p->key == key) {
			value = p->value;
			return OK;
		}
		p = p->next;
	}

	return ERROR;
}

Status Init(Hash &h) {
	int i;
	h.size = SIZE;				// NOTE: 如果将h.size写成大于SIZE，那么这个函数会改写h.size的值，实际上是由于结构体存储结构造成的
	for(i=0; i<h.size; i++) {
		h.l[i] = NULL;
	}
	return OK;
}

int main() {
	Hash h;
	Init(h);

	Insert(h, 10, 100);
	int v;
	Search(h, 10, v);
	printf("首次往key:10写入后搜索key:10的结果:%d\n", v);
	Insert(h, 10, 1000);
	Search(h, 10, v);
	printf("改写key:10后搜索key:10的结果:%d\n", v);
	
	Insert(h, 109, 10000);
	Search(h, 10, v);
	printf("往key:109写入创造冲突后搜索key:10的结果:%d\n", v);
	Search(h, 109, v);
	printf("搜索key:109的结果:%d\n", v);
}
