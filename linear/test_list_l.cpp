#include<stdio.h>
#include<assert.h>
#include"list_l.cpp"
//#include"my_list_l.cpp"

int main() {
	LinkList L = (LinkList)malloc(sizeof(LNode));
	ListInit_L(L);
	
	// 这里初始化的next指针如果不手动置为NULL，则整个程序出错 
	printf("初始化数据为:%d %p\n", L->data, L->next);
	int i;
	
	for(i=1;i<=10;i++) {
		ListInsert_L(L, i, i);
	}

	
	LinkList tmp=L; 
	for (i=1;i<=10;i++) {
		tmp = tmp->next;
		assert(tmp->data==i);
	} 
	
	for (i=1;i<=10;i++) {
		ElemType tmp;
		assert(GetElem_L(L, i, tmp));
		assert(tmp==i);
	} 
	
	ElemType e_tmp;
	ListDelete_L(L, 1, e_tmp);
	assert(e_tmp==1);
	ListDelete_L(L, 8, e_tmp);
	assert(e_tmp==9);
	ListDelete_L(L, 8, e_tmp);
	assert(e_tmp==10);
	
	printf("链表里面的数据为:");
	LinkList p = L;
	while (p->next) {
		printf(" %d", p->next->data);
		p = p->next;
	}
	printf("\n");
	
	LinkList Lb = (LinkList)malloc(sizeof(LNode));
	ListInit_L(Lb);
	
	for(i=1; i<9;i++) assert(ListInsert_L(Lb, i, i+8));
	printf("链表Lb里面的数据为:");
	p = Lb;
	while (p->next) {
		printf(" %d", p->next->data);
		p = p->next;
	}
	printf("\n");
	
	LinkList Lc = (LinkList)malloc(sizeof(LNode));
	ListInit_L(Lc);
	MergeList_L(L, Lb, Lc);
	
	printf("链表Lc里面的数据为:");
	printf("Lc的地址:%p\n", Lc);
	p = Lc;
	printf("Lc的二次地址:%p\n", p);
	int j=1;
	while (p->next) {
		printf(" %d", p->next->data);
		assert(p->next->data==j+1);
		p = p->next;
		j++;
	}
	printf("\n");
	
	return 0;
}
