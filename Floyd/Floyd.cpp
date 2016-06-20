//Floyd's Alogrithm

#include<iostream>
#include<string>
#include<stack>
using namespace std;

#define MAX_NUM 100

typedef struct Arc{
	int adjvex;
	int weight;
	Arc *next;
}Arc;

typedef struct Node{
	string data;
	Arc *first;
}Node, Adjlist[MAX_NUM];

typedef struct Graph{
	int vexnum;
	int arcnum;
	Adjlist vertices;
}Graph;

typedef struct MGraph{
	int Dis[MAX_NUM][MAX_NUM];
	int vexnum;
	int arcnum;
}MGraph;

int Distance[MAX_NUM][MAX_NUM];
int Path[MAX_NUM][MAX_NUM];
int vexnum;

int LocateVex(Graph G, string u){
	for(int i=0;i<G.vexnum;i++)
		if(G.vertices[i].data==u)
			return i;
	return -1;
}

void CreateGraph(Graph &G){
	string v1,v2;
	int i,j,k,w;

	cout<<"Please enter the number of vertices and arcs..."<<endl;
	cin>>G.vexnum>>G.arcnum;

	cout<<"Please enter the vertices..."<<endl;
	for(i=0;i<G.vexnum;i++){
		cin>>G.vertices[i].data;
		G.vertices[i].first=NULL;
	}
	
	cout<<"Please enter the arcs and their weight..."<<endl;
	for(k=0;k<G.arcnum;k++){
		cin>>v1>>v2>>w;
		i=LocateVex(G, v1);
		j=LocateVex(G, v2);

		Arc *arc=new Arc;
		arc->adjvex=j;
		arc->next=G.vertices[i].first;
		G.vertices[i].first=arc;
		arc->weight=w;

		arc=new Arc;
		arc->adjvex=i;
		arc->next=G.vertices[j].first;
		G.vertices[j].first=arc;
		arc->weight=w;
	}
}

void CreateMatrix(){
	int i,j;
	cout<<"Please enter the number of vexices..."<<endl;
	cin>>vexnum;
	cout<<"Please enter the Distance Matrix..."<<endl;
	for(i=0; i<vexnum; i++)
		for(j=0; j<vexnum;j++)
			cin>>Distance[i][j];
}

void Floyd(){
	int i,j,k;
	for(i=0; i<vexnum; i++)
		for(j=0; j<vexnum; j++)
			Path[i][j]=i;

	for(k=0; k<vexnum; k++)
		for(i=0; i<vexnum; i++)
			for(j=0; j<vexnum; j++)
				if(Distance[i][j]>Distance[i][k]+Distance[k][j]){
					Distance[i][j]=Distance[i][k]+Distance[k][j];
					Path[i][j]=Path[k][j];
				}
}

void PrintResult(int D[MAX_NUM][MAX_NUM], int P[MAX_NUM][MAX_NUM]){
	int i,j;
	stack<int> s;
	cout<<"Original->Destination	Distance	Path"<<endl;
	for(i=0; i<vexnum; i++)
		for(j=0; j<vexnum; j++){
			if(i!=j){
			cout<<i<<" -> "<<j<<"\t\t\t"<<Distance[i][j]<<"\t\t";
			int k=j;
			do{
				k=Path[i][k];
				s.push(k);
			}while(k!=i);
			while(!s.empty()){
				cout<<s.top()<<" -> ";
				s.pop();
			}
			cout<<j<<endl;
			}
		}
}

void main(){
	CreateMatrix();
	cout<<"The shortest path is as follow..."<<endl;
	Floyd();
	PrintResult(Distance, Path);


}