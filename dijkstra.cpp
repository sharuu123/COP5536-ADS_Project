
#include <iostream>
#include "dijkstra.h"

using namespace std;

vector<int> dijkstra(unordered_map<int, unordered_map<int,int>> &G, int src, int des){

	unordered_map<int,int> dist; // distances to source from different nodes
	unordered_map<int,int> prev; // map to previous node in shortest path
	Fibonacci_heap fh;
	vector<int> path;
	int count=0;
	for(int i=0;i<G.size();i++){
		if(i==src){
			dist[i]=0;
			fh.Insert(i,0);
		} else {
			dist[i]=INT_MAX;
			fh.Insert(i,INT_MAX);
		}
		count++;
	}
	// for(auto i : G){			// Initialization 
	// 	if(i.first == src){
	// 		dist[i.first]=0;	// for source dist=0
	// 		fh.Insert(i.first,0);
	// 	} else {
	// 		dist[i.first]=INT_MAX;
	// 		fh.Insert(i.first,INT_MAX);
	// 	}
	// 	count++;
	// 	if(count%100000==0) cout << "..";
	// 	// cout << "Inserting " << i.first << " " << dist[i.first] << endl;
	// 	// fh.Insert(i.first,dist[i.first]);
	// }
	cout << "\nNo of vertices = " << count << endl;
	int x=0;
	while(!fh.empty()){
		cout << "**";
		cout << ++x << endl;
		node *n = fh.RemoveMin();
		// cout << "Relaxing node " << n->vertex << " " << n->data << endl;

		if(n->vertex == des){
			cout << "\nTrace path and return" << endl;
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

		cout << "**";
		for(auto i : G[n->vertex]){  // update dist for neighbours
			cout << ".";

			int newdist = dist[n->vertex] + i.second;
			if(newdist < dist[i.first]){
				// cout << "Updating node " << i.first << " " << dist[i.first] << " with " 
				// << newdist << endl;
				fh.DecreaseKey(i.first,dist[i.first],newdist);
				// node* n1=fh.Find(fh.root,i.first);
				// cout << "Decreased node is " << n1->vertex << " " << n1->data << endl;
				dist[i.first]=newdist;
				prev[i.first]=n->vertex;
			}
		}

		// cout << "Relaxing Done" << endl;
	}
	cout << endl;
	return path;
}