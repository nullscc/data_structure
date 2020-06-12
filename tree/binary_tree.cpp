// 先序遍历二叉树
#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"tree.h"
#include"stack_sq.cpp"
#include"link_queue.cpp"

// 执行a.out < data, p129的数据
// 执行a.out < data2, p127的数据
// NOTE: 注意数据文件里面的空格，很重要
Status Create(pNode &pnode) {
	char ch;
	scanf("%c", &ch);
	if (ch == ' ') pnode = NULL;
	else {
		pnode = (pNode)malloc(sizeof(Node));
		pnode->data = ch;
		
		Create(pnode->lchild);
		Create(pnode->rchild);
	}
	return OK;
}

Status print_elem(ElemType e) {
	printf("%c", e);
	return OK;
}

Status PreSearch(pNode pnode) {
	if (!pnode) return OK;

	print_elem(pnode->data);
	
	PreSearch(pnode->lchild);
	PreSearch(pnode->rchild);
	return OK;
}

Status PostSearch(pNode pnode) {
	if (!pnode) return OK;
	
	PostSearch(pnode->lchild);
	PostSearch(pnode->rchild);
	print_elem(pnode->data);
	return OK;
}

Status MidSearch(pNode pnode) {
	if (!pnode) return OK;
	MidSearch(pnode->lchild);
	print_elem(pnode->data);
	MidSearch(pnode->rchild);
	return OK;
}

Status PreSearch2(pNode p) {
	pNode pnode = p;
	SqStack S;
	InitStack(S);
	while(pnode || !IsEmpty(S)) {
		if (pnode) {
			print_elem(pnode->data);
			Push(S, pnode);
			pnode = pnode->lchild;
		} else {
			Pop(S, pnode);
			pnode = pnode->rchild;
		
		}
	}
	return OK;
}

Status MidSearch2(pNode p) {
	pNode pnode = p;
	SqStack S;
	InitStack(S);
	while(pnode || !IsEmpty(S)) {
		if (pnode) {
			Push(S, pnode);
			pnode = pnode->lchild;
		} else {
			Pop(S, pnode);
			print_elem(pnode->data);
			pnode = pnode->rchild;
		}
	}
	return OK;
}

Status PostSearch2(pNode p) {
	pNode pnode = p;
	SqStack S;
	InitStack(S);
	pNode r = NULL;
	while(pnode || !IsEmpty(S)) {
		if (pnode) {
			Push(S, pnode);
			pnode = pnode->lchild;
		} else {
			GetTop(S, pnode);
			if (pnode->rchild && pnode->rchild!=r) {
				pnode = pnode->rchild;
				Push(S, pnode);
				pnode = pnode->lchild;
			} else {
				Pop(S, pnode);
				print_elem(pnode->data);
				r = pnode;
				pnode = NULL;
			}
		}
	}
	return OK;
}

Status LevelSearch(pNode pnode) {
	Queue Q;
	InitQueue(Q);
	pNode p;

	EnQueue(Q, pnode);
	while(!QIsEmpty(Q)) {
		DeQueue(Q, p);
		print_elem(p->data);
		if(p->lchild) EnQueue(Q, p->lchild);
		if(p->rchild) EnQueue(Q, p->rchild);
	}

	return OK;
}

int main() {
	printf("请输入二叉树的元素:");

	pNode parent;
	Create(parent);
	
	printf("\n");
	printf("前序遍历结果:");
	PreSearch(parent);
	printf("\n");

	printf("中序遍历结果:");
	MidSearch(parent);
	printf("\n");

	printf("\n");
	printf("后序遍历结果:");
	PostSearch(parent);
	printf("\n");

	printf("\n");
	printf("非递归前序遍历结果:");
	PreSearch2(parent);
	printf("\n");

	printf("\n");
	printf("非递归中序遍历结果:");
	MidSearch2(parent);
	printf("\n");

	printf("\n");
	printf("非递归后序遍历结果:");
	PostSearch2(parent);
	printf("\n");

	printf("\n");
	printf("层序遍历结果:");
	LevelSearch(parent);
	printf("\n");

	return 0;
}
