#include <iostream>
#include <string>
using namespace std;

#define MAX_VERTEX_NUM 13

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
		
		//undirected graph
		//structure the arc i->j
		ArcNode* arc=new ArcNode;
		arc->adjvex= j;
		arc->nextarc= G.vertices[i].firstarc;
		G.vertices[i].firstarc= arc;
		//structure the arc j->i
		arc=new ArcNode;
		arc->adjvex= i;
		arc->nextarc= G.vertices[j].firstarc;
		G.vertices[j].firstarc= arc;
	}
}

//find the articulation points

int count;
int visited[MAX_VERTEX_NUM];
int lowlink[MAX_VERTEX_NUM];

//find the articulation points from vertex v0 using DFS

void DFSArticul(ALGraph G, int v0){
	int min, e;
	ArcNode* p;
	visited[v0]= min= ++count; // v0 is the countth vertex being visited
	
	for(p=G.vertices[v0].firstarc; p; p=p->nextarc){
		e=p->adjvex;
		if(visited[e]==0){ // e has not been visited
			DFSArticul(G, e); // find the articulation points from vertex e using DFS, acquire the lowlink of e before return
			if(lowlink[e]<min) //e has other subtrees
				min=lowlink[e];
			if (lowlink[e]>=visited[v0]) // e is only connected with v0, then v0 is an articulation point
				cout<<G.vertices[v0].data<<" ";	
		}
		else if(visited[e]<min) // e is an ancestor of v0
			min=visited[e];	
	}
	lowlink[v0]=min;
}

void FindArticul(ALGraph G){
	int i, v;
	ArcNode* p;
	count= 1;
	visited[0]=1; // begin from the first vertex
	for(i=1; i<G.vexnum; i++)
		visited[i]= 0; // initialize
	p= G.vertices[0].firstarc;
	v= p->adjvex;
	DFSArticul(G, v);
	if(count<G.vexnum){ //means the root vertex has other subtrees, then the root is an articulation point
		cout<<G.vertices[0].data<<" ";
		while(p->nextarc){
			p= p->nextarc;
			v= p->adjvex;
			if(visited[v]==0)
				DFSArticul(G, v);		
		}
	}
}

void main(){
	ALGraph g;
	CreateDG(g);
	
	cout<<"The articulation points are as follow"<<endl;
	FindArticul(g);
	cout<<endl;
}


