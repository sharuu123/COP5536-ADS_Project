#include <iostream>

struct node{
	int degree;
	int data;
	node* child;
	node* left;
	node* right;
	node* parent;
	bool childcut;
	node(int val){   // Constructor for node structure.
		data=val;
		degree=0;
		child=NULL;
		left=NULL;
		right=NULL;
		parent=NULL;
		childcut=false;
	}
};

class Fibonacci_heap{

	private:
		node* root;
		int num;
	public:
		void Insert(int);
		node* RemoveMin();
		void Meld(node*,node*);
		void Remove(node*);
		void DecreaseKey();
		// Helper Functions
		void Link(node*,node*);
		void Consolidate();

};

void Fibonacci_heap::Insert(int val){
	if(root==NULL){				
		root = new node(val);	// Allocate memory for root

		root->left=root;
		root->right=root;
		num++;
	} else {
		node* n = new node(val); // Allocate memory for the element to be inserted

		root->left->right = n;		// Insert node into root's doubly linked list
		n->right = root;
		n->left = root->left;
		root->left = n;

		if(n->data < root->data){ // Change root if the inserted element is the minimum.
			root = n;
		}
		num++
	}
}

void Fibonacci_heap::Link(node* x,node* y){
	
}

void Fibonacci_heap::Consolidate(){
	int degrees = (int)(log(num)/log(2));
	node* A[degrees] = {NULL};
	node* 
	do{

	}while()
}

node* Fibonacci_heap::RemoveMin(){
	if(root==NULL){			// If heap is empty return NULL
		return NULL;
	}
	if(root->child==NULL && root->right==root){ // Only one element is present in the heap
		node* ptr = root;
		root = NULL;
		return ptr;
	}
	node* r = root;   		 // Store address of min node to return it at the end of function.
	node* child=NULL;
	if (root->child!=NULL){  // Check if child exists for the root
		child = root->child;
		node* first = child;
		node* next;
		do{							// insert each child node tree into root's doubly linked list
			next = child->right;

			root->left->right = child; 
			child->right = root;
			child->left = root->left;
			root->left = child;

			if(child->data < root->data){
				root = child;
			}

			child->parent = NULL;

			child = next;		// make child point to next tree in the list
		} while(child!=first)
	}
	r->left->right = r->right;  // Remove the min from the list.
	r->right->left = r->left;
	if(root==r){
		root = root->right;
	}
	Consolidate(); 
	num--; 

	return r;
}

int main(){
	return 0;
}