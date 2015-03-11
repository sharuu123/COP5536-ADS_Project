
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

	public:
		void Insert(int);
		node* RemoveMin();
		void Meld(node*,node*);
		void Remove(node*);
		void DecreaseKey();

}