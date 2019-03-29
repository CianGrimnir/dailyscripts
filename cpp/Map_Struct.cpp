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
	Person s4("rakesh3",26,87,200);
	Person s1("rakesh",23,57,170);
	Person s5("rakesh4",27,97,210);
	std::unordered_map<string, Person> map_pair;
	map_pair.insert(pair<string,Person>("rakesh",s1));
	map_pair.insert(pair<string,Person>("rakesh1",s2));
	map_pair.insert(pair<string,Person>("rakesh2",s3));
	map_pair.insert(pair<string,Person>("rakesh3",s4));
	map_pair.insert(pair<string,Person>("rakesh4",s5));
	std::unordered_map<string, Person>::iterator ptr;
	for(ptr=map_pair.begin();ptr!=map_pair.end();ptr++)
		cout<<ptr->first<<"\t"<<ptr->second;

	std::unordered_map<string, Person>::iterator ptr1=map_pair.find("rakesh12");
	if(ptr1==map_pair.end())	{ cout<<"Pair not found.\n"; } else { cout<<"Pair found \t"<<ptr1->first<<"\t"<<ptr1->second; }
	map_pair.erase(map_pair.find("rakesh1"),map_pair.find("rakesh4"));
	cout<<"After erasing ..\n";
	for(ptr=map_pair.begin();ptr!=map_pair.end();ptr++){
		cout<<ptr->first<<"\t"<<ptr->first.length()<<"\t"<<ptr->first[ptr->first.length()-1]<<"\t"<<ptr->second;
		if(ptr->first[ptr->first.length()-1]=='h'){
			cout<<"Found : "<<ptr->first<<endl;
		}	
	}
}


/*	string name="rakesh";
	map_pair.find(name);
*/