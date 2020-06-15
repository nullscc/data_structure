// 搞不动两个问题: 1. 多条关键路径怎么办，能输出吗？ 2. 算法中的栈可以改成队列吗？
#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"../stack/stack_sq.cpp"
#include"../queue/link_queue.cpp"

#define MAXSIZE 100

typedef struct TNode{
	int v;
	int weight;
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

Status Connect(Graph &g, int i, int j, int weight) {
	pTNode p_t = (pTNode)malloc(sizeof(TNode));
	p_t->v = j;
	p_t->weight = weight;
	p_t->next = g.vex[i].first;
	g.vex[j].in++;
	
	g.vex[i].first = p_t;		// NOTE: 由于边没有顺序要求，所以直接插入即可
	return OK;
}

Status GetEdge(Graph &g) {
	int i;
	int v1, v2, weight;

	printf("请输入边信息, 格式为1,2 2,3(以1开始), 0,0代表结束:");
	scanf("%d,%d,%d", &v1, &v2, &weight);
	i=0;
	while(v1 && v2 && weight) {
		Connect(g, v1-1, v2-1, weight);
		scanf("%d,%d,%d", &v1, &v2, &weight);
		i++;
	}
	g.edgenum = i;

	printf("\n");
	return OK;
}

Status TopoSort(Graph &g, SqStack &SC, int *etv) {
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
		Push(SC, v);

		pTNode p=g.vex[v].first;
		while(p) {
			if(!(--g.vex[p->v].in)) Push(S, p->v);

			if(etv[v]+p->weight > etv[p->v]) {		// 这里对连接到p-v的每个进行遍历，找到一条时间消耗最长的路径，就是这个事件的最早开始时间
				etv[p->v] = etv[v] + p->weight;
			}
			p = p->next;
		}
	}
	if(count<g.vexnum) return ERROR;
	return OK;

}

Status CriticalPath(Graph &g) {
	// 主要是为了计算这几个值
	int ete, lte;
	int etv[MAXSIZE], ltv[MAXSIZE];
	SqStack SC;
	InitStack(SC);

	int i;
	for(i=0; i<g.vexnum; i++) {
		etv[i] = 0;
	}

	if (!TopoSort(g, SC, etv)) return ERROR;


	for(i=0; i<g.vexnum; i++) {
		ltv[i] = etv[g.vexnum-1];	// 由于最后一个结点是终点，所以耗费时间肯定最长，事件的最晚发生时间不能再最后一个事件已经发生了还没发生，所以最多可以等于最后一个时间的最早发生时间
	}

	int v;
	while(!IsEmpty(SC)) {
		Pop(SC, v);
		pTNode p = g.vex[v].first;
		while(p) {
			if(ltv[p->v]-p->weight < ltv[v]) {
				ltv[v] = ltv[p->v] - p->weight;		// NOTE: 为什么？
			}
			p = p->next;
		}
	}
	for(i=0; i<g.vexnum; i++) {
		pTNode p = g.vex[i].first;
		while(p) {
			ete = etv[i];
			lte = ltv[p->v]-p->weight;				// NOTE: 为什么？
			if(ete == lte) {
				printf("V%c->V%c 耗费时间:%d\n", g.vex[i].e, g.vex[p->v].e, p->weight);
			}
			p = p->next;
		}
	}

	return OK;
}

// 数据使用《大话数据结构》p305(电子书p281), 图7-9-4
// 执行 a.out < data5 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);

	printf("\n关键路径结果为:\n");

	CriticalPath(g);
	
	return 0;
}
