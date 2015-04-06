#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#include "Fibonacci.h"

using namespace std;

void Fibonacci_heap::Insert(int vertex, int dist){
	if(root==NULL){	
		// cout << "Inserting root " << dist << " " << dist << endl;			
		root = new node(vertex,dist);	// Allocate memory for root

		root->left=root;
		root->right=root;
		num++;
	} else {
		// cout << "Inserting element " << dist << " " << dist << endl;
		node* n = new node(vertex,dist); // Allocate memory for the element to be inserted

		root->left->right = n;		// Insert node into root's doubly linked list
		n->right = root;
		n->left = root->left;
		root->left = n;

		if(n->data < root->data){ // Change root if the inserted element is the minimum.
			// cout << "changing root to " << dist << " " << dist << endl; 
			root = n;
		}
		num++;
	}
}

void Fibonacci_heap::Link(node* p2,node* p1){
	p2->left->right = p2->right; // sever connections of p2
	p2->right->left = p2->left;

	if(p1->right==p1) root=p1;
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

	p1->degree++; // Incriment the degree of p1
}

void Fibonacci_heap::Consolidate(){
	// cout << "Start consolidate" << endl;
	int D = 1+(int)(log(num)/log(2)); // Possible number of degrees with num elements
	int d;
	node* A[D];
	for(int i=0;i<=D;i++){
		A[i]=NULL;
	}
	node* r=root;
	node* p1 = root;

	stack<node*> s;
	s.push(r);
	r=r->right;
	while(r!=root){    		// Push all teh subtrees into a stack
		s.push(r);
		r=r->right;
	}

	while(!s.empty()){
		p1=s.top();
		s.pop();
		d=p1->degree;
		// cout << "popped subtree is " << p1->data << " " << p1->degree << endl;
		while(A[d]!=NULL){  // Check if array contains any subtree with same degree
			node* p2=A[d];
			if(p1->data > p2->data){
				node* temp = p1;
				p1 = p2;
				p2 = temp;
			}
			// cout << "link " << p2->data << " " <<  p1->data << endl;
			Link(p2,p1);	// Link subtree with root p2 to subtree with root p1
			if(p1->right==p1){
				root=p1;
			}
			A[d]=NULL;
			d++;
		}
		A[d]=p1;
	}

	// cout << "Linking done - update root" << endl;
	root = NULL;
	for(int i=0;i<=D;i++){ // Update the root with proper node
		if(A[i]!=NULL){
			if(root==NULL){
				root = A[i];
				root->left = root;
				root->right = root;
				// cout << "new root = " << root->data << endl;
			} else {
				A[i]->right = root;
				A[i]->left = root->left;
				root->left->right = A[i];
				root->left = A[i];
				if(A[i]->data < root->data){
					root = A[i];
					// cout << "Updated root = " << root->data << endl;
				}
			}
		}
	}
	// node* t=root;
	// cout << t->data << " ";
	// while(t->right!=root){
	// 	t = t->right;
	// 	cout << t->data << " ";
	// }
	// cout << endl;

}

node* Fibonacci_heap::RemoveMin(){
	// cout << "RemoveMin" << endl;
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
	node* child=root->child;
	node* rootend=root;
	node* childend=child;

	node* temp = root;
	if(root->child!=NULL){
		// cout << "Child is " << root->child->data << endl;
		// cout << "Child exists-merge lists" << endl;
		// cout << temp->data << " ";
		while(temp->right!=root){
			temp = temp->right;
			rootend = temp; 
			// cout << temp->data << " ";
		}
		// cout << "Find rootend " << root->data << " " << rootend->data << endl;
		temp = root->child;
		child->parent = NULL;
		// cout << "child data is " << temp->data << " ";
		int c=0;	
		while(temp->right!=child){
			c++;
			temp = temp->right;
			childend = temp;
			childend->parent = NULL;
			// if(c%1000000==0){
			// 	cout << temp->data << " ";
			// }
			
		}
		cout << endl;
		// cout << "Find childend" << child->data << " " << childend->data << endl;
		if(child==childend){
			root->left = child;
			child->right = root;
			rootend->right = childend;
			childend->left = rootend;
			// cout << "child list merged to top list" << endl;

		} else {
			root->right = child;
			child->left = root;
			rootend->left = childend;
			childend->right = rootend;
			// cout << "child list merged to top list" << endl;
		}
	}

	// node* t=root;
	// cout << t->data << " ";
	// while(t->right!=root){
	// 	t = t->right;
	// 	cout << t->data << " ";
	// }
	// cout << endl;

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
	ptr->mark=false;
	return p;
}

void Fibonacci_heap::DecreaseKey(int vertex, int data, int newdata){
	if(root==NULL) return;

	// cout << "Find " << vertex << " " << data << endl;
	node *ptr=Find(root,vertex,data);

	if(ptr==NULL){
		// cout << "Not found in the heap!!" << endl;
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
	// cout << "DecreaseKey done" << endl;

}

void Fibonacci_heap::Cut(node* ptr, node* par){
	// cout << "Cut " << ptr->vertex << " from " << par->vertex << endl;
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
	// cout << "Cascade_Cut " << ptr->vertex << endl;
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
