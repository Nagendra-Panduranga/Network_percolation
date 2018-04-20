/*-------------------------------------------------------------------------------
 * Contains graph class 
 * Contains graph functions
 * Graph is a vector of node objects
 * @Author: Nagendra Panduranga
-------------------------------------------------------------------------------*/


#ifndef GRAPH_HPP
#define GRAPH_HPP


/*-----------------------------------------------------------------------------*/

#include <vector>

#include <list>

#include "node.hpp"

/*-----------------------------------------------------------------------------*/

class Graph {
  
protected:

  vector<Node> vertices;
  
public:

  // Single node functions   
  int get_deg_vertex(int idx_vertex);

  
  // Returns the size of the network 
  int size();
  int get_num_vertices();
  void resize(int num_nodes);

  
  //check if node1 and node2 are connected or not
  bool connection_check(int node1,int node2);
  void insert_connection(int n1,int n2);

  
  // Interdependency function
  void add_a_dependant(int n1,int n2);
  void rm_a_node(int node_idx);
  void show_neighbors(int node_idx,vector<int> &v);
  void clear() {vertices.clear();}
  void set_dependence(int node_idx, int dependence_value);
  int get_dependence(int node_idx);


  // Protect node functions
  bool protect_check(int node_idx);
  void protect_node(int node_idx);
  void unprotect_node(int node_idx);
  void unprotect_allnodes();

  
  // Kcore thereshold functions
  void set_threshold(int node_idx, int threshold_inp); 
  int get_threshold(int node_idx);

  
  //iterator functions
  typedef list<int>::iterator node_neighbor_iterator;
  node_neighbor_iterator vertex_neighbor_begin(size_t index) { 
    return vertices[index].neighbor_begin(); }
  node_neighbor_iterator vertex_neighbor_end(size_t index) { 
    return vertices[index].neighbor_end(); }

  
  // Constructor
  Graph(int num_nd) {
    vertices.resize(num_nd);
  }
};

//------------------------------Member function definitions----------------------
/*-------------------------------------------------------------------------------
 * @param two integer indices for two nodes
 * @ Inserts a link between those two nodes
 * @ Updates the neighbor list for both the nodes
-------------------------------------------------------------------------------*/


void Graph::insert_connection(int n1,int n2) {
  vertices[n1].add_a_neighbor(n2);
  vertices[n2].add_a_neighbor(n1);
}


/*-------------------------------------------------------------------------------
 *@param int representing the index of the node to be removed
 *@function Removes all the links from the input node
 *@function Removes the index from the nighbor list of all the former nieghbors
-------------------------------------------------------------------------------*/


void Graph::rm_a_node(int node_idx)
{
  node_neighbor_iterator it;
  for(it=vertex_neighbor_begin(node_idx);it!=vertex_neighbor_end(node_idx);++it){
    vertices[*it].rm_a_neighbor(node_idx);
  }
  vertices[node_idx].rm_all_neighbors();
  return;
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * @param vector to store the indices of neighbors of the input node
-------------------------------------------------------------------------------*/


void Graph::show_neighbors(int node_idx,vector<int> &v)
{
  node_neighbor_iterator it; 
  for(it=vertex_neighbor_begin(node_idx);it!=vertex_neighbor_end(node_idx);++it){
    {
      v.push_back(*it);
    }
  }
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * @Returns degree of the input node
-------------------------------------------------------------------------------*/


int Graph::get_deg_vertex(int idx_vertex)
{
  return vertices[idx_vertex].get_degree();
}


/*-------------------------------------------------------------------------------
 * @Returns the number of nodes in the graph
-------------------------------------------------------------------------------*/


int Graph::size()
{
  return vertices.size();
}


/*-------------------------------------------------------------------------------
 * @Returns the number of nodes in the graph
-------------------------------------------------------------------------------*/


int Graph::get_num_vertices(){
  return vertices.size();
}


/*-------------------------------------------------------------------------------
 * @param two integer indices of two nodes
 * @Returns a boolean if the connection exists between two input nodes
-------------------------------------------------------------------------------*/


bool Graph::connection_check(int node1,int node2)
{
  node_neighbor_iterator it;
  for(it=vertex_neighbor_begin(node1);it!=vertex_neighbor_end(node1);++it)
    if(*it==node2)
      return true;
  return false;
}


/*-------------------------------------------------------------------------------
 * @param number of nodes
 * @Resizes the graph to the input number of nodes
-------------------------------------------------------------------------------*/


void Graph::resize(int num_nodes)
{
  vertices.resize(num_nodes);
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * @param integer threshold value for local kcore threshold
 * Updates the local threshold value of the input node to input threshold value
-------------------------------------------------------------------------------*/


void Graph::set_threshold(int idx_vertex, int threshold_inp)
{
  vertices[idx_vertex].set_threshold(threshold_inp);
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * @Returns local kcore threshold value for the input nodes
-------------------------------------------------------------------------------*/


int Graph::get_threshold(int idx_vertex)
{
  return vertices[idx_vertex].get_threshold();
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * Updates if the node is dependent on another node in the second network
-------------------------------------------------------------------------------*/


void Graph::set_dependence(int idx_vertex,int dependence_value)
{
  vertices[idx_vertex].set_dependence(dependence_value);
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * @Returns if the node is dependent on another node in the second network
 * Output 1 if dependent
-------------------------------------------------------------------------------*/


int Graph::get_dependence(int idx_vertex)
{
  return vertices[idx_vertex].get_dependence();
}


/*-------------------------------------------------------------------------------
 * @param two integer indices of two nodes
 * Creates dependence of first node on second node from other network
-------------------------------------------------------------------------------*/


void Graph::add_a_dependant(int n1,int n2)
{
  vertices[n1].add_a_dependant(n2);
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * Updates the protect_status of the node
-------------------------------------------------------------------------------*/


void Graph::protect_node(int node_idx)
{
  vertices[node_idx].protect_node();
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * Updates the protect_status of the node
-------------------------------------------------------------------------------*/


void Graph::unprotect_node(int node_idx)
{
  vertices[node_idx].unprotect_node();
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * Updates the protect_status of the node
-------------------------------------------------------------------------------*/


void Graph::unprotect_allnodes()
{
  for(int i=0;i<vertices.size();++i)
    vertices[i].unprotect_node();
}


/*-------------------------------------------------------------------------------
 * @param integer index of the node
 * Updates the protect_status of the node
-------------------------------------------------------------------------------*/


bool Graph::protect_check(int node_idx)
{
  return vertices[node_idx].protect_check();
}


#endif
    
