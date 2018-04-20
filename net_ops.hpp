/*-------------------------------------------------------------------------------
 * 1. Function to find the biggest cluster in the network
 * 2. Function to remove randomly chosen nodes with percolation probability
 * 3. Prune network to satisfy kcore condition
 * @Author: Nagendra Panduranga
-------------------------------------------------------------------------------*/


#ifndef NET_OPS_HPP
#define NET_OPS_HPP


/*-----------------------------------------------------------------------------*/


#include <cmath>

#include <queue>

#include <stack>

#include <string>


/*-------------------------------------------------------------------------------
 * @param graph object
 * @param input vector to store indices of nodes in biggest connected cluster
 * Finds the biggest connected cluster
-------------------------------------------------------------------------------*/


inline void find_biggest_cluster(Graph & net, vector<int> & biggest_cluster) {

  biggest_cluster.clear();
  int num_nodes = net.get_num_vertices();

  // Keep track of nodes visited and made a list of the node's neighbors
  bool * marked;
  marked=new bool[num_nodes];

  // start from a node if its not already visited
  for (int i=0; i < num_nodes; ++i) marked[i]=false;
  stack<int> search_stack;
  int idx_search;

  Graph::node_neighbor_iterator idx_neighbor;

  // temp cluster keeps all the interconnected nodes in a vector
  vector<int> temp_cluster;

  
  for (int idx_node=0; idx_node < num_nodes; ++idx_node) {

    // If the node is not marked, add the node to stack
    if (!marked[idx_node]) {

      temp_cluster.clear();
      temp_cluster.push_back(idx_node);
      search_stack.push(idx_node);

      // Mark the node as visited once it is added to search stack
      marked[idx_node]=true;
  
      while (!search_stack.empty()) {

	//Visit the node at the top of the stack
	idx_search=search_stack.top();
	search_stack.pop();

	// Add all the neighbors of the node to the stack to be visited
	for (idx_neighbor=net.vertex_neighbor_begin(idx_search);
	     idx_neighbor!=net.vertex_neighbor_end(idx_search); ++idx_neighbor)
	  if (!marked[*idx_neighbor]) {
	    search_stack.push(*idx_neighbor);
	    temp_cluster.push_back(*idx_neighbor);
	    marked[*idx_neighbor]=true;
	  }
      }

      // Copy the temp cluster to biggest cluster if temp cluster > biggest cluster
      if (temp_cluster.size() > biggest_cluster.size())
	biggest_cluster=temp_cluster;
    }
  }
  
  delete []marked;
}


/*-------------------------------------------------------------------------------
 * @param graph object
 * @param percolation probability
 * All the links are deleted from randomly chosen nodes 
 * Fraction of nodes with degree > 0 remaining in the graph is equal to percolation probabiity
-------------------------------------------------------------------------------*/


inline void initial_random_attack(double p, Graph &net){
  
  // p is the probability that a node survives random attack
  int num_nodes=net.get_num_vertices();

  
  // Create a set to keep track of removed nodes
  set<int> set_removed_nodes;
  set_removed_nodes.clear();

  
  //Number of nodes attacked
  int num_init_attack=int((1.-p)*num_nodes);

  
  // Randomly remove nodes until num_init_attack number of nodes are removed
  while(set_removed_nodes.size()<num_init_attack){

    //index of node removed is randomly chosen
    int node_idx=int(srand()*num_nodes);

    
    // Remove all the links of the randomly chosen node if its degree > 0
    if(net.get_deg_vertex(node_idx))
      net.rm_a_node(node_idx);
    set_removed_nodes.insert(node_idx);
  }
  set_removed_nodes.clear();
}


/*-------------------------------------------------------------------------------
 * @param graph object
 * Pruning = Remove links from all nodes in the network whose degree is less than its local kcore threshold
 * Pruning stops when the number of nodes pruned in a cycle is zero 
 * @return count of the number of prune scans of the entire network 
-------------------------------------------------------------------------------*/


int network_prune(Graph &net) { 

  
  int num_nodes;
  int node_local_threshold;
  int node_degree;

  
  num_nodes= net.get_num_vertices();

  
  // keep track of nodes removed
  set<int> set_removed_nodes;

  
  // Number of iterations pruning network 
  int num_prune_iterations;

  
  num_prune_iterations = 0;

  
     do{

      // For every scan, increase pruning iteration number by 1
      set_removed_nodes.clear();
      ++num_prune_iterations;


      // Scan through every node in the network to check that its degree is greater than its local kcore threshold
    for(int node_idx = 0; node_idx < num_nodes; node_idx++){

      
      // Get node's degree and its local kcore threshold
      node_local_threshold = net.get_threshold(node_idx);
      node_degree =  net.get_deg_vertex(node_idx);


      // Remove all the links from a node whose degree is less than that of its local kcore threshold
        if(node_degree > 0 && node_degree < node_local_threshold) {
	net.rm_a_node(node_idx);
	set_removed_nodes.insert(node_idx);
	}
    }    

    
    // Stop when no nodes are removed in a cycle
     }while(set_removed_nodes.size() > 0);
  

     return num_prune_iterations;

}


#endif
