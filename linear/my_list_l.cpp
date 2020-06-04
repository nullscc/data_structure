// NOTE: 注意操作指针时，访问NULL的指向时导致程序崩溃的问题 
// NOTE: 位序是从带数据的节点开始算的 

#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

typedef int ElemType;

typedef struct LNode{
	ElemType data;
	LNode *next;
}LNode, *LinkList;

Status GetElem_L(LinkList &L, int i, ElemType &e) {
	int j=0;
	LinkList p = L; // NOTE: 这里一定起始不能是 p = L-next 
	while(p && j<i) {
		p = p->next;
		j++;
	}
	
	if (j<i) return ERROR;
	
	e = p->data;
	
	return OK;
}

Status ListInit_L(LinkList &L) {
	L->next = NULL; 
	return OK;
}

Status ListInsert_L(LinkList &L, int i, ElemType e) {
	int j=0;
	LinkList p = L; // NOTE: 这里一定起始不能是 p = L-next
	
	while (p && j<i-1) {
		p = p->next;
		j++;
	}
	
	if (j<i-1) return ERROR;
	LinkList q = (LinkList)malloc(sizeof(LNode));
	if (!q) return OVERFLOW;
	
	q->next = p->next;
	q->data = e;
	p->next = q;
	
	return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e) {
	int j=0;
	LinkList p = L; // NOTE: 这里一定起始不能是 p = L-next
	
	while (p && j<i-1) {
		p = p->next;
		j++;
	}
	if (j<i-1) return ERROR;
	
	LinkList q = p->next;
	e = q->data;
	
	p->next = p->next->next;
	free(q);
	
	return OK;
}

Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
	LinkList pa = La->next; // NOTE: 这里一定起始要是 pa = La->next
	LinkList pb = Lb->next;
	LinkList pc = Lc; // NOTE: 这里一定起始不能是 p = L-next
	
	while (pa && pb){
		LinkList tmp = (LinkList)malloc(sizeof(LNode));
		tmp->next = NULL;
		pc->next = tmp;
		
		if (pa->data <= pb->data) {
			tmp->data = pa->data;
			pa = pa->next;
		} else {
			tmp->data = pb->data;
			pb = pb->next;
		}
		pc = pc->next;
	}

	pc->next = pa ? pa : pb; // NOTE: 由于是链表，所以不需要后面的两层循环了，但是如果不共享地址的话就还是需要，按照程序设计规范来说感觉还是需要将数据完全拷贝过来，而不仅仅是链接过来 
//	while (pa) {
//		LinkList tmp = (LinkList)malloc(sizeof(LNode));
//		tmp->next = NULL;
//		pc->next = tmp;
//		
//		tmp->data = pa->data;
//		
//		pa = pa->next;
//		pc = pc->next;
//	}
//	
//	while (pb) {
//		LinkList tmp = (LinkList)malloc(sizeof(LNode));
//		tmp->next = NULL;
//		pc->next = tmp;
//		tmp->data = pb->data;
//		
//		pb = pb->next;
//		
//		pc = pc->next;
//	}
	
	return OK;
}

