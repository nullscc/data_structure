// 二叉排序树不能有相同的数值？
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"../common.h"

typedef int ElemType;

typedef struct Node{
	ElemType data;
	Node *lchild;
	Node *rchild;	
	
}Node, *pNode;


// Search要返回两种信息: 成功或者失败；最后一次有效结点
// 即成功时需要返回对应的搜索到的结点；失败时需要返回失败时的父节点
Status Search(pNode &T, pNode f, pNode &p, ElemType e, pNode &parent) {
	int ret;

	if(!T) {
		p = f;
		parent = f;
		return ERROR;
	}
	ret = Search(T->lchild, T, p, e, parent);
	if (!ret) return ret;

	if(T->data == e) {
		p = T;
		parent = f;
		return OK;
	}

	ret = Search(T->rchild, T, p, e, parent);
	if (!ret) return ret;
	return OK;
}

Status Insert(pNode &T, ElemType e) {
	pNode s;
	pNode parent;
	if (!(Search(T, NULL, s, e, parent))) {
		pNode p = (pNode)malloc(sizeof(Node));
		p->data = e;
		p->lchild = NULL;
		p->rchild = NULL;

		if(!T) {
			T = p;
			return OK;
		}

		if (s->data == e) {
			return ERROR;
		}
		
		if(s->data > e) {
			s->lchild = p;
		} else {
			s->rchild = p;
		}
		return OK;
	}
	return ERROR;
}

Status SearchLchildRchildLast(pNode &T, pNode &f, pNode &last){
	if (!T) return ERROR;
	
	if(!T->lchild) return ERROR;

	pNode p = T->lchild;
	while(p) {
		if (p->rchild && !p->rchild->rchild) {
			f = p;
			last = p->rchild;
		}
		p->rchild;
	}

	return OK;
}

Status Delete(pNode &T, ElemType e) {
	pNode s, parent;
	int ret = Search(T, NULL, s, e, parent);
	if(!ret) return ERROR;

	if (!s->lchild) {
		parent->rchild = s->rchild;
	} else if(!s->rchild) {
		parent->lchild = s->lchild;
	} else {
		pNode f, last;
		SearchLchildRchildLast(s, f, last);
		if(last->lchild) {
			f->rchild = last->lchild;
		} else {
			f->rchild = NULL;
		}
		last->lchild = s->lchild;
		last->rchild = s->rchild;
		if(s->data > parent->data) {
			parent->rchild = last;
		} else {
			parent->lchild = last;
		}
	}
	free(s);
	return OK;
}

int main() {
	int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
	int i;
	pNode T;
	for(i=0; i<10; i++) {
		Insert(T, a[i]);
	}


	return 0;
}
