#include "state.h"
#include "pxl.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int industry(struct PXL *p)
{
    int m = 255 * 255 * 3 - p->red * p->red - p->blue * p->blue - p->green * p->green;
    return m;
}

void insert(struct State *s, int x, int y, int w) // 在s中，插入x指向y权值为w的边
{
    ArcNode *p;
    p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = y;
    p->weight = w;
    p->flag = 1;
    p->nextarc = s->G->adjlist[x].firstarc;
    s->G->adjlist[x].firstarc = p;
}

void init_State(struct State *s)
{
    s->G = (AdjGraph *)malloc(sizeof(AdjGraph));
    for (int i = 0; i < MAXV; i++)
    {
        s->G->adjlist[i].firstarc = NULL;
        s->pre[i] = -1;
    }
    s->G->n = 0;
    s->G->e = 0;
}
void delete_State(struct State *s)
{
    for (int i = 1; i <= s->G->n; i++)
    {
        ArcNode *p, *t;
        p = s->G->adjlist[i].firstarc;
        while (p != NULL)
        {
            t = p;
            p = p->nextarc;
            free(t);
        }
    }
    free(s->G);
}
void parse(struct State *s, struct PNG *p)
{
    struct PXL *pxl;
    int x = 6, y = 4;
    int m, count = 0;
    int no[p->height + 1][p->width + 1];
    memset(no, 0, sizeof(no));
    while (x < p->height)
    {
        while (y < p->width)
        {
            pxl = get_PXL(p, y, x);
            m = industry(pxl);
            if (m != 0 && m != 255 * 255 * 3)
            {
                s->G->adjlist[++count].industry = m;
                no[x][y] = count;
            }
            y = y + 4;
        }
        y = 0;
        x = x + 8;
    }
    const int MOV[3][2] = {{-8, 4}, {0, 8}, {8, 4}};
    s->G->n = count;
    x = 6, y = 4;
    while (x < p->height)
    {
        while (y < p->width)
        {
            int no1 = no[x][y];
            if (no1 != 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    int x1 = x + MOV[i][0], y1 = y + MOV[i][1];
                    if (x1 < 0 || x1 >= p->height || y1 < 0 || y1 >= p->width || no[x1][y1] == 0)
                        continue;
                    int no2 = no[x1][y1];
                    insert(s, no1, no2, s->G->adjlist[no2].industry);
                    insert(s, no2, no1, s->G->adjlist[no1].industry);
                }
            }
            y += 4;
        }
        y = 0;
        x += 8;
    }
}
int solve1(struct State *s)
{
    int d[10000];
    int vis[10000]={0};
    int n=s->G->n;
    memset(d,0x3f,sizeof(d));
    d[1]=0;
    for(int i=1;i<=n;i++)
    {
	int mind=0xffffff0;
	int u=0;
	for(int j=1;j<=n;j++)
	{
	    if(vis[j]==0&&d[j]<mind)
	    {
		mind=d[j];
		u=j;
	    }
	}
	vis[u]=1;
	ArcNode *p=s->G->adjlist[u].firstarc;
	while(p!=NULL)
	{
	    int v=p->adjvex;
	    if(d[v]>d[u]+p->weight)
	    {
		d[v]=d[u]+p->weight;
		s->pre[v]=u;
	    }
	    p=p->nextarc;
	}
    }
    return d[n];
}
int solve_( struct State *s){
    int d[10000];
    int vis[10000]={0};
    int mind;
    int n=s->G->n;
    memset(d,0x3f,sizeof(d));
    d[1]=0;
    for(int i=1;i<=n;i++)
    {
	int mind=0xffffff0;
	int u=0;
	for(int j=1;j<=n;j++)
	{
	    if(vis[j]==0&&d[j]<mind)
	    {
		mind=d[j];
		u=j;
	    }
	}
	vis[u]=1;
	ArcNode *p=s->G->adjlist[u].firstarc;
	while(p!=NULL)
	{
	    int v=p->adjvex;
	    if(d[v]>d[u]+p->weight&&p->flag)
	    {
		d[v]=d[u]+p->weight;
	    }
	    p=p->nextarc;
	}
    }
    return d[n];



}

void del(struct State *s,int v,int u){
    ArcNode *p=s->G->adjlist[v].firstarc;
    while(p!=NULL){
        if(p->adjvex==u){
            p->flag=0;
            return;
        }
        p=p->nextarc;
    }
}

void connect(struct State *s,int v,int u){
    ArcNode *p=s->G->adjlist[v].firstarc;
    while(p!=NULL){
        if(p->adjvex==u){
            p->flag=1;
            return;
        }
        p=p->nextarc;
    }
}

int solve2(struct State *s){
    int min1=solve1(s);
    int min2=2147483644;
    for(int i=s->G->n;i>1;i=s->pre[i]){
        del(s,i,s->pre[i]);
        del(s,s->pre[i],i);
        int tmp=solve_(s);
        if(tmp<min2&&tmp>min1){
            min2=tmp;
        }
        connect(s,i,s->pre[i]);
        connect(s,s->pre[i],i);
    }
    return min2;
    
}
