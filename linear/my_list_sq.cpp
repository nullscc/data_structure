#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_SQ(SqList &L) {
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	L.elem = (ElemType *)malloc(sizeof(ElemType)*L.listsize);
	return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e) {
	if (!((i<=L.length+1) && (i>=1))) {
		return ERROR;
	}
	
	if (L.length+1 > L.listsize) {
		L.elem = (ElemType *)realloc(L.elem, sizeof(ElemType)*(L.listsize+LISTINCREMENT));
		if (!L.elem) return OVERFLOW;
		L.listsize = L.listsize+LISTINCREMENT; 
	}
	
	int j;
	for (j=L.length; j>=i; j--) {
		L.elem[j] = L.elem[j-1];
	}
	L.elem[i-1] = e;
	
	L.length += 1;
	
	return OK;
}

Status LocateElem_Sq(SqList &L, ElemType e, Status (*compare)(ElemType, ElemType)) {
	int i;
	for(i=i; i<=L.length; i++) {
		if ((*compare)(e, L.elem[i-1])) {
			return i;
		}
	}
	return 0;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e) {
	if (!((i<=L.length+1) && (i>=1))) {
		return ERROR;
	}
	
	e = L.elem[i-1];
	
	int j;
	for(j=i; j<=L.length-1; j++) {
		L.elem[j-1] = L.elem[j];
	}
	
	L.length -= 1;
	
	return OK;
}

Status MergeList_Sq(SqList La, SqList &Lb, SqList &Lc) {
	// TODO: La ºÍ Lb ÒªÏÈÅÅÐò 
	Lc.listsize = LIST_INIT_SIZE + ((((La.length + Lb.length) - LIST_INIT_SIZE) / 10) + 1) * 10;
	Lc.elem = (ElemType *)malloc(sizeof(ElemType)*Lc.listsize);
	Lc.length = La.length + Lb.length; 
	
	int i=1, j=1, k=1;
	
	while (i<=La.length && j<=Lb.length) {
		if (La.elem[i-1] <= Lb.elem[j-1]) {
			Lc.elem[k-1] = La.elem[i-1];
			i++;
		} else {
			Lc.elem[k-1] = Lb.elem[j-1];
			j++;
		}
		k++;
	}
	
	while (i<=La.length) {
		Lc.elem[k-1] = La.elem[i-1];
		i++;
		k++; 
	}

	while (j<=Lb.length) {
		Lc.elem[k-1] = Lb.elem[j-1];
		j++;
		k++; 
	}
	
	return OK; 
}

