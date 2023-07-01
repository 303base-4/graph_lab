#ifndef STATE_H_
#define STATE_H_
#include "suan_png.h"
#include "pxl.h"
#define	MAXV 100000

typedef struct ANode
{	int adjvex;				
	struct ANode *nextarc;//	
	int weight;			
} ArcNode;					
typedef struct Vnode
{	InfoType info;			
	int count;				
	ArcNode *firstarc;		
} VNode;					
typedef struct 
{	VNode adjlist[MAXV];	
	int n,e;					
} AdjGraph;					
struct State {
    AdjGraph *G;
    int pre[10000];
};

// function
void init_State(struct State *s);
void delete_State(struct State *s);
void assign(struct State *a, struct State *b);
void parse(struct State *s, struct PNG *p);
int solve1(struct State *s);
int solve2(struct State *s);

#endif
