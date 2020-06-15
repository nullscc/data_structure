// 邻接表，有向图，无权

#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"../queue/link_queue.cpp"

#define MAXSIZE 100

typedef struct TNode{
	int v;
	TNode *next;
}TNode, *pTNode;

typedef struct {
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

void visit(Graph &g, int v) {
	printf("%c ", g.vex[v].e);
}

void DFS(Graph &g, int v, bool *visited) {
	visit(g, v);
	visited[v] = true;
	pTNode p_t = g.vex[v].first;
	while(p_t) {
		if (!visited[p_t->v]) DFS(g, p_t->v, visited);
		p_t = p_t->next;
	}
}

void DFSSearch(Graph &g) {
	int i;
	bool *visited = (bool *)malloc(sizeof(bool)*g.vexnum);
	for(i=0; i<g.vexnum; i++) {
		if(!visited[i]) {
			DFS(g, i, visited);
		}
	}
	free(visited);
}

void BFS(Graph &g, int v, bool *visited, Queue &Q) {
	EnQueue(Q, v);
	visited[v] = true;
	visit(g, v);

	pTNode p_t;
	while(!QIsEmpty(Q)) {
		DeQueue(Q, v);

		p_t = g.vex[v].first;
		while(p_t) {
			if (!visited[p_t->v]) {
				EnQueue(Q, p_t->v);
				visit(g, p_t->v);
				visited[p_t->v] = true;
			}
			p_t = p_t->next;
		}
	}
}

void BFSSearch(Graph &g) {
	int i;
	Queue Q;
	InitQueue(Q);

	bool *visited = (bool *)malloc(sizeof(bool)*g.vexnum);
	for(i=0; i<g.vexnum; i++) {
		if(!visited[i]) {
			BFS(g, i, visited, Q);
		}
	}
	free(visited);
}

// 数据使用《大话数据结构》p239(电子书p263), 图7-5-2，只不过将其改成了有向图
// 执行 a.out < data 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);
	
	printf("深度优先搜索结果:");
	DFSSearch(g);
	printf("\n");

	printf("广度优先搜索结果:");
	BFSSearch(g);
	printf("\n");

	return 0;
}
