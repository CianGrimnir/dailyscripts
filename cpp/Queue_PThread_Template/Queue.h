#include<stdio.h>                                                                                        
#include<stdlib.h>
#include<iostream>
#include<pthread.h>
#include<typeinfo>
#include<unistd.h>
#include<time.h>
#define MAX 40


pthread_mutex_t lock;
pthread_cond_t cond;
int wait=0;

template<typename var>
struct Node{
	var data;
	Node<var>* next;
};

template<typename T>
struct Node<T>* CreateNode(T value);

template<typename T>
class Queue{
	Node<T> *root;
	int count;
public:
	Queue();
	void push(T value);
	T pop();
	int size();
	void PrintQueue();
//	char* front();
};


template<class T>
struct Node<T>* CreateNode(T value){
	Node<T>* NewNode=(Node<T>*)malloc(sizeof(Node<T>));
	NewNode->data=value;
	return NewNode;
}	

template<class T>
Queue<T>::Queue(){
	root=NULL;
	count=0;
}

template<class T>
void Queue<T>::push(T value){
	pthread_mutex_lock(&lock);
	struct Node<T>* NewNode=CreateNode(value);
	//printf("push : %s\n",NewNode->data);
	std::cout<<"push : "<<NewNode->data<<std::endl;
	count++;
	if(root==NULL){
		root=NewNode;
		root->next=NULL;
	}
	else{
	struct Node<T>* temp=root;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=NewNode;
	NewNode->next=NULL;
	}
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&lock);
	return;
}

template<class T>
T Queue<T>::pop(){
	pthread_mutex_lock(&lock);
	if(root==NULL){ 
		struct timespec timewait;
		timewait.tv_sec=1;
		//printf("pop wait ...\n");
		int rt=pthread_cond_timedwait(&cond,&lock,&timewait);
		//printf("pop wake %d C: %d...\n",rt,count);
		if(count==0) { 
			pthread_cond_signal(&cond);
		        pthread_mutex_unlock(&lock);
			return 0; 
		}
	 }
	struct Node<T>* temp=root;
	root=root->next;
	count--;
	T data=temp->data;
//	std::cout<<"Typeinfo: "<<typeid(temp->data).name()<<std::endl;
//	std::cout<<"pop : "<<data<<std::endl;
	free(temp);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
	return data;
}

template<class T>
int Queue<T>::size(){
	return count;

}

template<class T>
void Queue<T>::PrintQueue(){
	pthread_mutex_lock(&lock);
	while(root==NULL){
		printf("Print wait ...\n");
		pthread_cond_wait(&cond,&lock);
	}
	struct Node<T>* temp=root;
	while(temp!=NULL){
		std::cout<<"QVal: "<< temp->data<<std::endl;
		temp=temp->next;
	}
	printf("PrintQueue finished\n");
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
}

/*
int main(){
	Queue<char*> Q;
	Q.push("a");
	Q.push("b");
	Q.push("c");
	Q.push("d");
//	Q.PrintQueue();
	std::cout<<"POP: "<<Q.pop()<<std::endl;
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
