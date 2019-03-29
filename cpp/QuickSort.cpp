#include<iostream>
#include<stdio.h>
using namespace std;

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

int Partition(int arr[],int start,int end){
	int pivot=arr[end];
	int PartitionIndex=start;
	for(int i=start;i<end;i++){
		if(arr[i]<pivot){
			swap(&arr[i],&arr[PartitionIndex]);
			PartitionIndex++;
		}
	}
	swap(&arr[PartitionIndex],&arr[end]);
	return PartitionIndex;
}

void QuickSort(int arr[],int start,int end){
	if(start<end){
		int PartitionIndex=Partition(arr,start,end);
		printf("Start: %d End: %d Partition: %d \n",start,end,PartitionIndex);
		QuickSort(arr,start,PartitionIndex-1);
		printf("Right: Start: %d End: %d Partition: %d \n",start,end,PartitionIndex+1);
		QuickSort(arr,PartitionIndex+1,end);
	}
}

void PrintArray(int arr[],int SZ){
	for(int i=0;i<SZ;i++)
		printf("%d ", arr[i]);
}



int main(){
	int arr[]={22,34,5,61,1,7,9};
	int SZ=sizeof arr/ sizeof arr[0];
	//PrintArray(arr,SZ);
	QuickSort(arr,0,SZ-1);
	PrintArray(arr,SZ);
}