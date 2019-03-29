#include<typeinfo>
#include "Queue.h"

struct Node* CreateNode(char* value){
	struct Node* NewNode=(Node*)malloc(sizeof(Node));
	NewNode->data=value;
	return NewNode;
}	

Queue::Queue(){
	root=NULL;
	count=0;
}

void Queue::push(char* value){
	if(count==MAX) { printf("Queue Full C:%d M:%d\n",count,MAX); return; }
	struct Node* NewNode=CreateNode(value);
	printf("push : %s\n",NewNode->data);
	count++;
	if(root==NULL){
		root=NewNode;
		root->next=NULL;
		return;
	}
	struct Node* temp=root;
	while(temp->next!=NULL)
		temp=temp->next;
	NewNode->next=NULL;
	temp->next=NewNode;
	return;
}

void Queue::pop(){
	if(root==NULL){ printf("Queue empty.\n"); return; }
	struct Node* temp=root;
	root=root->next;
	count--;
	free(temp->data);
	free(temp);
}

char* Queue::front(){
	if(root==NULL){	printf("Queue empty.\n"); return NULL; }
	return root->data;
}

int Queue::size(){
	return count;
}

void Queue::PrintQueue(){
	if(root==NULL){ printf("Queue empty.\n"); return; }
	struct Node* temp=root;
	while(temp!=NULL){
		printf("QVal: %s\n",temp->data);
		temp=temp->next;
	}
}
//
//int main(){
//	Queue Q;
//	Q.push(5);
//	Q.push(6);
//	Q.push(8);
//	Q.push(12);
//	Q.PrintQueue();
//	Q.CountPrint();
//	printf("Front: %d\n",Q.front());
//	Q.pop();
//	Q.CountPrint();
//	Q.PrintQueue();
//}
//	
