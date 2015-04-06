#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <unordered_map>
#include <vector>
#include <climits>
#include <algorithm>
#include "Fibonacci.h"

using namespace std;

// struct gnode{
// 	int vertex;
// 	int dist;
// 	gnode *prev;
// 	gnode(x,y){
// 		vertex=x;
// 		dist=y;
// 	}
// };

// unordered_map<int, unordered_map<int,int>> G;

vector<int> dijkstra(unordered_map<int, unordered_map<int,int>>&, int, int);

#endif