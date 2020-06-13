// 中序遍历线索二叉树
#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
typedef int ElemType;

typedef struct Node{
	ElemType data;
	Node *lchild;
	Node *rchild;	
	bool ltag, rtag;
	
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
		pnode->ltag = false;
		pnode->rtag = false;
		
		Create(pnode->lchild);
		Create(pnode->rchild);
	}
	return OK;
}

Status print_elem(ElemType e) {
	printf("%c", e);
	return OK;
}

Status MidThread(pNode &p, pNode &pre) {
	if (!p) return OK;
	
	MidThread(p->lchild, pre);
	if (!p->lchild) {
		p->ltag = true;
		p->lchild = pre;
	}
	if (pre && !pre->rchild) {
		pre->rtag = true;
		pre->rchild = p;
	}
	pre = p;
	MidThread(p->rchild, pre);

	return OK;
}

Status CreateMidThread(pNode &p) {
	if (!p) return OK;
	pNode pre=NULL;		// NOTE: 这里保证中序遍历的第一个节点的前驱没有了
	MidThread(p, pre);
	pre->rchild = NULL;	// NOTE: 这里保证中序遍历的最后一个节点的后继没有了
	pre->rtag = true;
	return OK;
}

pNode FirstNode(pNode p) {
	while (!p->ltag) p = p->lchild; // 一直找到没有左子结点的结点
	return p;
}

pNode NextNode(pNode p) {
	if (!p->rtag) return FirstNode(p->rchild);
	else return p->rchild;
}

void SearchMidThreadRear(pNode p) {
	if (!p) return;

	p = FirstNode(p);		// 要先找到第一个
	while (p) {
		print_elem(p->data);
		p = NextNode(p);
	}
}

pNode LastNode(pNode p) {
	while (!p->rtag) p = p->rchild; // 一直找到没有右子结点的结点
	return p;
}

pNode PreNode(pNode p) {
	if (!p->ltag) return LastNode(p->lchild);
	else return p->lchild;
}

void SearchMidThreadFront(pNode p) {
	if (!p) return;

	p = LastNode(p);		// 要先找到最后一个
	while (p) {
		print_elem(p->data);
		p = PreNode(p);
	}
}


int main() {
	printf("请输入二叉树的元素:");

	pNode parent;
	Create(parent);
	printf("\n");
	
	printf("建立中序线索二叉树...\n");
	CreateMidThread(parent);
	printf("建立中序线索二叉树完毕。\n");

	printf("后继搜索中序线索二叉树:");
	SearchMidThreadRear(parent);
	printf("\n");

	printf("前驱搜索中序线索二叉树:");
	SearchMidThreadFront(parent);
	printf("\n");

	return 0;
}
