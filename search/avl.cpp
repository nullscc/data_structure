/* 二叉平衡树
AVL取名自发明者，和算法本身没什么直接联系
几个要点：
	1. 不要试图直接一次性将所有的BF扳正，要利用递归一层一层来处理，每层只处理自己的，这就是taller的作用
	2. 注意处理好单旋和双旋的情况即可(目录下有手推图)
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"../common.h"

#define LH 1	// 左高
#define EH 0	// 等高
#define RH -1	// 右高

typedef int ElemType;

typedef struct Node{
	ElemType data;
	Node *lchild;
	Node *rchild;	
	int BF;
	
}Node, *pNode;

void L_Rotate(pNode &T) {
	pNode R = T->rchild;
	T->rchild = R->lchild;
	R->lchild = T;
	T = R;
}

void R_Rotate(pNode &T) {
	pNode L = T->lchild;
	T->lchild = L->rchild;
	L->rchild = T;
	T = L;
}

// 只有两种情况，长在T的左子树的右边还是左边
void LeftBalance(pNode &T) {
	pNode L = T->lchild;	// NOTE: 插入结点前L本身的平衡因子必为0，不然就是没有把不平衡扼杀在摇篮里，整个算法也就不成立了
	
	if(L->BF == LH) {		// 长在左边，这时T和L的平衡因子同号，只需要T做单右旋即可
		T->BF = L->BF = EH;	// 一定要先调节好平衡因子再旋转，因为旋转过后T已经变了
		R_Rotate(T);
	} else {
		pNode LR = L->rchild;
		switch(LR->BF) {
			case LH:
				L->BF = EH;
				T->BF = RH;
				break;
			case EH:		// 这种情况其实就是LR的左右子树都无
				T->BF = L->BF = EH;
				break;
			case RH:
				L->BF = LH;
				T->BF = EH;
				break;
		}
		L_Rotate(T->lchild);		// NOTE: 这里不能用L变量，因为最终的结果是需要改变T->lchild，用L变量达不到效果
		R_Rotate(T);
	}
}

void RightBalance(pNode &T) {
	pNode R = T->rchild;
	
	if(R->BF == RH) {
		T->BF = R->BF = EH;
		L_Rotate(T);
	} else {
		pNode RL = R->lchild;
		switch(RL->BF) {		// NOTE: 这里的对称性有时间还是手动推一遍不要自己记忆和LeftBalance对称性，很容易出错
			case LH:
				R->BF = RH;
				T->BF = EH;
				break;
			case EH:
				T->BF = R->BF = EH;
				break;
			case RH:
				R->BF = EH;
				T->BF = LH;
				break;
		}
		R_Rotate(T->rchild);			// NOTE: 这里的对称性也有坑~
		pNode tmp = T;
		L_Rotate(T);
	}
}

Status InsertAVL(pNode &T, ElemType e, bool &taller) {
	if(!T) {
		pNode tmp = (pNode)malloc(sizeof(Node));
		tmp->BF = 0;
		tmp->data = e;
		tmp->lchild = tmp->rchild = NULL;
		taller = true;
		T = tmp;
		return OK;
	}
	if(e < T->data) {
		if(!InsertAVL(T->lchild, e, taller)) return ERROR;
		
		if(taller) {				// NOTE: 这里的taller其实是从刚新建结点后的那一层InserAVL返回来的，处理完后要将taller置为false，以免影响更上一层的InserAVL
			switch(T->BF) {			// NOTE: 如果到这里了说明T->lchild=NULL，说明在T的左结点插入了，所以应该检查T的平衡度
				case LH:
					LeftBalance(T);	// 这种情况统一在LeftBalance里面处理平衡因子
					taller = false; // 经过右旋后只矮不高，不然没什么意义了
					break;
				case EH:
					T->BF = LH;
					taller = true;	// NOTE: 这里T长高了，由于程序的递归特性，需要在递归的上一层处理长高的“后遗症”
					break;
				case RH:
					T->BF = EH;
					taller = false;
					break;
			}
		
		}
	} else if(e > T->data) {
		if(!InsertAVL(T->rchild, e, taller)) return ERROR;
		
		if(taller) {
			switch(T->BF) {
				case LH:
					T->BF = EH;
					taller = false;
					break;
				case EH:
					T->BF = RH;
					taller = true;
					break;
				case RH:
					RightBalance(T);
					taller = false;
					break;
			}
		
		}
	} else {
		taller = false;
		return ERROR;
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


int main() {
	pNode T = NULL;
	bool taller;
	int i;
	int a[10] = {3,2,1,4,5,6,7,10,9,8};
	for(i=0; i<10; i++) {
		InsertAVL(T, a[i], taller);
	}
	assert(T->data == 4);

	printf("中序遍历结果:");
	MidSearch(T);
	printf("\n");
	return 0;
}
