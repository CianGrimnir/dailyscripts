#include<iostream>
/*#include<vector>*/
#include<unordered_map>
#include<fstream>
#include<string.h>
#include<sstream>
using namespace std;

struct Person{
	string Name;
	string last;
	int roll,standard;
	friend ostream & operator<<(ostream &o,Person& P);

	Person(string Name="empty",string last="empty",int roll=0,int standard=0){
	this->Name=Name;
	this->last=last;
	this->roll=roll;
	this->standard=standard;

	}
};

ostream & operator<<(ostream &o,Person& P){
	char dl='|';
	o<<P.Name<<dl<<P.last<<dl<<P.roll<<dl<<P.standard<<endl;
	return o;
}

int main(){
	Person P1("rakesh1","Nair",34,1);
	Person P2("rakesh","Nair",34,2);
	Person P3("rakesh2","Nair",34,3);
	Person P4("rakesh3","Nair",34,4);
	Person P5("rakesh4","Nair",34,5);
/*	std::vector<Person> v;
	v.push_back(P1);
	v.push_back(P2);
	v.push_back(P3);
	v.push_back(P4);
	v.push_back(P5);*/
	std::unordered_map<string,Person> mp;
	mp.insert(pair<string,Person>(P1.Name,P1));
	mp.insert(pair<string,Person>(P2.Name,P2));
	mp.insert(pair<string,Person>(P3.Name,P3));
	mp.insert(pair<string,Person>(P4.Name,P4));
	mp.insert(pair<string,Person>(P5.Name,P5));
	std::unordered_map<string,Person>::iterator IterMap;
	for(IterMap=mp.begin();IterMap!=mp.end();IterMap++){
		cout<<IterMap->first<<"\t"<<IterMap->second;
	}

	ofstream outfile("/tmp/student.txt");
	if(!outfile.is_open()){ cout<<"Failed to open file.\n"; return 1; }
	/*std::vector<Person>::iterator iter;
	for(iter=v.begin();iter!=v.end();iter++){
		outfile<<*iter;
	}*/
	for(IterMap=mp.begin();IterMap!=mp.end();IterMap++){
		outfile<<IterMap->second;
	}
	Person P;
	/*std::vector<Person> v1;*/
	std::unordered_map<string,Person> mp1;
	ifstream infile("/tmp/student.txt");
	if(!infile.is_open()){ cout<<"Failed to open file.\n"; return 1; }
	string str,roll,standard;
	while(getline(infile,str)){
		istringstream ss(str);
		getline(ss,P.Name,'|');
		getline(ss,P.last,'|');
		getline(ss,roll,'|');
		getline(ss,standard,'|');
		P.roll=stoi(roll);
		P.standard=stoi(standard);
		cout<<P;
		mp1.insert(pair<string,Person>(P.Name,P));
		/*v1.push_back(P);*/
	}
	/*cout<<"Vector out..\n";*/
	cout<<"Map out..\n";
	for(IterMap=mp1.begin();IterMap!=mp1.end();IterMap++){
		cout<<IterMap->first<<"\t"<<IterMap->second;
	}
	/*for(iter=v.begin();iter!=v.end();iter++){
		cout<<*iter;
	}*/
}