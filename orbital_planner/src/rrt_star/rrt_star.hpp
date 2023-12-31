#ifndef RRT_STAR_H
#define RRT_STAR_H

#include "utils.hpp"
#include "tree.hpp"
#include "../dynamics/astrodynamics.hpp"
#include "../dynamics/lqr.hpp"
#include "../dynamics/simulation.hpp"

/* General params*/
#define DEBUG_DEV false
#define DEBUG_USR false

#define MAX_ANGLE 2*M_PI
#define RRT_STAR_NUM_ITER 1000000 //500000
#define RRT_STAR_STEP_EXTEND 1.0 //4.0
#define RRT_STAR_GOAL_TOL 2.0 //2.0

#define RRT_STAR_DEBUG_REWIRING false
#define RRT_STAR_DEBUG_LOCAL false
#define RRT_STAR_DEBUG_INTER false

#define RRT_STAR_GOAL_BIASED 0.2 //0.5
#define RRT_STAR_LOCAL_BIASED 0.2 //0.5
#define RRT_STAR_TIME_MAX 2990000000000000
#define RRT_STAR_REF_MAX 49000000000000000
#define RRT_STAR_STD_DEV 2.0
#define RRT_STAR_R_MIN 0.1*RRT_STAR_STEP_EXTEND
#define RRT_STAR_R_MAX 0.5*RRT_STAR_STEP_EXTEND

#define RRT_STAR_NEW_RADIUS 75.0
#define RRT_STAR_K_NEIGHBORS 10

#define RRT_STAR_KEEP_UNTIL_TIME_MAX false
#define RRT_STAR_NODE_REJECTION_ACTIVE true //not implemented
#define RRT_STAR_LOCAL_BIAS_ACTIVE true 

#define SIM_DT 0.5
#define SIM_COST_TOL 1.0
#define MAX_EXTENT_TRIALS 80

using namespace Astrodynamics;
using namespace Optimal;
using namespace Simulation;

class RRTStar{
	
	
	public:


		// Dynamics
		MatrixA A;
		MatrixB B;
		MatrixA Ad;
		MatrixB Bd;

		Simulator sim;


		RRTStar(State& starting_configuration, State& goal_configuration, double ***_plan, int *_plan_length);


		// Sample State - Goal Biased 
		void SampleConfiguration(State& sample_state, State& goal_state, bool& path_found);
		

		// Rewire function
		void Rewire(Tree& tree, std::shared_ptr<Graph_Node>& new_state_node, std::shared_ptr<Graph_Node>& parent_node, std::vector<std::shared_ptr<Graph_Node>>& near_nodes);


		double ComputePath(std::vector<State>& state_path);
		void SteerTowards(Tree& tree, State& sample_state, std::shared_ptr<Graph_Node>& nearest_node, State& next_state, Control& policy);
		void Step(MatrixA& A, MatrixB& B, MatrixK& K, const State& state, State& target_state, State& next_state, Control& control);

		// Do one iteration of LQR-RRT*
		void Iterate();

		// Returns True if an initial path has been found 
		bool PathFound();
		void Reset();

		// Returns a pointer to the current Tree 
		const Tree* GetTree() const;


		// Linearize and discretize 
		void UpdateLinearizedDiscreteDynamicsAround(const State& x, const Control& u);

		// Backtrack from the specified node to get the path from start node 
		void BacktrackToStart(std::vector<std::shared_ptr<Graph_Node>>& path, std::shared_ptr<Graph_Node> last_node_ptr);

		// Compute Quadratic Cost of the Path
		double ComputeQuadraticCost(const std::vector<std::shared_ptr<Graph_Node>>& path, const State& goal_state);





		// Utils Methods
		void _sample_goal_biased_config(State& sample_state, State& goal_state);
		void _sample_local_biased_config(State& sample_state);


	private:

		State start_config;
		State goal_config;
		double ***plan;
		int *plan_length;
		std::vector<std::shared_ptr<Graph_Node>> path;
		int count;
		bool path_found;
		int update_count;

		// Sampling
        int seed; // Change this value as needed
        // Create the Mersenne Twister engine with the fixed seed
        std::mt19937 gen;
        std::normal_distribution<double> distribution_rrt_star;
        std::uniform_real_distribution<double> distribution_local_bias;
		OrbitalSampler sampler;



		// LQR
		LQR lqr;
		MatrixQ Q;
		MatrixR R;
		MatrixS S;
		MatrixK K;
		Control zero_control;

		// Tree
		Tree tree;
		std::shared_ptr<Graph_Node> start_node;
		std::shared_ptr<Graph_Node> goal_node;
		std::shared_ptr<Graph_Node> new_state_node;


		// Find nearest states 
		// Need to change distance function in kd_tree.cpp to LQR distance
		std::shared_ptr<Graph_Node> FindNearestStateTo(Tree& tree, State& state, MatrixS& S);
		std::vector<std::shared_ptr<Graph_Node>> FindNearestStates(Tree& tree, State& new_state, const MatrixS& S);

		// Check if the state is valid
		bool ValidState(State& state);

		// Tree methods
		std::shared_ptr<Graph_Node> CreateTreeNode(Tree& tree, State& state);
		void AddToTree(Tree& tree, std::shared_ptr<Graph_Node> state_node, std::shared_ptr<Graph_Node> parent_state_node, MatrixS& S);
		
		// Choose Parent
		void ChooseParent(Tree& tree, std::shared_ptr<Graph_Node>& new_state_node, std::shared_ptr<Graph_Node>& parent_node, std::vector<std::shared_ptr<Graph_Node>>& near_nodes, MatrixS& S_new);




};

#endif // RRT_STAR_H

