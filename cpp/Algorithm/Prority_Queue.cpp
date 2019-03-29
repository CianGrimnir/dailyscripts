#include<iostream>
#include<stdlib.h>

using namespace std;


struct Node{	
	int key;
	int Priority;
	Node *next;
};

class PQueue{
private:
	Node *root;
public:
	PQueue(){
		root=NULL;
	}
	void Enqueue(int key,int Priority);
	void Dequeue();
	void PrintQueue();
};
struct Node* CreateNode(int key,int Priority){
	struct Node* node=(Node*)malloc(sizeof(Node));
	node->key=key;
	node->Priority=Priority;
	return node;
}

void PQueue::Enqueue(int key,int Priority){
	if(root==NULL || root->Priority> Priority){
		Node *temp=CreateNode(key,Priority);
		temp->next=root;
		root=temp;
		return;
	}
	Node *temp=root;
	while(temp->next!=NULL && temp->next->Priority < Priority)
		temp=temp->next;
	Node *node=CreateNode(key,Priority);
	node->next=temp->next;
	temp->next=node;
}

void PQueue::Dequeue(){
	Node *node=root;
	int key=root->key;
	int Priority=root->Priority;
	printf("Dequeue: K: %d P: %d\n",key,Priority);
	root=root->next;
	free(node);
}

void PQueue::PrintQueue(){
	if(root==NULL){ printf("Queue Empty.\n"); return; }
	Node *temp=root;
	while(temp!=NULL){
		printf("K: %d P: %d\n",temp->key,temp->Priority);
		temp=temp->next;
	}
}


int main(){
	PQueue pq;
	pq.Enqueue(15,5);
	pq.Enqueue(25,15);
	pq.Enqueue(35,7);
	pq.Enqueue(45,4);
	pq.Enqueue(55,12);
	pq.Enqueue(65,10);
	pq.PrintQueue();
	pq.Dequeue();
	pq.PrintQueue();

}