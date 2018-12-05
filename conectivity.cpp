#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAXVEX 20
typedef struct ArcNode
{
	int tailvex,headvex;
	char tailvexdata,headvexdata;
	int weight;
	struct ArcNode *hnextarc,*tnextarc;
}ArcNode;
typedef struct VertexNode
{
	char vexdata;
	ArcNode *head,*tail;
}VertexNode;
typedef struct 
{
	VertexNode vetex[MAXVEX];
	int vexnum;
	int arcnum;
}OrthList;
OrthList *G;
int mark[MAXVEX];
int count=0;
void Init()
{
	int i;
	for(i=1;i<MAXVEX;i++)
	{
		mark[i]=0;
	}
}
void CreatGraph()
{
	int n,i,j;
	ArcNode *p;
	G=(OrthList*)malloc(sizeof(OrthList));
	scanf("%d",&n);
	G->vexnum=n;
	scanf("%d",&G->arcnum);
	getchar();
	for(i=1;i<=n;i++)
	{
	    G->vetex[i].head=NULL;
		G->vetex[i].tail=NULL;
	    scanf("%c",&G->vetex[i].vexdata);
    }
    getchar();
	for(i=1;i<=G->arcnum;i++)
	{
		p=(ArcNode*)malloc(sizeof(ArcNode));
		fflush(stdin);
		p->tailvexdata=getchar();
		p->headvexdata=getchar();
		getchar();
		for(j=1;j<=G->vexnum;j++)
		{
			if(p->tailvexdata==G->vetex[j].vexdata)
			{
			p->tailvex=j;
			break;
	    	}
		}	
		for(j=1;j<=G->vexnum;j++)
		{
			if(p->headvexdata==G->vetex[j].vexdata)
			{
			p->headvex=j;
			break;
		}
		}	
		p->tnextarc=G->vetex[p->tailvex].tail;
		G->vetex[p->tailvex].tail=p;
		p->hnextarc=G->vetex[p->headvex].head;
		G->vetex[p->headvex].head=p;
	}
}

void DFS(int i)
{
	int a[MAXVEX],m=1,k,j,temp;
	ArcNode *p;
	if(count>G->vexnum)
	return ;
	p=G->vetex[i].tail;
	if(!mark[i])
	{
		mark[i]=1;
		count++;
	}
	if(p==NULL)
	return ;
    while(p!=NULL)
     {
   	  a[m]=p->headvex;
   	  p=p->tnextarc;
   	  m++;
     }
     for(k=1;k<m-1;k++)
     {
   	  for(j=k+1;j<m;j++)
   	  {
   		if(a[k]>a[j])
   		{
   			temp=a[k];
   			a[k]=a[j];
   			a[j]=temp;
		     }
	     }
       }
     for(i=1;i<m;i++)
     {
   	 if(!mark[a[i]])
   	 DFS(a[i]);
     }
}

int main()
{
	int i,j=0;
	ArcNode *p;
	CreatGraph();
	Init();
	for(i=1;i<=G->vexnum;i++)
	{
		if(!mark[i])
		{
			DFS(i);
		    p=G->vetex[1].head;
		    while(p!=NULL)
		    {
			 DFS(p->tailvex);
			 p=p->hnextarc;
		   }
		j++;
	   }
	}
	printf("%d",j);
 }
