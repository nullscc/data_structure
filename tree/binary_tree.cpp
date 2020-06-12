// 先序遍历二叉树
#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

typedef int ElemType;

typedef struct Node{
	ElemType data;
	Node *lchild;
	Node *rchild;	
	
}Node, *pNode;

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

	printf("后序遍历结果:");
	PostSearch(parent);
	printf("\n");

	return 0;
}
