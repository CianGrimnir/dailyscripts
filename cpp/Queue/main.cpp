#include "Queue.h"

int main(){
	FILE *fp;
	Queue Q;
	char* string=(char*)malloc(sizeof(char)*20);
	fp=fopen("test.txt","r+");
	if(fp==NULL) { printf("File not open.\n"); return 1; }
	while(fscanf(fp,"%s",string)==1){
//		printf("string: %s \n",string);
		Q.push(string);
		string=(char*)malloc(sizeof(char)*20);
	}
	Q.PrintQueue();
	printf("Size : %d \n",Q.size());
	printf("Front: %s\n",Q.front());
	Q.pop();
	printf("Size : %d \n",Q.size());
	Q.PrintQueue();
}	
