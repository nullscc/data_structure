/*
搞懂几个问题: 
1. 多条关键路径怎么办，能输出吗？ 
	能输出，看data6的数据，算法找的是关键活动(由于是AOE，即是边)，所以所有的关键的边都能找出来
2. 算法中的栈可以改成队列吗？
	不可以，改成队列的话ltv算不对，导致算法出错
3. 算法中的etv, ltv, ete, lte分别怎么算出来的？
	见下面的注释
4. 算法有一个有点违背常识的地方(理解这个非常重要):
	终点事件的最早发生时间=终点事件的最晚发生时间；关键在于理解: ltv[g.vexnum-1]为什么等于etv[g.vexnum-1]；主要是因为终点的最早发生时间其实就是耗时最长的路径了，所以终点的最晚发生时间就是最早能发生的时间，说起来很奇怪，用数据 v0,v1,2 v0,v2,2 v1,v3,5 v2,v3,2就知道了，etv[3]的值不是4而是7
	}

*/
#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"../stack/stack_sq.cpp"

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

			if(etv[v]+p->weight > etv[p->v]) {		// NOTE: 顺推，这里对连接到p-v的每个进行遍历，找到一条时间消耗最长的路径，就是这个事件的最早开始时间
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
		ltv[i] = etv[g.vexnum-1];	// NOTE: 这个语句有两个目的，1. 将ltv[0..g.vexnum-1]置为最大的数，好在计算ltv时比小 2. 将ltv[g.vexnum-1]
									// 其实关键在于理解: ltv[g.vexnum-1]为什么等于etv[g.vexnum-1]；其实主要是因为终点的最早发生时间其实就是耗时最长的路径了，所以终点的最晚发生时间就是最早能发生的时间，说起来很奇怪，用数据 v0,v1,2 v0,v2,2 v1,v3,5 v2,v3,2就知道了，etv[3]的值不是4而是7
	}

	int v;
	while(!IsEmpty(SC)) {			// NOTE: 如果换成队列，这里的ltv会算不对；因为ltv必须是从终点往源头逆推才能算出来
		Pop(SC, v);					// 这里第一个pop出来的就是终点
		pTNode p = g.vex[v].first;
		while(p) {
			if(ltv[p->v]-p->weight < ltv[v]) {
				ltv[v] = ltv[p->v] - p->weight;		// NOTE: 为什么？逆推，画出两个从v出发到p->v终止的结点就知道了；取最小的原因在于需要预留足够长的时间给最需要时间的那个活动
			}
			p = p->next;
		}
	}
	for(i=0; i<g.vexnum; i++) {
		pTNode p = g.vex[i].first;
		while(p) {
			ete = etv[i];
			lte = ltv[p->v]-p->weight;				// NOTE: 为什么？ 逆推，其实是按递推关系来算的，以vk->vj为例，这个活动的最晚发生时间也要在vj的最晚发生时间减去vk->vj这个活动所花费的时间
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
// 执行 a.out < data6 看有两条关键路径的情况
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);

	printf("\n关键路径结果为:\n");

	CriticalPath(g);
	
	return 0;
}
