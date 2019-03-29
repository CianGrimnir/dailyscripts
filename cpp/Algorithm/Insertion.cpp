#include<iostream>
#include<stdlib.h>
using namespace std;


/*		INSERTION SORT		*/
void insertsort(int arr[],int n){
	int key,j;
	for(int i=1;i<n;i++){
		key=arr[i];
		j=i-1;
		while(j>=0 && arr[j]>key){
			arr[j+1]=arr[j];
			j-=1;
		}
		arr[j+1]=key;
	}

}

/*		SELECTION SORT		*/

void swap(int *a,int *b){
	int temp=*a;
	*a=*b; *b=temp;
}
void selectionsort(int arr[],int n){
	for(int i=0;i<n-1;i++){
		int MinIndex=i;
		for(int j=i+1;j<n;j++){
			if(arr[j]<arr[MinIndex]){
				MinIndex=j;
			}
		}
		/*cout<<&arr[MinIndex]<<" "<<&arr[i]<<endl;*/
		swap(&arr[MinIndex],&arr[i]);
	}
}


void PrintArray(int arr[],int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
}
int main(){
	int arr[]={65,61,77,81,11,1,12,66};
	int SIZE=sizeof(arr)/sizeof(arr[0]);
	PrintArray(arr,SIZE);
	cout<<endl;
//	insertsort(arr,SIZE);
	selectionsort(arr,SIZE);
	PrintArray(arr,SIZE);
}

/*		SELECTION SORT		*/

