#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include "Fibonacci.h"
#include "dijkstra.h"
#include "BinaryTrie.h"

using namespace std;

unordered_map<int, unordered_map<int,int>> G;
unordered_map<int, unordered_map<int,int>> IP;
unordered_map<int, BTrie> bt;

void BuildTries(int n){
	for(int i=0;i<n;i++){ 		// for each router
		for(int j=0;j<n;j++){	// add next hop for remaining all routers
			if(i!=j){
				// cout << "Building Trie for " << i << " " << j << endl;
				vector<int> spath = dijkstra(G,i,j);
				int hop = spath[1];
				// cout << "Next hop is " << hop << endl;
    			// cout << IP[j][0]<<"."<<IP[j][1]<<"."<< IP[j][2]<<"."<<IP[j][3]<< endl;
				bt[i].AddRoute(IP[j],hop);
			}
		}
	}
}

// void FindPath(int src, int des){
// 	int x=src;
// 	cout << src << " ";
// 	int count=0;
// 	while(x!=des){
// 		x=bt[x].FindRoute(IP[des]);
// 		count++;
// 		cout << x << " ";
// 	}
// 	cout << endl;
// }

void FindPath(int src, int des){
	int x=src;
	while(x!=des){
		x=bt[x].FindRoute(IP[des]);
		cout << " ";
	}
	cout << endl;
}

int main(int argc, char *argv[]){

	string filename1=argv[1];
	string filename2=argv[2];
	int src=atoi(argv[3]);
	int des=atoi(argv[4]);

	int n,m;

	ifstream myfile1(filename1);
	myfile1 >> n; 		// Vertices
	myfile1 >> m;		// Edges
	int a,b,c;
    while (myfile1 >> a){
        myfile1 >> b >> c;
        G[a][b]=c;
        G[b][a]=c;
    }

    string line;
	ifstream myfile2(filename2);
	int count=0;

    while (getline(myfile2,line)){
    	int start=0;
        int dot=line.find('.');
		string s = line.substr(start,dot);
    	IP[count][0]=stoi(s);
    	for(int i=1;i<3;i++){
    		start=++dot;
    		dot=line.find('.',dot);
    		string s = line.substr(start,dot-1);
        	IP[count][i]=stoi(s);
    	}
    	s = line.substr(dot+1,line.size()-1);
        IP[count][3]=stoi(s);
     	count++;
     	getline(myfile2,line);
    } 

    // for(int i=0;i<n;i++){
    // 	cout << IP[i][0]<<"."<<IP[i][1]<<"."<< IP[i][2]<<"."<<IP[i][3]<< endl;
    // }

    int sval=0;
    vector<int> spath = dijkstra(G,src,des);

    for(int i=0;i<spath.size()-1;i++){
    	int s=spath[i];
    	int d=spath[i+1];
    	sval += G[s][d];
    }

    cout << sval << endl;

    // for(int i=0;i<spath.size();i++){
    // 	cout << spath[i] << " ";
    // }
    // cout << endl;

 //   	spath = dijkstra(G,1,6);
	// int hop = spath[1];
	// cout << "Next hop is " << hop << endl;
	// cout << IP[6][0]<<"."<<IP[6][1]<<"."<< IP[6][2]<<"."<<IP[6][3]<< endl;
	// cout << " ";
	// bt[1].AddRoute(IP[6],hop);
	// cout << endl;

    BuildTries(n);
    // cout << "Done BuildTries !!!" << endl;
    for(auto i:bt){
    	// cout << "PostOrderTraversal for " << i.first << endl;
    	i.second.PostOrderTraversal();
    }
    // cout << "PostOrderTraversal Done !!!" << endl;

    FindPath(src,des);

	return 0;
}

