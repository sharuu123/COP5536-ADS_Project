#include <iostream>
#include <vector>
#include "BinaryTrie.h"

using namespace std;

void BTrie::Add(tnode* ptr, unordered_map<int,int> des, int hop, int part, int bit){
	// cout << "part " << part << " " << "bit " << bit << endl;
	int ip=des[part];
	int flag=(ip & (1<<(7-bit)));
	// cout << ip << " " << bit << " " << flag << endl;

	if(part==4){
		ptr->hop=hop;
		ptr->type=1;
		return;
	}

	if(bit<7){
		bit++;
	} else {
		bit=0;
		part++;
	}

	if(flag==0){ // bit is 1
		// cout << "Check for part " << part << " bit " << bit << endl;
		if(ptr->left==NULL){
			ptr->left = new tnode(0);
			ptr->left->parent = ptr;
		}
		Add(ptr->left,des,hop,part,bit);
	} else {	 // bit is 0
		// cout << "Check for part " << part << " bit " << bit << endl;
		if(ptr->right==NULL){
			ptr->right = new tnode(0);
			ptr->right->parent = ptr;
		}
		Add(ptr->right,des,hop,part,bit);
	}
}

void BTrie::AddRoute(unordered_map<int,int> des, int hop){

	if(root==NULL){
		root = new tnode(0);
	}

	Add(root,des,hop,0,0);

}

int BTrie::Find(tnode* ptr, unordered_map<int,int> des, int part, int bit){
	int ip=des[part];
	int flag=(ip & (1<<(7-bit)));
	// cout << "part " << part << " bit " << bit << " flag " << flag << endl; 

	if(ptr->type==1){
		return ptr->hop;
	}

	if(bit<7){
		bit++;
	} else {
		bit=0;
		part++;
	}

	if(flag==0){ // bit is 1
		cout << 0;
		return Find(ptr->left,des,part,bit);
	} else {	 // bit is 0
		cout << 1;
		return Find(ptr->right,des,part,bit);
	}
}

int BTrie::FindRoute(unordered_map<int,int> des){
	return Find(root,des,0,0);
}

void BTrie::pst(tnode* ptr){
	if(ptr->left!=NULL){
		pst(ptr->left);
	}
	if(ptr->right!=NULL){
		pst(ptr->right);
	}
	if(ptr->left==NULL && ptr->right==NULL && ptr->type==1){
		if(ptr->parent->left == ptr){ // left child to parent
			if(ptr->parent->right!=NULL){
				if(ptr->parent->right->type==1){
					if(ptr->parent->right->hop==ptr->hop){
						ptr->parent->type=1;
						ptr->parent->hop=ptr->hop;
						ptr->parent->right=NULL;
						ptr->parent->left=NULL;
					}
				}
			} else {
				ptr->parent->type=1;
				ptr->parent->hop=ptr->hop;
				ptr->parent->right=NULL;
				ptr->parent->left=NULL;
			}

		} else {
			if(ptr->parent->left!=NULL){
				if(ptr->parent->left->type==1){
					if(ptr->parent->left->hop==ptr->hop){
						ptr->parent->type=1;
						ptr->parent->hop=ptr->hop;
						ptr->parent->left=NULL;
						ptr->parent->right=NULL;
					}
				}
			} else {
				ptr->parent->type=1;
				ptr->parent->hop=ptr->hop;
				ptr->parent->left=NULL;
				ptr->parent->right=NULL;
			}
		}
	}

}

void BTrie::PostOrderTraversal(){
	pst(root);
}