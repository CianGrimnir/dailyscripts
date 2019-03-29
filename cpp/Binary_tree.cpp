#include<iostream>
#include<stdlib.h>

using namespace std;

struct Node{
	int item;
	Node *left,*right;
};


class Btree{
public:
	Node *root;
public:
	Btree(){
		root=NULL;
	}
	void insert(int key);
	void add(Node **leaf,int key);
	void Search(Node *leaf,int key);
	/*void Delete(Node *leaf,int key);*/
	void PrintB(Node *leaf);
	int GetLevel(Node *leaf,int key,int level);
};

struct Node* CreateNode(int key){
	struct Node* node=(Node*)malloc(sizeof(Node));
	node->item=key;
	node->left=node->right=NULL;
	return node;
}

void Btree::insert(int key){
	if(root!=NULL)
		add(&root,key);
	else{
		printf("New root node\n");
		root=CreateNode(key);
	}
}

void Btree::add(Node **leaf,int key){
	if(*leaf==NULL){
		*leaf=CreateNode(key);
		return;
	}
	else{
		if((*leaf)->item==key) { printf("Key exist\n"); return; }
		else if((*leaf)->item>key)
			add(&(*leaf)->left,key);
		else
			add(&(*leaf)->right,key);
	}
}

void Btree::Search(Node *leaf,int key){
	if(leaf!=NULL){
		if(leaf->item==key){printf("Key Found\n"); return; }
		else if(leaf->item>key)	Search(leaf->left,key);
		else Search(leaf->left,key);
	}
	else
		printf("Key not found\n");
}

void Btree::PrintB(Node *leaf){
	if(leaf!=NULL){
		PrintB(leaf->left);
		printf("%d ",leaf->item );
		PrintB(leaf->right);
	}
}

int Btree::GetLevel(Node *leaf,int key,int level){
	if(leaf!=NULL){
		if(leaf->item==key)	return level;
		else if (leaf->item>key) GetLevel(leaf->left,key,level+1);
		else GetLevel(leaf->right,key,level+1);
			}
	else
		return 0;
}

int main(){
	Btree bt;
	bt.insert(15);
	bt.insert(43);
	bt.insert(15);
	bt.insert(5);
	bt.insert(7);
	bt.insert(33);
	bt.Search(bt.root,17);
	bt.PrintB(bt.root);
	printf("Level of 7: %d\n", bt.GetLevel(bt.root,7,1));
}
