#ifndef STATE_H_
#define STATE_H_
#include "pxl.h"
#include "suan_png.h"

#define MAXV 10000

typedef struct ANode
{
    int adjvex;
    struct ANode *nextarc;
    int weight;
    int flag;
} ArcNode;
typedef struct Vnode
{
    int industry;
    ArcNode *firstarc;
} VNode;
typedef struct
{
    VNode adjlist[MAXV];
    int n, e;
} AdjGraph; // 邻接表
struct State
{
    AdjGraph *G;
    int pre[10000]; // 标记最短路上每个点的前驱
};

// function
void init_State(struct State *s);
void delete_State(struct State *s);
void assign(struct State *a, struct State *b);
void parse(struct State *s, struct PNG *p);
int solve1(struct State *s);
int solve2(struct State *s);

#endif
