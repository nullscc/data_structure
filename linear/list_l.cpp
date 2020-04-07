// 线性表的链表实现

#include<stdio.h>
#include<stdlib.h>
#include "../common.h"

typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

Status GetElem_L(LinkList &L, int i, ElemType &e) {
	LinkList p = L->next;
	int j=1;
	while(p&&j<i) {
		p = p->next; ++j;
	}
	
	if (!p || j>i) return ERROR;
	e = p->data;
	return OK;
} 

Status ListInit_L(LinkList &L) {
	L->next = NULL;
	return OK;
}

Status ListInsert_L(LinkList &L, int i, ElemType e) {
	LinkList p = L;
	int j=0;
	
	while(p && j<i-1) {
		p = p->next;
		++j;
	}
	
	if (!p || j>i-1) return ERROR;
	
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	
	return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e) {
	LinkList p = L;
	int j = 0;
	
	while (p->next && j<i-1) {
		p = p->next;
		++j;
	}
	
	if (!(p->next)) return ERROR;
	
	LinkList q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);	
}

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
	LinkList pa = La->next, pb = Lb->next;
	LinkList pc;
	Lc = pc = La;
	while (pa && pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		} else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	
	pc->next = pa ? pa : pb;
	free(Lb); // 这里应该不能释放吧？感觉不符合程序设计规范 
}
