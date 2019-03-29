#include<iostream>
#include<string.h>
//#include<map>
#include<unordered_map>
#include<sstream>
using namespace std;

struct Person{
	char*  Name;
	int age;
	int weight;
	int height;

	Person(const char* Name,int age=0,int weight=0,int height=0){
		int length=strlen(Name)+1;
		char* str=new char(length);
		str=strncpy(str,Name,length);
		this->Name=str;
		this->age=age;
		this->weight=weight;
		this->height=height;
	}

	friend ostream& operator<<(ostream& o,Person &P);
};

ostream& operator<<(ostream& o,Person &P){
	o<<P.Name<<" "<<P.age<<" "<<P.weight<<" "<<P.height<<endl;
	return o;
}

int main(){
	Person s2("rakesh1",24,67,180);
	Person s3("rakesh2",25,77,190);
	cout<<s2;	
}