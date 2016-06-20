//Tarjan's strongly connected component algorithm

#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define MAX_VERTEX_NUM 100

//data structure of adjlist
typedef struct ArcNode{ // arc information
	int adjvex; 
	ArcNode* nextarc;
}ArcNode;

typedef struct VNode{ //vertex information
	string data;
	ArcNode* firstarc;
}VNode,Adjlist[MAX_VERTEX_NUM];

typedef struct{
	Adjlist vertices;
	int arcnum, vexnum;
}ALGraph;

int LocateVex(ALGraph G, string u)  
{  
    for(int i=0; i<G.vexnum; i++)  
        if(G.vertices[i].data==u)  
            return i;  
		return -1;  
}  

//structure the graph

void CreateDG(ALGraph &G){
	string v1, v2;
	int i, j, k;
	cout<<"Please enter the number of vertices and arcs..."<<endl;
	cin>>G.vexnum>>G.arcnum;
	
	cout<<"Please enter the vertices..."<<endl;
	for(i=0; i<G.vexnum; i++){
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;
	}
	
	cout<<"Please enter the arcs..."<<endl;
	for(k=0; k<G.arcnum; k++){
		cin>>v1>>v2;
		i= LocateVex(G, v1);
		j= LocateVex(G, v2);
		
		//directed graph
		//structure the arc i->j
		ArcNode* arc=new ArcNode;
		arc->adjvex= j;
		arc->nextarc= G.vertices[i].firstarc;
		G.vertices[i].firstarc= arc;
	}
}

//find the strongly connected component

int count=0;
int visited[MAX_VERTEX_NUM];
int lowlink[MAX_VERTEX_NUM];
stack<int> s;

//find the articulation points from vertex v0 using DFS
void SCCom(ALGraph G, int v0){
	int min, e;
	ArcNode* p;
	visited[v0]=min=++count; // v0 is the countth vertex being visited
	s.push(v0);
	for(p=G.vertices[v0].firstarc; p; p=p->nextarc){
		e=p->adjvex;
		if(visited[e]==0){ // e has not been visited
			SCCom(G, e);
			if(min>lowlink[e])
				min=lowlink[e];
		}
		else if(min>visited[e])  // e is an ancestor of v0
			min=visited[e];	
	}
	lowlink[v0]=min;
	if(lowlink[v0]==visited[v0]){
		while(s.top()!=v0){
			cout<<G.vertices[s.top()].data<<" ";
			s.pop();
		}
		cout<<G.vertices[s.top()].data<<endl;
		s.pop();
	}
	
}
void FindSCCom(ALGraph G){
	for(int i=0; i<G.vexnum; i++){
		visited[i]=0;
	}
	for(i=0; i<G.vexnum; i++)
		if(visited[i]==0)
			SCCom(G,i);
}
void main(){
	ALGraph g;
	CreateDG(g);
	cout<<"The Strongly Connected Component are as follow"<<endl;
	FindSCCom(g);
}


