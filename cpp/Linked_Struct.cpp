#include<iostream>
#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
};
/*
void append(struct node **Node,int value);
void AddBegin(struct node **Node,int value);
void AddPos(struct node *Node,int value);
int DeletePos(struct node *Node);
void Display(struct node *Node);
*/
void append(struct node **head,int value){
	struct node *Node=(struct node*)malloc(sizeof(struct node));
	Node->data=value;
	Node->next=NULL;
	if(*head==NULL){
		printf("App CALL: Empty List\n");
		*head=Node;
		return;
	}
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	temp=*head;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=Node;
	return;
}

void AddBegin(struct node **head,int value){
	struct node *Node=(struct node*)malloc(sizeof(struct node));
	Node->data=value;
	Node->next=*head;
	*head=Node;
	return;
}

void AddPos(struct node **head,int POS,int value){
	if(POS==0){
		AddBegin(head,value);
		return;
	}
	struct node *Node=(struct node*)malloc(sizeof(struct node));
	Node->data=value;
	struct node *Next,*Prev;
	int i;
	for(i=0,Next=*head;i<POS;i++){
		if(Next==NULL){
			printf("Wrong POS\n");
			return;
		}
		Prev=Next;
		Next=Next->next;
		printf("\nIN LOOP: %d %d\n",Prev->data,Next->data);
	}
	Node->next=Prev->next;
	Prev->next=Node;
	printf("\nFINAL: %d %d %d\n",Prev->data,Prev->next->data,Node->next->data);
	return;
}

void DeleteNode(struct node **head,int POS){
	struct node *Node=(struct node*)malloc(sizeof(struct node));
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	Node=*head;
	if(POS==1){
		Node=*head;
		*head=Node->next;
		delete Node;
		return;
	}
	for(int i=1;i<POS;i++){
		if(Node==NULL){
			printf("\nDeleteNode CALL: Wrong POS\n");
			return;
		}
		temp=Node;
		Node=Node->next;
	}
	temp->next=Node->next;
	delete Node;
	return;
}

void Display(struct node *head){
	if(head==NULL){
		printf("List Empty\n");
		return;
	}
	struct node *Node=(struct node*)malloc(sizeof(struct node));
	Node=head;
	printf("\nDisplay: \t");
	while(Node!=NULL){
		printf("%d ",Node->data);
		Node=Node->next;
	}
	return;
}

int main(){
	struct node *head=NULL;
	Display(head);
	AddBegin(&head,11);
	Display(head);
	append(&head,12);
	append(&head,13);
	append(&head,14);
	Display(head);
	AddPos(&head,0,22);
	Display(head);
	AddPos(&head,3,23);
	Display(head);	
	DeleteNode(&head,8);
	Display(head);

}