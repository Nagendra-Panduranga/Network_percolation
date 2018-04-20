/*-------------------------------------------------------------------------------
 * Simulates k-core percolation on single network
 * Calcualtes biggest cluster size as a function of percolation probability
 * @Author: Nagendra Panduranga
-------------------------------------------------------------------------------*/

using namespace std;
#include <iostream>

#include <fstream>
#include <set>

#include <string>
#include <sstream>


// Random number generator
#include "./statool/srand.hpp"


// Node and graph data structures
#include "node.hpp" 
#include "graph.hpp"


// Network building algorithm file
#include "net_algo.hpp"


// Percolation process functions
#include "net_ops.hpp"


/*-------------------------------------------------------------------------------
 * Main function: Executes the following steps
 * Simulates a kcore percolation in a single network
 * Builds a single network with poissonian degree distribution
 * Randomly removes nodes with a percolation probability
 * Finds the largest kcore cluster 
 * Repeats for different percolation probability
 * Returns int Exit code
 -------------------------------------------------------------------------------*/


int main(){

  
  // Initialize the random number generator
  initsrand(1);

  
  // Number of nodes in each network
  const int num_nodes = 1000000;

  
  // Average degree for each network
  float avg_degree = 10.0;  
  
  // kcore threshold values randomly chosen from
  int threshold1, threshold2;

  
  // Declare fraction of nodes set to have threshold1
  double frac_of_nodes_thresh1; 

  
  // Number of pruning iterations before biggest cluster stabilizes
  int num_of_prune_iterations; 

  
  // Percolation probability
  double percolation_prob;

  
  // Vector stoing node indices in largest cluster
  vector<int> cluster_big;

  
  // Fractional size of giant component ( biggest cluster)
  double Giant_comp_frac;
 
  
  // Read parameters for the network from a input file
  cin >> threshold1;
  cin >> frac_of_nodes_thresh1;
  cin >> threshold2;

  
  // Output file
  ofstream output_file;
  string file_name;


  // Convert Parameter values to string for output filename

  ostringstream ostr_num_nodes;
  ostr_num_nodes << double(num_nodes);
  
  ostringstream ostr_frac_thresh1;
  ostr_frac_thresh1 << frac_of_nodes_thresh1;

  ostringstream ostr_thresh1, ostr_thresh2;
  ostr_thresh1 << threshold1;
  ostr_thresh2 << threshold2;

  ostringstream ostr_avg_degree;
  ostr_avg_degree << avg_degree;
  
  file_name="./data/GCvsprobNn"+ ostr_num_nodes.str()+"avgdeg_"+ ostr_avg_degree.str() +"L1_"+ ostr_thresh2.str()+"r_"+ ostr_frac_thresh1.str()+"L2_"+ ostr_thresh2.str()+".dat";
  
  
  // Output run parameters to screen
  cout << "Number of nodes in the network  = " << num_nodes  << endl;
  cout << "\n Average degree of nodes in the network is " << avg_degree << endl;
  cout << "\n kcore thresholds are: " <<  threshold1 << "  " << threshold2 << endl;
  cout << "fraction of nodes with threshold1 is " << frac_of_nodes_thresh1 << endl; 
  cout << "data is written to " << file_name.c_str() << endl;

  
  /*-------------------------------------------------------------------------------
   * Build network and initialize
   -------------------------------------------------------------------------------*/

  
  // Create two networks 
  Graph netA(num_nodes); 

  // Create two backup networks
  Graph netA_initial(num_nodes); 

  // Build two ER networks
  lt_ER_algo(netA_initial,avg_degree);  


  // Set local kcore thresholds for nodes
  set_init_threshold_frac(netA_initial, threshold1, frac_of_nodes_thresh1, threshold2, 1.0 - frac_of_nodes_thresh1); 



  /*-------------------------------------------------------------------------------
   * Simulates percolation process
  -------------------------------------------------------------------------------*/

  
  // open the output file stream
  output_file.open(file_name.c_str());

  
  // Set the step size for percolation prob increment
  double delta_perco_prob = 0.005; 


  // Loop for different percolation probabilities
  for(percolation_prob = 1.00 ; percolation_prob >= (1.0/avg_degree); percolation_prob -= delta_perco_prob)
    {

      
      // Use Backup network to initialize the network to run simulation for new percolation_prob
      netA = netA_initial;  

    
      // Remove randomly chosen nodes from both networks
      initial_random_attack(percolation_prob, netA);
   

      // Remove nodes with degree less than the local threshold to satisfy the kcore condition
      num_of_prune_iterations = network_prune(netA);
 

      // Find the biggest cluster
      find_biggest_cluster(netA, cluster_big);
      Giant_comp_frac = double(cluster_big.size())/double(num_nodes);

      
      // Output result to file
      output_file << 1.0 - percolation_prob <<"  "<< Giant_comp_frac  << "  " << num_of_prune_iterations << endl;	        

    } 

  
  // close the output file stream
  output_file.close();
 
  
  return 0;
}



