#include<iostream>
#include<stdio.h>

using namespace std;

void Merge(int arr[],int l,int m,int r);
void MergeSort(int arr[],int l,int r);
void PrintArray(int arr[],int SZ);

int main(){
	int arr[]={22,34,5,61,1,7,9};
	int SZ=sizeof arr/sizeof arr[0];
	printf("Size: %d\n",SZ );
	MergeSort(arr,0,SZ-1);
	PrintArray(arr,SZ);
}


void MergeSort(int arr[],int l,int r){
	if(l<r){
		int m=l+(r-l)/2;
		MergeSort(arr,l,m);
		MergeSort(arr,m+1,r);
		/*printf("\nMergeCall: %d %d %d\n",l,m,r );*/
		Merge(arr,l,m,r);
	}
}

void Merge(int arr[],int l,int m,int r){
	int n1=m-l+1;
	int n2=r-m;
	int temp[n1],temp2[n2];
	for(int i=0;i<n1;i++)
		temp[i]=arr[l+i];
	for(int j=0;j<n2;j++)
		temp2[j]=arr[m+j+1];
	int i=0,j=0,k=l;
	while(i<n1 && j<n2){
		if(temp[i]>temp2[j]){
			arr[k]=temp[i];
			i++;
		}
		else{
			arr[k]=temp2[j];
			j++;
		}
		k++;
	}
	while(i<n1){
		arr[k]=temp[i];
		i++;
		k++;
	}
	while(j<n2){
		arr[k]=temp2[j];
		j++;
		k++;
	}
}


void PrintArray(int arr[],int SZ){
	for(int i=0;i<SZ;i++)
		printf("%d ",arr[i]);
}