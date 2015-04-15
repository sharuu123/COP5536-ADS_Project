
#include <iostream>
#include <ctime>
#include "dijkstra.h"

using namespace std;

vector<int> dijkstra(unordered_map<int, unordered_map<int,int>> &G, int src, int des){
	int* dist = new int[G.size()];  // array to store minimun distances from source
	int* prev = new int[G.size()];	// array to store parent nodes 

	unordered_map<int,node*> addr;  // map to store address after insertion into heap
	Fibonacci_heap fh;				// fibonacci heap to store min distances
	vector<int> path;				// vector to store shortest path

	int count=0;
	for(int i=0;i<G.size();i++){	// Intialize the nodes with starting min distances
		if(i==src){
			dist[i]=0;				// for source min distance = 0
			addr[i]=fh.Insert(i,0);
		} else {
			dist[i]=INT_MAX;		// for other nodes, min distance = INT_MAX
			addr[i]=fh.Insert(i,INT_MAX);
		}
		count++;
	} 

	while(!fh.empty()){
		node *n = fh.RemoveMin();	// extract the minimum element

		if(n->vertex == des){		// if extracted element is des, stop relaxing
			// cout << "\nTrace path and return" << endl;
			int temp=des;
			// cout << temp << " ";
			while(prev[temp]!=src){
				path.insert(path.begin(),temp);
				temp=prev[temp];
				// cout << temp << " " << endl;
			}
			path.insert(path.begin(),temp);
			path.insert(path.begin(),src);
			break;
		}

		for(auto i : G[n->vertex]){  // relax the neighbours

			int newdist = dist[n->vertex] + i.second;
			if(newdist < dist[i.first]){ // decrease the min distance if found new path

				fh.DecreaseKey(addr[i.first],newdist);
				dist[i.first]=newdist;		// update new min distance
				prev[i.first]=n->vertex;	// update the parent node
			}
		}

	}
	return path;
}