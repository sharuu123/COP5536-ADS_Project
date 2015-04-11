#ifndef BINARY_TRIE_H
#define BINARY_TRIE_H
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

struct tnode{
	int hop;
	int type;
	tnode* left;
	tnode* right;
	tnode* parent;
	tnode(int x){
		type=x;
		hop=-1;
		left=NULL;
		right=NULL;
		parent=NULL;
	}
};

class BTrie{
private:
	tnode* root;
public:	
	BTrie(){
		root=NULL;
	}
	void AddRoute(unordered_map<int,int>,int);
	int FindRoute(unordered_map<int,int>);
	void PostOrderTraversal();
	// Helper Functions
	void Add(tnode*,unordered_map<int,int>,int,int,int);
	int Find(tnode*,unordered_map<int,int>,int,int);
	void pst(tnode*);

};

#endif