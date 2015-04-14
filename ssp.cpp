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
    cout << "Adding done" << endl;

     // cout << G[0][170] << endl;


    vector<int> spath;
    int sval=0;

    spath = dijkstra(G,src,des);

    cout << "dijkstra done" << endl;

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