
#include<iostream>
#include<stdio.h>

class Linked{

private:
	struct node{
		int data;
		struct node *next;
	}*parent;
	int count;
	
public:
	Linked();
	void Append(int);
	void AddAtBegin(int);
	void AddAtPos(int,int);
	void DeleteNode(int);
	void Display();
	int SearchElem(int);
	int MidElem();
};

Linked::Linked(){
	parent=NULL;
	count=0;
}

void Linked::Append(int value){
	node *temp,*NewNode;
	count++;
	if(parent==NULL){
		printf("New node parent\n");
		parent=new node;
		parent->data=value;
		parent->next=NULL;
		return;
	}
	temp=parent;
	NewNode=new node;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	NewNode->data=value;
	NewNode->next=NULL;
	temp->next=NewNode;
	return;
}

void Linked::AddAtBegin(int value){
	node *temp=new node;
	count++;
	temp->data=value;
	temp->next=parent;
	parent=temp;
}

void Linked::AddAtPos(int Pos,int value){
	if(parent==NULL){
		printf("Empty List\n");
		return;
	}
	node *temp=parent;
	node *NewNode=new node;
	for(int i=1;i<Pos;i++){
		if(temp==NULL){
			printf("Wrong POS\n");
			return;
		}
		else{
			temp=temp->next;
		}
	}
	NewNode->data=value;
	NewNode->next=temp->next;
	temp->next=NewNode;
	count++;
	return;
}

void Linked::DeleteNode(int value){
	printf("Deleting node.\n");
	if(parent==NULL){
		printf("Already Empty\n");
		return;
	}
	if(parent->data==value){
		node *temp=parent;
		parent=parent->next;
		delete temp;
		count--;
	}
	node *temp=parent;
	node *prev=temp;
	for (temp=parent;temp->next!=NULL;temp=temp->next){
		if(temp->data==value){
			prev->next=temp->next;
			delete temp;
			count--;
		}
		prev=temp;
	}
}

void Linked::Display(){
	node *temp=parent;
	if(parent==NULL){
		printf("Empty List\n");
		return;
	}
	else{
		printf("List:\n");
		while(temp!=NULL){
			printf("%d\n",temp->data);
			temp=temp->next;
		}
	}
	return;
}

int Linked::MidElem(){
	if(parent==NULL){
		printf("List Empty\n");
		return NULL;
	}
	node *temp=parent;
	for(int i=1;i<=count/2;i++)
		temp=temp->next;
	return temp->data;
}

int Linked::SearchElem(int value){
	int found=0;
	if(parent==NULL){
		printf("List Empty\n");
		return NULL;
	}
	node *temp=parent;
	while(temp->next!=NULL){
		if(temp->data==value){
			found++;
		}
		temp=temp->next;
	}
	return found;
}


int main(){
	Linked list;
	list.DeleteNode(13);
	list.Append(11);
	list.Append(12);
	list.Append(13);
	list.Append(10);
	list.Display();
	list.Append(14);
	list.Display();
	list.AddAtBegin(10);
	list.Display();
	list.DeleteNode(10);
	list.Display();
	printf("Middle element %d\n",list.MidElem());	
	list.AddAtPos(3,15);
	list.Display();
	printf("Middle element %d\n",list.MidElem());	
	printf("Found %d times\n",list.SearchElem(10));
//printf("%d total count\n",list.count );
}
