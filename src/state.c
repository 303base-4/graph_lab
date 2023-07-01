#include "state.h"
#include "pxl.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int industry(struct PXL *p) // 计算像素p对应的发达程度
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

void init_State(struct State *s) // 初始化s,其中pre数组初始化为1，adjlist[].firstarc初始化为NULL
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
void delete_State(struct State *s) // 释放s中元素的内存
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
void parse(struct State *s, struct PNG *p) // 利用p中的信息建图，存放于s中
{
    struct PXL *pxl;                     // pxl用于临时存储像素指针
    int x = 6, y = 4;                    // 第一个点的中心点所在座标。x为纵座标，y为横座标
    int m, count = 0;                    // m用于临时存储发达程度，count用于点计数
    int no[p->height + 1][p->width + 1]; // 用no[x][y]表示像素(x,y)对应的点的编号
    memset(no, 0, sizeof(no));
    // 先建点
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
            y = y + 4; // 每次向右移动半格，以保证探测精度
        }
        y = 0;
        x = x + 8;
    }
    const int MOV[3][2] = {
        {-8, 4},
        {0, 8},
        {8, 4}}; // MOV数组用于探测目的节点。对于每个节点，探测其右上、右、右下三个节点，如果存在则双向建边
    s->G->n = count;
    // 接下来插入边
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
                    s->G->e += 2;
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
    // TODO
    return 0;
}
int solve2(struct State *s)
{
    // TODO
    return 0;
}
