
#include <iostream>
#include "dijkstra.h"

using namespace std;

vector<int> dijkstra(unordered_map<int, unordered_map<int,int>> &G, int src, int des){

	// for(auto i:G){
 //    	for(auto j:i.second){
 //    		cout << i.first << " " << j.first << " " << j.second << endl;
 //    	}
 //    }

	unordered_map<int,int> dist; // distances to source from different nodes
	unordered_map<int,int> prev; // map to previous node in shortest path
	Fibonacci_heap fh;
	vector<int> path;
	int count=0;
	for(auto i : G){			// Initialization 
		if(i.first == src){
			dist[i.first]=0;	// for source dist=0
		} else {
			dist[i.first]=INT_MAX;
		}
		count++;
		// cout << "Inserting " << i.first << " " << dist[i.first] << endl;
		fh.Insert(i.first,dist[i.first]);
	}
	cout << "No of vertices = " << count << endl;

	while(!fh.empty()){
		node *n = fh.RemoveMin();
		cout << "Relaxing node " << n->vertex << " " << n->data << endl;

		if(n->vertex == des){
			cout << "Trace path and return" << endl;
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

		for(auto i : G[n->vertex]){  // update dist for neighbours

			int newdist = dist[n->vertex] + i.second;
			if(newdist < dist[i.first]){
				cout << "Updating node " << i.first << " " << dist[i.first] << " with " 
				<< newdist << endl;
				fh.DecreaseKey(i.first,dist[i.first],newdist);
				// node* n1=fh.Find(fh.root,i.first);
				// cout << "Decreased node is " << n1->vertex << " " << n1->data << endl;
				dist[i.first]=newdist;
				prev[i.first]=n->vertex;
			}
		}

		cout << "Relaxing Done" << endl;
	}

	// int temp=des;
	// while(prev[temp]!=src){
	// 	path.insert(path.begin(),temp);
	// 	temp=prev[temp];
	// }
	// path.insert(path.begin(),temp);
	// path.insert(path.begin(),src);
	

	// for(int i=0;i<path.size();i++){
	// 	cout << path[i] << " ";
	// }
	return path;
}