#include<iostream>
#include<stdio.h>

using namespace std;


void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

/*
		BubbleSort
void BubbleSort(int arr[],int SZ){
	for(int i=0;i<SZ-1;i++)
		for(int j=0;j<SZ-i-1;j++)
			if(arr[j]>arr[j+1])
				swap(arr[j],arr[j+1]);
}
*/

/*
		InsertionSort
void InsertionSort(int arr[],int SZ){
	for(int i=1;i<SZ-1;i++){
		int key=arr[i];
		int j=i-1;
		while(j>=0 && arr[j]>key){
			arr[j+1]=arr[j];
			j-=1;
		}
		arr[j+1]=key;
	}
}
*/

void SelectionSort(int arr[],int SZ){
	for(int i=0;i<SZ-1;i++){
		int MinIndex=i;
		for(int j=i+1;j<SZ;j++){
			if(arr[j]<arr[MinIndex])
				MinIndex=j;
		}
		swap(arr[MinIndex],arr[i]);
	}
}

void PrintArray(int arr[],int SZ){
	printf("\n");
	for(int i=0;i<SZ;i++)
		printf("%d ",arr[i] );
}


int main(){
	int arr[]={22,34,5,61,1,7,9};
	int SZ=sizeof arr/ sizeof arr[0];
	PrintArray(arr,SZ);
//	BubbleSort(arr,SZ);
//	InsertionSort(arr,SZ);
	SelectionSort(arr,SZ);
	PrintArray(arr,SZ);
}