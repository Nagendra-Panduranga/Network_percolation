/*-------------------------------------------------------------------------------
 * 1. Function to build networks with desired degree distribution
 * 2. Function to establish coupling between two networks
 * 3. Functions to set kcore threshold for nodes in a network
 * @Author: Nagendra Panduranga
-------------------------------------------------------------------------------*/


#ifndef NET_ALGO_HPP
#define NET_ALGO_HPP


/*-------------------------------------------------------------------------------
 * Builds connections between nodes in a network 
 * Degree distribution of network is a poissonian
-------------------------------------------------------------------------------*/


inline void lt_ER_algo(Graph & network, float avg_degree)
{

  
  int num_nodes = network.size();

  // indices of two nodes to be connected
  int idx1, idx2;

  // Connects two randomly chosen nodes until the average of degree of nodes is avg_degree
  for(int i=0;i<int(num_nodes*avg_degree/2);){

    //randomly choose two node indices
    idx1=int(srand()*num_nodes);
    idx2=int(srand()*num_nodes);

    // connect nodes idx1 and idx2 if they are not connected
    if((idx1!=idx2)&&(!network.connection_check(idx1,idx2))){
      ++i;
      network.insert_connection(idx1,idx2);
    }
  }
}


/*-------------------------------------------------------------------------------
 * @params two graph objects that needs to be interdependent
 * Makes every node in first network dependent on node with same index in second network and vice versa
-------------------------------------------------------------------------------*/


void build_complete_dependence(Graph &network1, Graph &network2)
{

  int num_nodes = network1.size();

  // updates every node of network to be dependent on corresponding node in the 2nd network
  for (int i = 0; i <= num_nodes-1; i++){
    network1.set_dependence(i,1);
    network2.set_dependence(i,1);
  }
}


/*-------------------------------------------------------------------------------
 * @params two graph objects that needs to be interdependent
 * @param double prec number between 0 and 1 represents coupling  
 * Makes nodes interdependent in two networks such that fraction of nodes dependent isequal to the coupling
-------------------------------------------------------------------------------*/


void build_partial_dependence(Graph &network1, Graph &network2, double coupling){

  int num_dep_nodes;
  int num_nodes = network1.size();

//Maintain a set to keep count of nodes made dependent
  set<int> chosen_nodes_set;

  // Call complete dependence function
  if(coupling == 1.0){
    build_complete_dependence(network1, network2);}
  else{

    // Calculate the number of nodes to be made dependent
    num_dep_nodes = int(double(num_nodes)*coupling);

    // --------------Build dependence for first network -------------------------
    
    // Initialize the set 
    chosen_nodes_set.clear();

    
    while(chosen_nodes_set.size()< num_dep_nodes){
      
      // Randomly choose index of the node made dependent
      int node_idx = int(srand()*num_nodes);

      //if the node is not dependent
      if(!network1.get_dependence(node_idx)){
	network1.set_dependence(node_idx, 1);
        chosen_nodes_set.insert(node_idx);}
    }

    // --------------Build dependence for second network --------------------------

    // Initialize the set 
    chosen_nodes_set.clear();
    
    while(chosen_nodes_set.size()< num_dep_nodes){

      //Randomly choose index of the node made dependent
      int node_idx = int(srand()*num_nodes);

      //if the node is not dependent
      if(!network2.get_dependence(node_idx)){
	network2.set_dependence(node_idx, 1);
	chosen_nodes_set.insert(node_idx);}
    }
    chosen_nodes_set.clear();
  }
}



/*-------------------------------------------------------------------------------
 * Sets local kcore threshold for nodes in the network
 * @params one graph object
 * @param two integer threshold values to be set for nodes
 * @param two double prec probability of finding nodes with given thresholds
-------------------------------------------------------------------------------*/


void set_init_threshold_frac(Graph &net, int threshold1, double prob_thresh1, int threshold2 , double prob_thresh2){

   int num_nodes = net.get_num_vertices(); 
   int node_idx;
   int threshold_inp;


   // Randomly assign the local threshold values for each node in network
   for (int i = 0; i < num_nodes; i++){
     
     node_idx = i;

     // if random number < prob_thresh1, set local threshold = threshold1 
     if(srand() < prob_thresh1){
       threshold_inp = threshold1;}
     else{
       threshold_inp = threshold2;}
     
     net.set_threshold(node_idx, threshold_inp);   
   }
 }


#endif
