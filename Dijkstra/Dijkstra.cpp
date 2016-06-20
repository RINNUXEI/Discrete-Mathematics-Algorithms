#include<iostream>
#include<string>
#include<stack>
using namespace std;

#define MAX_VERX_NUM 100
#define INFINITE 10000

/*typedef struct Arc{
	int adjlist;
	Arc *next;
	int weight;
}Arc;
*/

typedef struct Side{
	int adjvex;
	Side *next;
	int weight;
}Side;

typedef struct Node{
	string data;
	int visited;
	int distance;
	Side *first;
}Node,Adjlist[MAX_VERX_NUM];

typedef struct Graph{
	Adjlist vertices;
	int vexnum, arcnum;
}Graph;

int LocateGraph(Graph G, string u){
	for(int i=0; i<G.vexnum; i++)
		if(G.vertices[i].data==u)
			return i;
	return -1;
}

int v0;
string s;
int pre[MAX_VERX_NUM];


void CreateGraph(Graph &G){
	string v1, v2;
	int i, j, k,w;
	cout<<"Please enter the number of vertices and arcs..."<<endl;
	cin>>G.vexnum>>G.arcnum;

	cout<<"Please enter the vertices..."<<endl;
	for(k=0; k<G.vexnum; k++){
		cin>>G.vertices[k].data;
		G.vertices[k].first=NULL;
	}

	cout<<"Please enter the arcs and their weight..."<<endl;
	for(k=0; k<G.arcnum; k++){
		cin>>v1>>v2>>w;
		i= LocateGraph(G, v1);
		j= LocateGraph(G, v2);

        Side *arc=new Side;
		arc->adjvex=j;
		arc->next=G.vertices[i].first;
		G.vertices[i].first=arc;
		arc->weight=w;

		arc=new Side;
		arc->adjvex=i;
		arc->next=G.vertices[j].first;
		G.vertices[j].first=arc;
		arc->weight=w;
	}
	cout<<"Please enter the start vertex..."<<endl;
	cin>>s;
	v0= LocateGraph(G, s);   
}


void Djikstra(Graph &G){
	Side *e;
	int i, step, min, x, p;
	for(i=0; i<G.vexnum; i++){ // initialize
		G.vertices[i].distance=INFINITE;
		G.vertices[i].visited=0;
	}

	for(i=0; i<G.vexnum; i++){ // initialize the pre node
		pre[i]=v0;
	}

	G.vertices[v0].distance=0;

	for(step=1; step<=G.vexnum; step++){
		min= INFINITE;
		for(i=0; i<G.vexnum; i++){
			if(G.vertices[i].visited==0 && G.vertices[i].distance<min){
				min= G.vertices[i].distance;
				p= i;
			}
		}
		G.vertices[p].visited= 1;
		for(e=G.vertices[p].first; e; e=e->next){
			x=e->adjvex;
			if(G.vertices[x].visited==0)
				if(G.vertices[x].distance>G.vertices[p].distance+(e->weight)){
					G.vertices[x].distance= G.vertices[p].distance+(e->weight);
					pre[x]=p;
				}
		}			
	}
}

void printResult(Graph G){
	stack<int> Stack;
	cout<<"The Shortest distance between "<<s<<" and other vextices are as follow..."<<endl;
	cout<<"Original->Destination"<<"	"<<"Distance"<<"	"<<"Path"<<endl;
	for(int i=0;i<G.vexnum;i++){
		if(i==v0)
			continue;	
		cout<<s<<" -> "<<G.vertices[i].data<<"\t\t\t"<<G.vertices[i].distance<<"\t\t";
		int ite=i;
		do{
			ite=pre[ite];
			Stack.push(ite);
		}while(ite!=v0);
		while(!Stack.empty()){
			cout<<G.vertices[Stack.top()].data<<"->";
			Stack.pop();
		}
		cout<<G.vertices[i].data<<endl;

	}

}

void main(){
	Graph g;
	CreateGraph(g);
	Djikstra(g);
	
	printResult(g);
	

}