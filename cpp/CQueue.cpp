#include<iostream>
#include<stdio.h>
#define MAX 10

class Queue{
private:
	int arr[MAX];
	int front,rear;
public:
	Queue();
	void pushQ(int);
	int popQ();
	void Display();
	int count();
};

Queue::Queue(){
	front=rear=-1;
}

void Queue::pushQ(int value){
	if((rear==MAX-1 && front==0) || (rear+1==front)){
		printf("Queue FULL\n");
		return;
	}
	if(rear==MAX-1){
		rear=0;
	}
	else{
		rear++;
	}
	arr[rear]=value;
	if (front==-1) front=0;
}

int Queue::popQ(){
	if(front==-1){
		printf("Queue Empty.\n");
		return NULL;
	}
	int data=arr[front];
	if(front==rear)	front=rear=-1;
	if(front==MAX-1){
		front=0;
	}
	else{
		front++;
	}
	return data;
}

void Queue::Display(){
	if(front==-1){
		printf("Queue Empty\n");
		return;
	}
	printf("DISPLAY -> FRONT: %d REAR: %d\n",front,rear);
	int temp=front;
	//do{
		//printf("Temp: %d Rear:%d Value: %d\n",temp,rear,arr[temp] );
		//if(temp==MAX-1){
			//temp=0;
		//}
		//else temp++;
	//}while(temp!=rear+1 );
	if(rear>front){
		for(int i=temp;i<=rear;i++)
			printf("Temp: %d Rear:%d Value: %d\n",temp,rear,arr[i]);
		}
	else{
		for(int i=temp;i<=rear;i++)
			printf("Temp: %d Rear:%d Value: %d\n",temp,rear,arr[i]);
	}
	printf("FRONT: %d REAR: %d\n",front,rear);
	}

int Queue::count(){
	if(front==-1){
		printf("Empty Queue\n");
		return NULL;
	}
	int count=0,temp=front;
	//while(front!=rear+1){
		//count++;
		//if(front==MAX-1){
			//front=0;
		//}
		//else front++;
	//}
	if(rear>front){
		for(int i=temp;i<=rear;i++)
			count++;
		}
	else{
		for(int i=temp;i<=rear;i++)
			count++;
	}
	return count;
}

int main(){
	Queue q;
	q.Display();
	for(int i=1;i<8;i++)
		q.pushQ(i);
	q.Display();
	printf("POP Value: %d\n",q.popQ());
	q.Display();
	printf("Total Count : %d\n",q.count());
}