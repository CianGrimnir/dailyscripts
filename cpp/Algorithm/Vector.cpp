#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#define MAX 20
using namespace std;

struct student{
	string Name;
	int age;
	int weight;
	int height;
	student(string Name="empty",int age=0,int weight=0,int height=0){
		this->Name=Name;
		this->age=age;
		this->weight=weight;
		this->height=height;
	}
	friend ostream& operator <<(ostream& o,student& P);
	friend istream& operator >>(istream& o,student& P);
};

ostream& operator <<(ostream& o,student& P){
	o<<P.Name<<" "<<P.age<<" "<<P.weight<<" "<<P.height<<endl;
	return o;
}

istream& operator >>(istream& o,student& P){
	o>>P.Name>>P.age>>P.weight>>P.height;
	return o;
}

int main(){
	ofstream outfile("student.txt"/*,ios::app*/);
	if(!outfile.is_open()){cout<<"Failed to open!"; return 1; }
	student s1("rakesh",23,57,170);
	student s2("rakesh1",24,67,180);
	student s3("rakesh2",25,77,190);
	student s4("rakesh3",26,87,200);
	student s5("rakesh4",27,97,210);
	std::vector<student> v;
	v.push_back(s1);
	v.push_back(s2);
	v.push_back(s3);
	v.push_back(s4);
	v.push_back(s5);
	std::vector<student>::iterator ptr;
	for (ptr=v.begin();ptr<v.end();ptr++)
	{
		outfile<<*ptr;
	}

	std::vector<student> v1;
	student P;
	string str;
	ifstream infile("student.txt");
	while(getline(infile,str)){
		istringstream iss(str);	
		iss>>P;
		v1.push_back(P);
	}

	cout<<"Size\tCapacity: "<<v1.size()<<"\t"<<v1.capacity()<<endl;
	for(ptr=v1.begin();ptr<v1.end();ptr++){
		cout<<*ptr;
	}
}