#include "state.h"

int industry(struct PXL *p){
	int m=255*255*3-p->red*p->red-p->blue*p->blue-p->green*p->green;
	return m;
}

void insert(struct State *s,int x,int y,int w){
	ArcNode *p;
	p=(ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex=y;
	p->weight=w;
	p->nextarc=s->G->adjlist[x].firstarc;
	s->G->adjlist[x].firstarc=p;
}

void init_State(struct State *s) {
    for (int i=0;i<MAXV;i++){
    	s->G->adjlist[i].firstarc=NULL;
    	pre[i]=-1;
	}
	s->G->n=0;
	s->G->e=0;
	
}
void delete_State(struct State *s) {
	
	 
}
void parse(struct State *s, struct PNG *p) {
    struct PNG *p1;
	struct PXL *p2;
	int x=4,y=6;
	int m,count=0;
	int _indstury[10000];
	init(p1);
	init_pxl1(p2);
    load(p1,file_name);//
    p2=get_PXL(p,x,y){
    	m=industry(p2);
    	if(m!=0&&y!=255*255*3){
    		_indstury[count+1]=m;
    		count++;
		}
		y=y+4;
	}
    while(x<=p1->height){
       	while(y<=p1->weight){
    		p2=get_PXL(p,x,y){
    			m=industry(p2);
    			if(m!=0&&y!=255*255*3){
    				_indstury[count+1]=m;
    				insert(s,count,count+1,_indstury[count+1]);  //没考虑除了横向相邻的其它路径 
    				insert(s,count+1,count,_industry[count]);
    				count++;
				}
				y=y+4;
			}
		}
		y=0;
		x=x+8;
	}
	s->G->n=count;
	delete_PNG(p1);
	free(p2);
}
int solve1(struct State *s) {
    // TODO
    return 0;
}
int solve2(struct State *s) {
    // TODO
    return 0;
}
