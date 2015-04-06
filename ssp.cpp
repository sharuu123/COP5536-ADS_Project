#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include "Fibonacci.h"
#include "dijkstra.h"

using namespace std;

int main(int argc, char *argv[]){
	
	// Fibonacci_heap fh;

	// int arr[]={3, 6, 1, 8, 5, 11, 2, 7, 9, 4};
	// // int arr[]={7,4,2,7,8,1,12,8,9,10,11,23,13,56,15,16,17,18,19,20};
	// for(int i=0;i<10;i++){
	// 	fh.Insert(i,arr[i]);
	// }

	// fh.DecreaseKey(5,11,0);
	// // fh.DecreaseKey(0,7,1);
	// // fh.DecreaseKey(1,4,1);
	// // cout << "Insertions done" << endl;
	// for(int i=0;i<8;i++){
	// 	node* n=fh.RemoveMin();
	// 	cout << "min val is " << n->data << endl;
	// }

	// node* n=fh.Find(fh.root,4,5);
	// cout << "Find " << n->vertex << " " << n->data << endl;

	// fh.DecreaseKey(3,4,2);
	// fh.DecreaseKey(9,210,1);

	// n=fh.RemoveMin();
	// cout << "min val is " << n->vertex << " " << n->data << endl;

	string filename=argv[1];
	int src=atoi(argv[2]);
	int des=atoi(argv[3]);

	int n,m;
	unordered_map<int, unordered_map<int,int>> G;

	string line;
	ifstream myfile(filename);
	myfile >> n; 		// Vertices
	myfile >> m;		// Edges
	int a,b,c;
    while (myfile >> a){
        myfile >> b >> c;
        G[a][b]=c;
        G[b][a]=c;
    }

     // cout << G[0][170] << endl;


    vector<int> spath;
    int sval=0;

    spath = dijkstra(G,src,des);

    for(int i=0;i<spath.size()-1;i++){
    	int s=spath[i];
    	int d=spath[i+1];
    	sval += G[s][d];
    }

    cout << sval << endl;

    for(int i=0;i<spath.size();i++){
    	cout << spath[i] << " ";
    }
    cout << endl;

    // for(unordered_map<int, unordered_map<int,int>>::iterator it1 = G.begin();
    // 	 it1 != G.end(); it1++){
    // 	for(unordered_map<int,int>::iterator it2 = it1->second.begin();
    // 		it2 != it1->second.end(); it2++){
    // 		cout << it1->first << " " << it2->first << " " << it2->second << endl;
    // 	}
    // }

	return 0;
}