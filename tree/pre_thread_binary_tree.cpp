// 先序线索二叉树
// 先序线索二叉树没法找到结点的前驱，因为相当于是要找二叉树的双亲
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

Status PreThread(pNode &p, pNode &pre) {
	if (!p) return OK;
	// NOTE: 由于是先访问根节点后访问左子结点，所以这里不能对p->lchild赋值，不然会造成死循环
	if (pre && !pre->rchild) {
		pre->rtag = true;
		pre->rchild = p;
	}
	pre = p;

	PreThread(p->lchild, pre);
	PreThread(p->rchild, pre);

	return OK;
}

Status CreatePreThread(pNode &p) {
	if (!p) return OK;
	pNode pre=NULL;
	PreThread(p, pre);
	pre->rchild = NULL;	// NOTE: 这里保证中序遍历的最后一个节点的后继没有了
	pre->rtag = true;
	return OK;
}

pNode NextNode(pNode p) {
	if (!p->rtag) {
		if (p->lchild) return p->lchild;
		else return p->rchild;
	}
	else return p->rchild;
}

// 先序二叉树没法找到前驱结点
void SearchPreThreadRear(pNode p) {
	if (!p) return;

	while (p) {
		print_elem(p->data);
		p = NextNode(p);
	}
}

int main() {
	printf("请输入二叉树的元素:");

	pNode parent;
	Create(parent);
	printf("\n");
	
	printf("建立先序线索二叉树...\n");
	CreatePreThread(parent);
	printf("建立先序线索二叉树完毕。\n");

	printf("后继搜索先序线索二叉树:");
	SearchPreThreadRear(parent);
	printf("\n");

	return 0;
}
