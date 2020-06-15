// 拓扑排序: 循环找到入度为0的点并将以这个结点为弧尾的弧删除
// NOTE: 算法过程很简单，用栈和队列均可
// 邻接表，有向图，无权

#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"../stack/stack_sq.cpp"

#define MAXSIZE 100

typedef struct TNode{
	int v;
	TNode *next;
}TNode, *pTNode;

typedef struct {
	int in;			// 入度
	char e;
	pTNode first;
}Vex, *pVex;

typedef struct {
	Vex vex[MAXSIZE];
	int vexnum, edgenum;
}Graph;

Status GetVex(Graph &g) {
	printf("请输入顶点信息, 以空格分隔:");
	char ch;
	scanf("%c", &ch);
	int i=0;
	while(ch && ch != '\n') {
		g.vex[i].e = ch;
		g.vex[i].first = NULL;
		g.vex[i].in = 0;
		scanf("%c", &ch);
		i++;
	}
	g.vexnum = i;
	g.edgenum = 0;

	printf("\n");
	return OK;
}

Status Connect(Graph &g, int i, int j) {
	pTNode p_t = (pTNode)malloc(sizeof(TNode));
	p_t->v = j;
	p_t->next = g.vex[i].first;
	g.vex[j].in++;
	
	g.vex[i].first = p_t;		// NOTE: 由于边没有顺序要求，所以直接插入即可
	return OK;
}

Status GetEdge(Graph &g) {
	int i;
	int v1, v2;

	printf("请输入边信息, 格式为1,2 2,3(以1开始), 0,0代表结束:");
	scanf("%d,%d", &v1, &v2);
	i=0;
	while(v1 && v2) {
		Connect(g, v1-1, v2-1);
		scanf("%d,%d", &v1, &v2);
		i++;
	}
	g.edgenum = i;

	printf("\n");
	return OK;
}

Status TopoSort(Graph &g) {
	SqStack S;
	InitStack(S);
	
	int i, count=0;
	for(i=0; i<g.vexnum; i++) {
		if(!g.vex[i].in) Push(S, i);
	}

	while(!IsEmpty(S)) {
		int v;
		Pop(S, v);
		count++;
		printf("V%d ", g.vex[v].e-65);

		pTNode p=g.vex[v].first;
		while(p) {
			if(!(--g.vex[p->v].in)) Push(S, p->v);
			p = p->next;
		}
	}
	printf("\n");
	if(count<g.vexnum) return ERROR;
	return OK;

}

// 数据使用《大话数据结构》p296(电子书p272), 图7-8-2
// 执行 a.out < data4 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);
	printf("0的入度为:%d\n", g.vex[0].in);
	printf("8的入度为:%d\n", g.vex[8].in);

	printf("拓扑排序结果为:");
	int r = TopoSort(g);
	if(!r) printf("oh, shit! 存在环，工程进行不下去啦\n");
	else printf("good，不存在环\n");
	
	return 0;
}
