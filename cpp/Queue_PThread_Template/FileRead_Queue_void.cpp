#include "Queue.h"
#include<string.h>

Queue<void*> Q;
int STOPPED=0;
int count=0;

void* Producer(void* args){
	FILE* fp=fopen("test.txt","r+");
	if(fp==NULL) { printf("File not open.\n"); STOPPED=1; return NULL; }
	char* string=(char*)malloc(sizeof(char)*20);
	while(fscanf(fp,"%s",string)==1){
		printf("Produced: %s \n",string);
		Q.push((void*)string);
		string=(char*)malloc(sizeof(char)*20);		
	}
	free(string);
	fclose(fp);
	STOPPED=1;
	//return NULL;
	pthread_exit(NULL);
}

void* Consumer(void* args){
	while(!STOPPED || Q.size()!=0 ){
		char* data=(char*)Q.pop();
//		if(strcmp(data,"Empty")==0){ continue; }
		if(data==NULL) continue;
		printf("Consumed%d: %s\n",*((int*)args),data);
		free(data);
//		Q.PrintQueue();
	}
//	return NULL;
	pthread_exit(NULL);
}
	
int main(){
	pthread_t producer,consumer1,consumer2,consumer3;
	int i=0,j=1,k=2;
	printf("Thread started\n");
	int prod=pthread_create(&producer,NULL,Producer,NULL);
	int cons=pthread_create(&consumer1,NULL,Consumer,&i);
	int cons1=pthread_create(&consumer2,NULL,Consumer,&j);
	int cons2=pthread_create(&consumer3,NULL,Consumer,&k);
	if(!prod) pthread_join(producer,NULL);
	if(!cons) pthread_join(consumer1,NULL);
	if(!cons1) pthread_join(consumer2,NULL);
	if(!cons2) pthread_join(consumer3,NULL);
	printf("Thread ended\n");
}	
