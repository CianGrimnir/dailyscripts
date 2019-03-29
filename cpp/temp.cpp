#include<iostream>
#include<stdio.h>
#include<map>
#define MAX(a,b) a>b a:b
using namespace std;

class Complex{
	int real,img;
public:
	Complex(int real,int img=0){
		this->real=real;
		this->img=img;
	}
	void PrintComplex(){
		printf("%d %d\n",real,img );
	}
};

int& point(){
	char *s="asdasdsd";
	return (int&)s;
}
void print(){
	cout<<"oay";
}


int main(){
	Complex C=2;
	C.PrintComplex();
	cout<<(char*)point();
	printf("\n%p %p\n",point,print);
	int diff=0x400796-0x400784;
	printf("Diff: %d\n", diff*sizeof(int) );
	int a=5,b=6;
	printf("%d %d\n",a,b );
	/*std::multimap<char,int> a;
	a.insert(pair<char,int>('a',1));
	a.insert(pair<char,int>('a',12));
	a.insert(pair<char,int>('b',11));
	a.insert(pair<char,int>('c',13));
	a.insert(pair<char,int>('d',12));
	a.insert(pair<char,int>('d',12));
	std::multimap<char,int>::iterator i;
	for(i=a.begin();i!=a.end();i++)
		cout<<i->first<<i->second<<endl;*/
}
