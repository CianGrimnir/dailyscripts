#include<stdio.h>
#include<stdlib.h>
#define MAX 10
struct Node* CreateNode(int value);

struct Node{
	int data;
	Node* next;
};

class Queue{
	Node *root;
	int count;
public:
	Queue();
	void push(int value);
	void pop();
	int size();
	void PrintQueue();
	int front();
};
