#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#include "Fibonacci.h"

using namespace std;

void Fibonacci_heap::Insert(int vertex, int dist){
	if(root==NULL){	
		// cout << "Inserting root " << vertex << endl;			
		root = new node(vertex,dist);	// Allocate memory for root

		root->left=root;
		root->right=root;
		num++;
	} else {
		// cout << "Inserting element " << vertex << endl;
		node* n = new node(vertex,dist); // Allocate memory for the element to be inserted

		root->left->right = n;		// Insert node into root's doubly linked list
		n->right = root;
		n->left = root->left;
		root->left = n;

		if(n->data < root->data){ // Change root if the inserted element is the minimum.
			// cout << "changing root to " << vertex << endl; 
			root = n;
		}
		num++;
	}
}

void Fibonacci_heap::Link(node* p2,node* p1){
	p2->left->right = p2->right; // sever connections of p2
	p2->right->left = p2->left;

	//if(p1->right==p1) root=p1;
	if(p2==root) root=p1;

	p2->parent = p1;		// Make p1 parent of p2
	if(p1->child == NULL){	// Insert p2 into its child circular list
		p1->child = p2;
		p2->left = p2;
		p2->right = p2;
	} else {
		p2->right = p1->child;
		p2->left = p1->child->left;
		p1->child->left->right = p2;
		p1->child->left = p2;
	}

	if(p2->data < p1->child->data){ // Store the smallest element in the child pointer
		p1->child = p2;
	}

	p1->degree++; // Incriment the degree of p1
}

void Fibonacci_heap::Consolidate(){
	// cout << "Start consolidate" << endl;
	int D = (int)(log(num)/log(2)); // Possible number of degrees with num elements
	int d;
	node* A[D+1];
	for(int i=0;i<=D+1;i++){
		A[i]=NULL;
	}
	node* r=root;
	node* p1 = root;
	node *p2,*temp;

	stack<node*> s;
	s.push(r);
	r=r->right;
	while(r!=root){
		s.push(r);
		r=r->right;
	}

	while(!s.empty()){
		p1=s.top();
		s.pop();
		d=p1->degree;
		while(A[d]!=NULL){  // Check if array contains any subtree with same degree
			p2=A[d];
			if(p1->data > p2->data){
				temp = p1;
				p1 = p2;
				p2 = temp;
			}
			// cout << "link " << p2->data << " " << p1->data << endl;
			Link(p2,p1);	// Link subtree with root p2 to subtree with root p1
			A[d]=NULL;
			d++;
		}
		A[d]=p1;
	}

	// do{
	// 	d=p1->degree;
	// 	bool end=false;
	// 	while(A[d]!=NULL){  // Check if array contains any subtree with same degree
	// 		p2=A[d];
	// 		if(p1->data > p2->data){
	// 			temp = p1;
	// 			p1 = p2;
	// 			p2 = temp;
	// 		}
	// 		cout << "link " << p2->data << " " << p1->data << endl;
	// 		if(p1->right==root && p2==root){
	// 			end=true;
	// 		}
	// 		Link(p2,p1);	// Link subtree with root p2 to subtree with root p1
	// 		A[d]=NULL;
	// 		d++;
	// 	}
	// 	A[d]=p1;
	// 	if(end==false){
	// 		p1=p1->right;
	// 	} else {
	// 		p1=root;
	// 	}	
	// }while(p1!=root);

	// cout << "Linking done - update root" << endl;
	root = NULL;
	for(int i=0;i<=D;i++){ // Update the root with proper node
		if(A[i]!=NULL){
			if(root==NULL){
				root = A[i];
				root->left = root;
				root->right = root;
			} else {
				A[i]->right = root;
				A[i]->left = root->left;
				root->left->right = A[i];
				root->left = A[i];
				if(A[i]->data < root->data){
					root = A[i];
				}
			}
		}
	}
}

node* Fibonacci_heap::RemoveMin(){
	if(root==NULL){			// If heap is empty return NULL
		return NULL;
	}
	if(root->child==NULL && root->right==root){ // Only one element is present in the heap
		node* ptr = root;
		// cout << "only element, make root=NULL" << endl;
		root = NULL;
		num--;
		return ptr;
	}
	node* r = root;   		 // Store address of min node to return it at the end of function.
	node* child=NULL;
	if (root->child!=NULL){  // Check if child exists for the root
		// cout << "Child of root exits" << endl;
		child = root->child;
		node* first = child;
		node* next;
		do{							// insert each child node tree into root's doubly linked list
			next = child->right;

			// cout << "Insert " << child->data << " to left of root" << root->data << endl;
			root->left->right = child; 
			child->right = root;
			child->left = root->left;
			root->left = child;

			// if(child->data < root->data){
			// 	root = child;
			// }

			child->parent = NULL;

			child = next;		// make child point to next tree in the list
		} while(child!=first);
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

node* Fibonacci_heap::Find(node* ptr, int vertex, int data){
	// cout<<"Entering Find"<< endl;
	// cout << ptr->vertex << " " << ptr->data << endl;
	if(ptr==NULL) return NULL;
	ptr->mark = true;
	if(ptr->data == data){
		// cout << "data matches" << endl;
		if(ptr->vertex == vertex){
			// cout << "vertex also matches !!!" << endl;
			ptr->mark=false;
			return ptr;
		}
		// } else {
		// 	return Find(ptr->right,vertex,data);
		// }
	} 
	node *p=NULL;
	if(ptr->child!=NULL){
		// cout << "Find in child tree" << endl;
		p=Find(ptr->child,vertex,data);
	} 
	if(p==NULL){
		// cout << "Check in right subtree" << endl;
		if(ptr->right->mark!=true){
			return Find(ptr->right,vertex,data);
		}
		
	}
	return p;
}

void Fibonacci_heap::DecreaseKey(int vertex, int data, int newdata){
	if(root==NULL) cout << "Heap is empty!!" << endl;

	cout << "Find " << vertex << " " << data << endl;
	node *ptr=Find(root,vertex,data);

	if(ptr==NULL){
		cout << "Not found in the heap!!" << endl;
		return;
	}

	if(ptr->data < newdata){
		cout << "New value is less than actual value!!" << endl;
	}

	if(ptr==root){
		root->data=newdata;
	}

	ptr->data = newdata;
	node *par=ptr->parent;

	if(par!=NULL && ptr->data < par->data){
		Cut(ptr,par);
		Cascade_Cut(par);
	}

	if(ptr->data < root->data){
		root=ptr;
	}
	cout << "DecreaseKey done" << endl;

}

void Fibonacci_heap::Cut(node* ptr, node* par){
	cout << "Cut " << ptr->vertex << " from " << par->vertex << endl;
	if(ptr->right==ptr){
		par->child=NULL;
	} else {
		par->child=ptr->right;
		ptr->left->right=ptr->right;
		ptr->right->left = ptr->left;
	}
	par->degree--;

	root->left->right=ptr;
	ptr->right=root;
	ptr->left=root->left;
	root->left=ptr;

	ptr->parent=NULL;
	ptr->childcut=false;
}

void Fibonacci_heap::Cascade_Cut(node* ptr){
	cout << "Cascade_Cut " << ptr->vertex << endl;
	node *par=ptr->parent;
	if(par!=NULL){
		if(par->childcut==false){
			par->childcut=true;
		} else {
			Cut(ptr,par);
			Cascade_Cut(par);
		}
	}
}

bool Fibonacci_heap::empty(){
	if(root==NULL && num==0){
		return true;
	} else {
		return false;
	}
}

