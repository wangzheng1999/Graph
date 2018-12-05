
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAXVEX 20
typedef struct ArcNode
{
	int tailvex, headvex;
	char tailvexdata, headvexdata;
	int weight;
	struct ArcNode *hnextarc, *tnextarc;
}ArcNode;
typedef struct VertexNode
{
	char vexdata;
	int InDegree;
	int OutDegree;
	ArcNode *head, *tail;
}VertexNode;
typedef struct
{
	VertexNode vetex[MAXVEX];
	int vexnum;
	int arcnum;
}OrthList;
typedef struct stack
{
	int data;
	struct stack *next;
}Stack;
Stack *InitStack()
{
	Stack *p;
	p = (Stack*)malloc(sizeof(Stack));
	p->next = NULL;
	return p;
}
void Push(Stack *p, int q)
{
	Stack *m;
	m = (Stack*)malloc(sizeof(Stack));
	m->data = q;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = m;
	m->next = NULL;
}
int Pop(Stack *p)
{
	Stack *q;
	q = p->next;
	if (q != NULL)
		p->next = q->next;
	return q->data;
}
OrthList *G;
int mark[MAXVEX], sign[MAXVEX];
int count = 0;
void Init()
{
	int i;
	for (i = 1; i<MAXVEX; i++)
	{
		mark[i] = 0;
		sign[i] = 0;
	}
}
void CreatGraph()
{
	int n, i, j;
	ArcNode *p;
	G = (OrthList*)malloc(sizeof(OrthList));
	scanf("%d", &n);
	G->vexnum = n;
	scanf("%d", &G->arcnum);
	getchar();
	for (i = 1; i <= n; i++)
	{
		G->vetex[i].head = NULL;
		G->vetex[i].tail = NULL;
		scanf("%c", &G->vetex[i].vexdata);
	}
	getchar();
	for (i = 1; i <= G->arcnum; i++)
	{
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->tailvexdata = getchar();
		p->headvexdata = getchar();
		getchar();
		for (j = 1; j <= G->vexnum; j++)
		{
			if (p->tailvexdata == G->vetex[j].vexdata)
			{
				p->tailvex = j;
				break;
			}
		}
		for (j = 1; j <= G->vexnum; j++)
		{
			if (p->headvexdata == G->vetex[j].vexdata)
			{
				p->headvex = j;
				break;
			}
		}
		p->tnextarc = G->vetex[p->tailvex].tail;
		G->vetex[p->tailvex].tail = p;
		p->hnextarc = G->vetex[p->headvex].head;
		G->vetex[p->headvex].head = p;
	}
}
void InDegree()
{
	int i;
	ArcNode *p;
	for (i = 1; i <= G->vexnum; i++)
	{
		G->vetex[i].InDegree = 0;
		p = G->vetex[i].head;
		while (p != NULL)
		{
			p = p->hnextarc;
			G->vetex[i].InDegree++;
		}
	}
}
void OutDegree()
{
	int i;
	ArcNode *p;
	for (i = 1; i <= G->vexnum; i++)
	{
		G->vetex[i].OutDegree = 0;
		p = G->vetex[i].tail;
		while (p != NULL)
		{
			p = p->tnextarc;
			G->vetex[i].OutDegree++;
		}
	}
}
void DFS(int i)
{
	int a[MAXVEX], m = 1, k, j, temp;
	ArcNode *p;
	if (count>G->vexnum)
		return;
	p = G->vetex[i].tail;
	if (!mark[i])
	{
		printf("%c", G->vetex[i].vexdata);
		mark[i] = 1;
		count++;
	}
	while (p != NULL)
	{
		a[m] = p->headvex;
		p = p->tnextarc;
		m++;
	}
	for (k = 1; k<m - 1; k++)
	{
		for (j = k + 1; j<m; j++)
		{
			if (a[k]>a[j])
			{
				temp = a[k];
				a[k] = a[j];
				a[j] = temp;
			}
		}
	}
	for (i = 1; i<m; i++)
	{
		if (!mark[a[i]])
			DFS(a[i]);
	}
}
void BFS(int i)
{
	int a[MAXVEX], m, t, k, j, temp;
	Stack *h;
	ArcNode *p;
	h = InitStack();
	p = G->vetex[i].tail;
	Push(h, i);
	sign[i] = 1;
	while (h->next != NULL)
	{
		t = Pop(h);
		printf("%c", G->vetex[t].vexdata);
		p = G->vetex[t].tail;
		m = 1;
		while (p != NULL)
		{
			a[m] = p->headvex;
			p = p->tnextarc;
			m++;
		}
		for (k = 1; k<m - 1; k++)
		{
			for (j = k + 1; j<m; j++)
			{
				if (a[k]>a[j])
				{
					temp = a[k];
					a[k] = a[j];
					a[j] = temp;
				}
			}
		}
		for (k = 1; k<m; k++)
		{
			if (!sign[a[k]])
			{
				Push(h, a[k]);
				sign[a[k]] = 1;
			}
		}
	}
}
int main()
{
	int i;
	CreatGraph();
	InDegree();
	OutDegree();
	for (i = 1; i <= G->vexnum; i++)
		printf("%c %d %d %d\n", G->vetex[i].vexdata, G->vetex[i].OutDegree, G->vetex[i].InDegree, G->vetex[i].OutDegree + G->vetex[i].InDegree);
	Init();
	DFS(1);
	printf("\n");
	BFS(1);
}


