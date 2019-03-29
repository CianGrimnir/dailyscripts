#include<iostream>
#define N 5
using namespace std;

struct Node{
	int dst;
	Node *next;
};

struct queue{
	int item[N];
	int top;
	int rear;
};

struct queue* CreateQueue(){
	struct queue *q=(queue*)malloc(sizeof(queue));
	*q->item=(int *)malloc(sizeof(queue)*N);
	q->top=q->rear=-1;
	return q;
}

int IsEmpty(queue *q){
	if(q->top==-1){
		return 0;
	}
	else{
		return 0;
	}
}

void enqueue(queue *q,int val){
	if(q->rear==N-1){
		cout<<"Queue is Full\n";
		return;
	}
	else{
		if(q->top==-1) q->top++; 
		q->rear++;
		item[q->rear]=val;
	}
}

int dequeue(queue *q){
	int item;
	if(IsEmpty(q)){
		cout<<"Queue IsEmpty"<<endl;
		item=-1;
	}
	else{
		item=q->item[q->top];
		q->top++;
		if(q->top==q->rear){
			cout<<"Calling reset\n";
			q->top=q->rear=-1;
		}
	}
	return item;
}

struct Node* CreateNode(int dst){
	struct Node *node=(Node*)malloc(sizeof(struct Node));
	node->dst=dst;
	return node;
}

struct Graph{
	int V;
	Node* head[N];
	int* visited;
};

void BFS(Graph *graph,int StartVertex){

}


struct Graph* CreateGraph(int V){
	struct Graph *graph=(Graph*)malloc(sizeof(Graph));
	graph->V=V;
	*graph->head=(struct Node*)malloc(V*sizeof(struct Node));
	for(int i=0;i<V;i++)
		graph->head[i]=NULL;
	return graph;
}

void AddEdge(struct Graph* graph,int src,int dst){
	struct Node *node=CreateNode(dst);
	node->next=graph->head[src];
	graph->head[src]=node;

	struct Node *nextnode=CreateNode(src);
	nextnode->next=graph->head[dst];
	graph->head[dst]=nextnode;

}

void PrintGraph(struct Graph *graph){
	for(int v=0;v<graph->V;v++){
		printf("Head[%d]\t",v );
		struct Node* node=graph->head[v];
		while(node){
			cout<<node->dst<<" ";
			node=node->next;
		}
		cout<<endl;
	}
}

int main(){
	struct Graph *graph=CreateGraph(5);
	AddEdge(graph,0,1);
	AddEdge(graph,0,4);
	AddEdge(graph,1,2);
	AddEdge(graph,1,3);
	AddEdge(graph,1,4);
	AddEdge(graph,2,3);
	AddEdge(graph,3,4);
	PrintGraph(graph);
}
