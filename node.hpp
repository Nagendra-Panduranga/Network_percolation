/*-------------------------------------------------------------------------------
 * Contains Node class 
 * Contains Node member function definitions 
 * @Author: Nagendra Panduranga
-------------------------------------------------------------------------------*/

#ifndef NODE_HPP
#define NODE_HPP


/*-----------------------------------------------------------------------------*/

#include <stdlib.h>

#include <list>

#include <iostream>

/*-----------------------------------------------------------------------------*/


class Node {

protected:

  // List of indices of nodes linked to the current node
  list<int> neighbors;


  // List of dependent node on the current node
  list<int> dependants;

  
  // Integer value if the node is dependent on another node 
  int dependence; 

  
  // Protect_status = 1 means node cannot be attacked
  int protect_status;

  
  // kcore threshold for the node. if degree of the node < threshold, node gets removed during kcore percolation
  int threshold;

  
public:

  // Single node neighbor functions
  void add_a_neighbor(int other_node_index);
  void rm_a_neighbor(int node_index);
  void rm_all_neighbors();
  int  get_degree();

  
  // protect a node
  void protect_node();
  void unprotect_node();
  bool protect_check();

  
  // interdependency functions
  void rm_a_dependant(int node_index);
  void rm_all_dependants();
  void add_a_dependant(int node_index);
  void set_dependence(int dependence_value);
  int get_dependence();

  
  // k-core functions
  void set_threshold(int threshold_inp);
  int get_threshold();

  
  // iterator definition
  typedef list<int>::iterator neighbor_iterator;
  neighbor_iterator neighbor_begin() { return neighbors.begin(); }
  neighbor_iterator neighbor_end() { return neighbors.end(); }

  
  // constructor
  Node() {
    
    protect_status=0;
    dependence = 0; 
  }
};

//------------------------------Member function definitions----------------------
/*-------------------------------------------------------------------------------
 * Returns the number of neighbors of the node
-------------------------------------------------------------------------------*/


int Node::get_degree()
{
  return neighbors.size();
}


/*-------------------------------------------------------------------------------
 * @param integer index for the node to be added to the neighbor list
-------------------------------------------------------------------------------*/


void Node::add_a_neighbor(int other_node_index)
{
  neighbors.push_back(other_node_index);
}


/*-------------------------------------------------------------------------------
 * @param integer index of node to be removed
 * @ Updates the neighbor list for both the nodes
-------------------------------------------------------------------------------*/


void Node::rm_a_neighbor(int node_index)
{

  neighbor_iterator it;

  for(it=neighbor_begin();it!=neighbor_end();++it){
    if(*it==node_index){
      break;
    }
  }

  // looks for the input node index in the neighbors list
  if(it!=neighbor_end()){
    it=neighbors.erase (it);
  }
  
  else{
    cerr<<"don't have such neighbor!"<<endl;
    exit(1);
  }
}


/*-------------------------------------------------------------------------------
 * @ Removes all neighbors of the node
-------------------------------------------------------------------------------*/


void Node::rm_all_neighbors()
{
  neighbors.clear();
  return;
}


/*-------------------------------------------------------------------------------
 * @param integer index of node to be added
 * @ Inserts the input index to the list of dependents of the node
-------------------------------------------------------------------------------*/


void Node::add_a_dependant(int node_index)
{
  dependants.push_back(node_index);
}


/*-------------------------------------------------------------------------------
 * @param integer index of node to be removed
 * Removes the input node index from the dependents list
-------------------------------------------------------------------------------*/


void Node::rm_a_dependant(int node_index){
  neighbor_iterator it;
  for(it=dependants.begin();it!=dependants.end();++it){
    if(*it==node_index){
      break;
    }
  }
  if(it!=dependants.end()){
    it=dependants.erase (it);
  }
  else{
    cerr<<"don't have such dependant!"<<endl;
    exit(1);
  }
}


/*-------------------------------------------------------------------------------
 * @Removes all dependents of the node
-------------------------------------------------------------------------------*/


void Node::rm_all_dependants()
{
  dependants.clear();
} 


/*-------------------------------------------------------------------------------
 * Sets the protect_status to 1
 * Node cannot be attacked
-------------------------------------------------------------------------------*/


void Node::protect_node()
{
  protect_status=1;
}


/*-------------------------------------------------------------------------------
 * Sets the protect_status to 0
 * Node can be attacked
-------------------------------------------------------------------------------*/


void Node::unprotect_node()
{
  protect_status=0;
}


/*-------------------------------------------------------------------------------
 * Checks if the node is protected
 * @Returns a boolen 
-------------------------------------------------------------------------------*/


bool Node::protect_check()
{
  if(protect_status) return true;
  else return false;
}


/*-------------------------------------------------------------------------------
 * Updates the dependence value to input integer
-------------------------------------------------------------------------------*/


void Node::set_dependence(int dependence_value){
  dependence = dependence_value;
}


/*-------------------------------------------------------------------------------
 * Returns dependence value
-------------------------------------------------------------------------------*/


int Node::get_dependence()
{
  return dependence;
}


/*-------------------------------------------------------------------------------
 * Updates the local kcore threshold value
-------------------------------------------------------------------------------*/


void Node::set_threshold(int threshold_inp)
{
  threshold = threshold_inp;
}


/*-------------------------------------------------------------------------------
 * Returns the local threshold value
-------------------------------------------------------------------------------*/


int Node::get_threshold()
{
  return threshold;
}


#endif
