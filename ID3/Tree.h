#ifndef TREE_H
#define TREE_H
#include "Classificator.h"
#include <vector>
#include <string>
#include <map>

using namespace std;



struct node{
	int key; //if key is 11 class is recurrence-events ,if its 12 - no-recurrence-events
	map<string, int> indval;//map of children based on attr value
	vector<node *>children;
};

class Tree{
public:
	Tree();
	~Tree();

	node * insert(int key, node *child); //add a child
	//string search(int *attr);
	void destroy_tree();
	void print();
	node * getroot();
	int find(string attr[]);


private:
	void destroy_tree(node *leaf);
	void print(node *leaf);
	node *root;
	int find(string attr[],node *leaf);
};



#endif // TREE_H
