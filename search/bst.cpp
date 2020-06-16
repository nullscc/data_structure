// 二叉排序树不能有相同的数值？ yes，但是可根据实际应用对数据的存储和逻辑做调整
// 注意删除结点的操作不要费力的去找要删除的结点的双亲结点，见相应的注释
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
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
Status Search(pNode &T, pNode f, pNode &p, ElemType e) {
	int ret;

	if(!T) {
		p = f;
		return ERROR;
	}

	if(T->data == e) {
		p = T;
		return OK;
	}

	if(e < T->data) {
		return Search(T->lchild, T, p, e);
	} else {
		return Search(T->rchild, T, p, e);
	}
}

Status Insert(pNode &T, ElemType e) {
	pNode s;
	if (!(Search(T, NULL, s, e))) {
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
	return OK;
}

Status print_elem(ElemType e) {
	printf("%d ", e);
	return OK;
}

Status MidSearch(pNode pnode) {
	if (!pnode) return OK;
	MidSearch(pnode->lchild);
	print_elem(pnode->data);
	MidSearch(pnode->rchild);
	return OK;
}

Status Delete(pNode &p) {
	pNode q, s;

	if(!p->rchild) {
		q = p;
		p = p->lchild;
		// NOTE: 这里很重要，看了好久才看懂，还以为大话数据结构和严蔚敏书写错了呢...
		// 实际上p本身是虽然是要删除的结点的地址，但是这个地址值是存放在其双亲结点的lchild(或rchild)域里面，又因为这里传过来的p是引用，所以相当于直接更改了双亲结点的lchild(或rchild)域
		// 所以根本不用费力去找要删除结点的双亲结点
		free(q);
	} else if(!p->lchild) {
		q = p;
		p = p->rchild;
		free(q);
	} else {
		q = p;
		s = p->lchild;
		while(s->rchild) {		// NOTE: 这里就要找双亲结点了，最终q为双亲结点，s为要删除的结点
			q=s; s=s->rchild;
		}
		p->data = s->data;
		if(q!=p) q->rchild = s->lchild;		// 如果要替换的结点有右子树
		else q->lchild = s->lchild;			// 如果要替换的结点没有右子树
		free(s);
	}
	return OK;
}

Status DeleteBST(pNode &T, ElemType e) {
	if (!T) return ERROR;
	if(e == T->data) return Delete(T);
	else if(e < T->data) return DeleteBST(T->lchild, e);
	else return DeleteBST(T->rchild, e);
}


int main() {
	int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
	int i;
	pNode T=NULL;
	for(i=0; i<10; i++) {
		assert(Insert(T, a[i]));
	}

	printf("创建排序树完成以后的数据:");
	MidSearch(T);
	printf("\n");

	pNode p;
	Search(T, NULL, p, 99); 
	
	DeleteBST(T, 62);
	printf("删除一个数据以后树的数据:");
	MidSearch(T);
	printf("\n");
	
	return 0;
}
