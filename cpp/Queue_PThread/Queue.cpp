#include<typeinfo>
#include "Queue.h"
#include<unistd.h>
#include<time.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int wait=0;

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
	pthread_mutex_lock(&lock);
	struct Node* NewNode=CreateNode(value);
//	printf("push : %s\n",NewNode->data);
	count++;
	if(root==NULL){
		root=NewNode;
		root->next=NULL;
	}
	else{
	struct Node* temp=root;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=NewNode;
	NewNode->next=NULL;
	}
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&lock);
	return;
}

char* Queue::pop(){
	pthread_mutex_lock(&lock);
	if(root==NULL){ 
		struct timespec timewait;
		timewait.tv_sec=2;
//		printf("pop wait ...\n");
		int rt=pthread_cond_timedwait(&cond,&lock,&timewait);
//		printf("pop wake %d C: %d...\n",rt,count);
		if(count==0) { 
			pthread_cond_signal(&cond);
		        pthread_mutex_unlock(&lock);
			return "Empty"; 
		}
	 }
	struct Node* temp=root;
	root=root->next;
	count--;
	char* data=temp->data;
//	std::cout<<"Typeinfo: "<<typeid(temp->data).name()<<std::endl;
	free(temp);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
	return data;
}

int Queue::size(){
	return count;

}

void Queue::PrintQueue(){
	pthread_mutex_lock(&lock);
	while(root==NULL){
		printf("Print wait ...\n");
		pthread_cond_wait(&cond,&lock);
	}
	struct Node* temp=root;
	while(temp!=NULL){
		printf("QVal: %s\n",temp->data);
		temp=temp->next;
	}
	printf("PrintQueue finished\n");
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
}

/*
int main(){
	Queue Q;
	printf("Front: %s\n",Q.front());
	Q.push("a");
	Q.push("b");
	Q.push("c");
	Q.push("12");
	Q.PrintQueue();
	Q.pop();
	Q.PrintQueue();
}
*/	
/*char* Queue::front(){
	pthread_mutex_lock(&lock);
	printf("Front entered\n");
	char* data="None";
	if(count!=0){ 
	//while(root==NULL){
	//	printf("front wait ...\n");
	//	pthread_cond_wait(&cond,&lock);
	//	} 
	data=root->data;
	printf("Front data %s\n",data);
	pthread_cond_signal(&cond);
	}
	pthread_mutex_unlock(&lock);
	return data;
}
*/
