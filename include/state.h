#ifndef STATE_H_
#define STATE_H_
#include "pxl.h"
#include "suan_png.h"

#define MAXV 10000 // 最大节点数

typedef struct ANode
{
    int adjvex;            // 边的目标节点
    struct ANode *nextarc; // 下一条边
    int weight;            // 边的权值
    int flag;              // 标记边是否删除
} ArcNode;
typedef struct Vnode
{
    int industry;      // 该节点的发达程度
    ArcNode *firstarc; // 该节点连接的第一条边
} VNode;
typedef struct
{
    VNode adjlist[MAXV]; // 节点列表
    int n, e;
} AdjGraph; // 邻接表
struct State
{
    AdjGraph *G;   // 邻接表
    int pre[MAXV]; // 标记最短路上每个点的前驱
};

// function
void init_State(struct State *s);
void delete_State(struct State *s);
void assign(struct State *a, struct State *b);
void parse(struct State *s, struct PNG *p);
int solve1(struct State *s);
int solve2(struct State *s);

#endif
