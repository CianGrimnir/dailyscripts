#include<stdio.h>
//#include "Queue.cpp"
#include "Queue.h"
#include<pthread.h>
#ifdef MAX
	#undef MAX
#endif
#define MAX 10

int g=0;
int concount=0;
pthread_mutex_t lock;
pthread_cond_t cond;
static Queue Q;


void* Producer(void* args){
	static int count=0;
	while(1){
		pthread_mutex_lock(&lock);
		if(Q.size() < MAX && count < MAX){
			printf("Produced : %d\n",g);
			Q.push(g);
			g++; count++;
			pthread_cond_broadcast(&cond);
		}
		else if(count == MAX){
			pthread_mutex_unlock(&lock);
			return NULL;
		}
		else{
			printf("Producer in wait ..\n");
			pthread_cond_wait(&cond,&lock);
		}
		pthread_mutex_unlock(&lock);
	}
}
			
void* Consumer(void* args){
	while(1){
		pthread_mutex_lock(&lock);
		if(Q.size() > 0){
			printf("Queue size: %d %d\n",Q.size(),MAX);
			int data=Q.front();
			concount++;
			printf("Consumed%d : %d\n",*((int*)args),data);
			Q.pop();
			pthread_cond_signal(&cond);
		}
		else if(concount == MAX){
			pthread_mutex_unlock(&lock);
			return NULL;
		}
		else{
			printf("Consumer in wait ..\n");
//			Q.PrintQueue();
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


