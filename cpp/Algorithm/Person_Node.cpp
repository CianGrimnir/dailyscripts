#include<iostream>
#include<string>
using namespace std;

class Person{
public:
	string Name;
	int age;
	int weight;
	int height;

	Person(string Name="empty",int age=0,int weight=0,int height=0){
		this->Name=Name;
		this->age=age;
		this->weight=weight;
		this->height=height;
	}
	Person operator =(const Person& p){
		this->Name=Name;
		this->age=age;
		this->weight=weight;
		this->height=height;
		return *this;
	}
	friend ostream& operator <<(ostream& o,const Person& p);
};
	ostream& operator <<(ostream& o,const Person& p){
		o<<p.Name<<" "<<p.age<<" "<<p.weight<<" "<<p.height<<endl;
	}

class Node{
public:
	Person *data;
	Node *next;

	Node(Person *A){
		data=A;
		next=NULL;
	}
};

class LinkedList{
private:
	Node *head;

public:
	LinkedList(){
		head=NULL;
	}

	void InsertNode(Person *A){
		Node *node=new Node(A);
		node->next=head;
		head=node;
	}

	void InsertAtEnd(Person *A){
		if(head==NULL){
			InsertNode(A);
			return;
		}
		else{
			Node *node=new Node(A);
			node->next=NULL;
			Node *temp=head;
			while(temp->next!=NULL)
				temp=temp->next;
			temp->next=node;
		}
	}

	void InsertAtPos(Person *A,int POS){
		if(head==NULL){
			cout<<"List Empty.\n";
			return;
		}
		else{
			Node *node=new Node(A);
			Node *temp=head;
			for(int i=1;i<POS;i++){
				temp=temp->next;
				if(temp==NULL){	cout<<"Wrong Position.\n"; return; }
			}
			node->next=temp->next;
			temp->next=node;

		}
	}

	void DeleteAtHead(){
		Node *temp=head;
		head=head->next;
		delete temp;
	}

	void DeleteAtPos(int POS){
		if(head==NULL){ cout<<"List Empty.\n"; return; }
		Node *temp=head;
		Node *prev=NULL;
		if(POS==1) {head=temp->next; delete temp; return; }
		for(int i=1;i<POS;i++){
			prev=temp;
			temp=temp->next;
			if(temp==NULL){ cout<<"Wrong POS.\n"; return; }
		}
			prev->next=temp->next;
			delete temp;
	}

	void UpdateAtPos(Person *A,int POS){
		if(head==NULL){ cout<<"List Empty.\n"; return; }
		Node *temp=head;
		for(int i=1;i<POS;i++){
			temp=temp->next;
			if(temp==NULL){ cout<<"Wrong POS.\n"; return; }
		}
		temp->data=A;
	}

	void DeleteByVal(string DelName){
		if(head==NULL){ cout<<"List Empty.\n"; return; }
		Node *temp=head,*prev=NULL,*DelNode=NULL;
		while(temp!=NULL){
			if(temp->data->Name==DelName){
				if(prev!=NULL){
					prev->next=temp->next;
				}
				else{
					head=temp->next;
				}
				DelNode=temp;
				temp=temp->next;
				delete DelNode;
			}
			else{
				prev=temp;
				temp=temp->next;
			}

		}
	}

	void PrintData(){
		if(head==NULL){
			cout<<"\nList Empty.\n";
			return;
		}
		else{
			cout<<"\nPrinting data:\n";
			Node *temp=head;
			while(temp!=NULL){
				cout<<*(temp->data);
				temp=temp->next;
			}
		}
	}

};

int main(){
		LinkedList L1;
		/*L1.PrintData();*/
		L1.InsertNode(new Person("rakesh",23,57,170));
		L1.InsertNode(new Person("rakesh1",24,58,172));
		L1.InsertNode(new Person("rakesh1",25,59,175));
		L1.InsertNode(new Person("rakesh1",24,58,172));
		L1.InsertAtEnd(new Person("Rahul",28,70,17777));
		L1.InsertAtPos(new Person("Vinit",24,169,213),2);
		L1.PrintData();
		L1.DeleteAtHead();
		L1.PrintData();
		L1.DeleteAtPos(4);
		L1.PrintData();
		cout<<"\nUpdating ...";
		L1.InsertNode(new Person("rakesh",23,57,170));
		L1.UpdateAtPos(new Person("rakesh",32,111,12),2);
		L1.PrintData();
		L1.DeleteByVal("Vinit");
		L1.PrintData();
	}	



