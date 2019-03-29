#include<iostream>
#include<stdio.h>

class LStack{
private:
	struct node
	{
		int data;
		struct node *next;
	}*parent;
public:
	LStack();
	void Lpush(int);
	int Lpop();
	void LDisplay();
	//int LCount();
};

LStack::LStack(){
	parent=NULL;
}

void LStack::Lpush(int value){
	node *temp=new node;
	temp->data=value;
	if(parent==NULL){
		parent=new node;
		temp->next=NULL;
		parent=temp;
		return;
	}
	temp->next=parent;
	parent=temp;
}

int LStack::Lpop(){
	if(parent==NULL){
		printf("Stack empty\n");
		return NULL;
	}
	node *temp=parent;
	while(temp->next->next!=NULL){
		temp=temp->next;
	}
	int value=temp->next->data;
	node *delnode=temp->next;
	temp->next=NULL;
	delete delnode;
}

void LStack::LDisplay(){
	if(parent==NULL){
		printf("Stack empty\n");
		return;
	}
	node *temp=parent;
	printf("\nData in stack:\n");
	while(temp!=NULL){
		printf("%d->",temp->data );
		temp=temp->next;
	}
}
int main(){
	LStack ls;
	ls.LDisplay();
	ls.Lpush(20);
	ls.Lpush(21);
	ls.Lpush(22);
	ls.Lpush(23);
	ls.LDisplay();
	ls.Lpop();
	ls.Lpop();
	ls.LDisplay();
}
