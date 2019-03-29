#include<iostream>
#include<stdio.h>

class LQueue{
private:
	struct node{
		int data;
		struct node *next;
	}*parent;
public:
	LQueue();
	void Enqueue(int);
	int Dequeue();
	void DisplayQ();
	int Count_Q();
};

LQueue::LQueue(){
	parent=NULL;
}

void LQueue::Enqueue(int value){
	node *temp,*Newnode;
	if(parent==NULL){
		parent=new node;
		parent->data=value;
		parent->next=NULL;
		return;
	}
	temp=parent;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	Newnode=new node;
	Newnode->data=value;
	Newnode->next=NULL;
	temp->next=Newnode;
}

int LQueue::Dequeue(){
	if(parent==NULL){
		printf("No data in queue\n");
		return NULL;
	}
	int value=parent->data;
	node *temp=parent;
	parent=parent->next;
	delete temp;
	return value;
}

int LQueue::Count_Q(){
	if(parent==NULL){
		printf("Empty parent\n");
		return NULL;
	}
	node *temp=parent;
	int count=0;
	while(temp!=NULL){
		temp=temp->next;
		count++;
	}
	return count;
}

void LQueue::DisplayQ(){
	if(parent==NULL){
		printf("PARENT Empty\n");
		return;
	}
	node *temp=parent;
	while(temp!=NULL){
		printf("value: %d\n",temp->data);
		temp=temp->next;
	}
}

int main(){
	LQueue lq;
	printf("Total Count: %d\n",lq.Count_Q());
	lq.Enqueue(2);
	lq.Enqueue(3);
	lq.Enqueue(4);
	lq.Enqueue(5);
	lq.DisplayQ();
	printf("Deleted value: %d\n",lq.Dequeue());
	lq.DisplayQ();
	printf("Deleted value: %d\n",lq.Dequeue());
	lq.DisplayQ();
	printf("Total Count: %d\n",lq.Count_Q());
}
