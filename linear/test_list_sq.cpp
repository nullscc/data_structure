// 线性表的顺序实现的测试程序 

#include<stdio.h>
#include "list_sq.cpp"
//#include "my_list_sq.cpp"
#include <assert.h>

Status compare(int a, int b){
	if (a==b) return TRUE;
	return FALSE;
}

int main() {
	SqList L;
	
	InitList_SQ(L);
	printf("初始化后，动态数组的地址:%p, listsize:%d，length:%d\n", L.elem, L.listsize, L.length);
	assert(L.elem);
	assert(LIST_INIT_SIZE==L.listsize);
	assert(!L.length);
	
	int i=1;
	for (; i<=L.listsize; i++) {
		assert(ListInsert_Sq(L, L.length+1, i)==1);
	}
	printf("插入100个元素后，动态数组里面的数据为:");
	for (i=1; i<=L.length; i++) {
		printf(" %d", L.elem[i-1]);
	}
	printf("\n");
	assert(L.elem);
	assert(LIST_INIT_SIZE==L.listsize);
	assert(L.length==100);
	
	for (i=1; i<=L.length; i++) {
		assert(LocateElem_Sq(L, i, compare)==i);
	}
	
	assert(ListInsert_Sq(L, 99, 98));
	printf("在99的位置上插入98后:");
	int sum=0;
	for (i=1; i<=L.length; i++) {
		sum += L.elem[i-1]; 
		printf(" %d", L.elem[i-1]);
	}
	printf("\n");
	printf("%d", sum);
	assert(sum==5148);
	assert(L.listsize==LIST_INIT_SIZE+LISTINCREMENT);
	assert(L.length==LIST_INIT_SIZE+1);
	
	//删除99上的98
	ElemType tmp;
	assert(ListDelete_Sq(L, 99, tmp));
	assert(tmp == 98);
	assert(LIST_INIT_SIZE+LISTINCREMENT==L.listsize);
	assert(L.length==LIST_INIT_SIZE);
	printf("删除99上的98后，动态数组里面的数据为:");
	for (i=1; i<=L.length; i++) {
		printf(" %d", L.elem[i-1]);
	}
	printf("\n");
	
	SqList Lb, Lc;
	InitList_SQ(Lb);
	
	for (i=1; i<=10; i++) {
		assert(ListInsert_Sq(Lb, Lb.length+1, i)==1);
	}
	
	printf("Lb动态数组里面的数据为:");
	for (i=1; i<=Lb.length; i++) {
		printf(" %d", Lb.elem[i-1]);
	}
	printf("\n");
	
	MergeList_Sq(L, Lb, Lc);
	
	printf("Lc动态数组里面的数据为:");
	ElemType prev = -1;
	for (i=1; i<=Lc.length; i++) {
		assert(Lc.elem[i-1] >= prev);
		printf(" %d", Lc.elem[i-1]);
		prev = Lc.elem[i-1]; 
	}
	printf("\n");
	printf("Lc.listsize: %d, Lc.length:%d", Lc.listsize, Lc.length);
	assert(Lc.listsize==LIST_INIT_SIZE+2*LISTINCREMENT);
	assert(Lc.length==110);
	
	return 0;
}

