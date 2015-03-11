
COP 5536 Spring 2015
Programming Project

1. Problem description

Part 1
You are required to implement Dijkstra's Single Source Shortest Path (ssp) algorithm for undirected graphs using Fibonacci heaps. You must use the adjacency list representation for graphs.

Part 2
You are required to implement a routing scheme (routing) for a network. Each router has an IP address and packets are forwarded to the next hop router by longest prefix matching using a binary trie (See Lectures 27-30). For each router R in the network, call ssp implemented in Part 1 to obtain shortest path from R to each destination router Y. To construct the router table for R, for each destination Y, examine the shortest path from R to Y and determine the router Z just after R on this path. This gives you a set of pairs <IP address of Y, next-hop router Z>. Insert these pairs into a binary trie. Finally,do a postorder traversal, removing subtries in which the next hop is the same for all destinations. Thus, multiple destinations having a prefix match and the same next hop will be grouped together in the trie.

