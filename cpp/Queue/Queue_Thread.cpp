#include "Queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<typeinfo>

Queue Q;
FILE *fp;
int FILEC=0;
int Qlock=0;
pthread_mutex_t lock;
pthread_cond_t cond;

void* Producer(void* args){
	char* string=(char*)malloc(sizeof(char)*20);
	fp=fopen("test.txt","r+");
	if(fp==NULL) { printf("File not open.\n"); FILEC=1; pthread_cond_broadcast(&cond); return NULL; }
	while(fscanf(fp,"%s",string)==1){
		if(1){
			pthread_mutex_lock(&lock);
			printf("Produced : %s\n",string);
			Q.push(string);
			string=(char*)malloc(sizeof(char)*20);
			pthread_cond_broadcast(&cond);
		}
		else{
			printf("Producer in wait ..\n");
			pthread_cond_wait(&cond,&lock);
		}
		pthread_mutex_unlock(&lock);
	}
	FILEC+=1;
}
			
void* Consumer(void* args){
	while(1){
		pthread_mutex_lock(&lock);
		if(Q.size() > 0){
			char* data=Q.front();
			printf("Consumed%d : %s\n",*((int*)args),data);
			Q.pop();
			pthread_cond_signal(&cond);
		}
		else if(FILEC > 0){
			pthread_mutex_unlock(&lock);
			return NULL;
		}
		else{
			printf("Consumer in wait ..\n");
			pthread_cond_wait(&cond,&lock);
		}
		pthread_mutex_unlock(&lock);
	}
}

int main(){
	int i=0,j=1,k=2;
	pthread_t producer,consumer0,consumer1,consumer2;
	printf("Thread started...\n");
	int prod=pthread_create(&producer,NULL,Producer,NULL);
	int cons=pthread_create(&consumer0,NULL,Consumer,&i);
	int cons1=pthread_create(&consumer1,NULL,Consumer,&j);
	int cons2=pthread_create(&consumer2,NULL,Consumer,&k);
	if(!cons) pthread_join(consumer0,NULL);
	if(!cons1) pthread_join(consumer1,NULL);
	if(!cons2) pthread_join(consumer2,NULL);
	printf("Thread Ended...\n");
	return 0;
}
