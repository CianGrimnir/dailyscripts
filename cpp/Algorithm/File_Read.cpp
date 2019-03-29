#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

struct student{
	char name[10];
	char surname[10];
	int roll;
	char div;
};

int main(){
	struct student *st=new student;
	ofstream outfile("SAMPLE.TXT",ios::app|ios::binary);
	char ch='y';
	while(ch=='y'){
		cout<<"Enter records: name surname roll div\n";
		cin>>st->name>>st->surname>>st->roll>>st->div;
		cout<<st->name<<st->surname<<st->roll<<st->div<<endl;
		cout<<sizeof(*st);
		outfile.write((char *)st,sizeof(*st));
		cout<<"Enter another records [y/n] ?\n";
		cin>>ch;
	}
	
outfile.close();

struct student *st1=new student;
ifstream infile("SAMPLE.TXT",ios::binary);
while(infile.read((char *)st1,sizeof(*st1))){
	cout<<"Records:#\n";
	cout<<st1->name<<st1->surname<<st1->roll<<st1->div<<endl;
}
infile.close();
char *full_path=realpath("SAMPLE.TXT",NULL);
printf("%s",full_path);
}