// 图的邻接多重链表（无向、无权）

#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"../queue/link_queue.cpp"

#define MAXSIZE 100

typedef struct TNode {
	int ivex;
	int jvex;
	TNode *ilink;
	TNode *jlink;
}TNode, *pTNode;

typedef struct {
	char data;
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
		g.vex[i].data = ch;
		g.vex[i].first = NULL;
		scanf("%c", &ch);
		i++;
	}
	g.vexnum = i;

	printf("\n");
	return OK;
}

Status GetEdge(Graph &g) {
	int i;
	int v1, v2;

	printf("请输入边信息, 格式为1,2 2,3(以1开始), 0,0代表结束:");
	scanf("%d,%d", &v1, &v2);
	i=0;
	while(v1 && v2) {
		pTNode p_tnode = (pTNode)malloc(sizeof(TNode));
		p_tnode->ivex = v1-1;
		p_tnode->jvex = v2-1;

		// NOTE: 这里不用像《大话数据结构》说的那样需要进行手动交错，那样实现就太麻烦了，在访问时进行判断即可
		p_tnode->ilink = g.vex[v1-1].first;		
		g.vex[v1-1].first = p_tnode;
		p_tnode->jlink = g.vex[v2-1].first;
		g.vex[v2-1].first = p_tnode;

		scanf("%d,%d", &v1, &v2);
		i++;
	}
	g.edgenum = i;

	printf("\n");
	return OK;
}

void visit(Graph &g, int v) {
	printf("%c ", g.vex[v].data);
}

void DFS(Graph &g, int v, bool *visited) {
	visit(g, v);
	visited[v] = true;
	pTNode p_t = g.vex[v].first;
	while(p_t) {
		// NOTE: 这里需要进行判断才能正确访问
		int next_v = p_t->ivex;
		if (p_t->ivex == v) next_v = p_t->jvex;
		
		if (!visited[next_v]) DFS(g, next_v, visited);
		
		// NOTE: 这里需要进行判断才能正确访问
		if (p_t->jvex == v) p_t = p_t->jlink;
		else p_t = p_t->ilink;
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
			int next_v = p_t->ivex;
			if (p_t->ivex == v) next_v = p_t->jvex;

			if (!visited[next_v]) {
				EnQueue(Q, next_v);
				visit(g, next_v);
				visited[next_v] = true;
			}

			if (p_t->jvex == v) p_t = p_t->jlink;
			else p_t = p_t->ilink;
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

// 数据使用《大话数据结构》p239(电子书p263), 图7-5-2
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

}
