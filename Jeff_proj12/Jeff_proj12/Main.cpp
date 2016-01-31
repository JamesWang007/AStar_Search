#include <iostream>
#include <fstream>
#include <string>
#include "AdjacencyMatrix.h"
#include "distance_between_hexes.h"
#include <algorithm>
#include "HexMap.h"
#define INIFINITY 9999
using namespace std;

map<unsigned int, unsigned int> astar(unsigned, unsigned, AdjacencyMatrix &);

int main()
{
	// load mapedges.data
	VertexManager vm;
	vm.LoadEdgeData("mapedges.data");

	// populate the matrix
	int numOfVertex = vm.ids.size();
	AdjacencyMatrix am(numOfVertex);
	am.pvm = &vm;

	// load terrain_cost.data
	TerrainCost tc("terrain_costs.data");
	am.ptc = &tc;

	// test the loading
	cout << tc.cost['.'] << endl;
	cout << tc.cost['h'] << endl;	
	cout << tc.CostCalculator(".wt") << endl;

	// populate edges
	cout << "now populate edges into matrix:\n";
	for (unsigned int i = 0; i < vm.cVector.size(); i++)
	{
		int src = vm.cVector[i].start;
		int dst = vm.cVector[i].end;

		// populate into matrix
		int x = vm.vmap[src];
		int y = vm.vmap[dst];

		string wt = vm.cVector[i].weight_type;
		int weight = tc.CostCalculator(wt);

		am.add_edge(x, y, weight);

	}
	cout << "edge population is done!\n";

	cout << "prepare to call astar()\n";
	
	// Testing (309, 1605)
	int start_id = 601;
	int finish_id = 1605;
	int start = am.pvm->vmap[start_id];
	int finish = am.pvm->vmap[finish_id];
	map<unsigned int, unsigned int> path = astar(start, finish, am);
	vector<unsigned int> res;
	int next = finish_id;
	do
	{	
		next = path[next];		
		res.push_back(next);	
	} while (next != start_id);

	HexMap hm(finish_id);
	cout << finish_id << endl;
	for (vector<unsigned int>::iterator it = res.begin(); it != res.end(); it++)
	{
		hm.add(*it);
		cout << *it << endl;
	}
	cout << "path found\n";
	getchar();
	return 0;
}

bool which_is_closer(const unsigned& a, const unsigned& b)
{
	return (total_est_dist[a] > total_est_dist[b]);
}

// parameter: 
// start should be index
map<unsigned int, unsigned int> astar(unsigned int start, unsigned int finish, AdjacencyMatrix &am)
{
	int numOfVertex = am.pvm->vts.size();

	set<unsigned int> closed; //holds vertices we no longer process
	vector<unsigned int> open; //holds vertices we still need to process XXX
	// XXX no longer needed: set<unsigned int> visited;

	map<unsigned int, unsigned int> parent;//what is returned

	//should be number of vertices
	//holds the distance already traveled for each vertex
	vector<int> distance_traveled;
	//also, initialize to infinity: XXX
	distance_traveled.resize(numOfVertex, INIFINITY);

		//recall, total_est_dist is a global variable
		//Here, initialize it to infinity for all entries. # entries
		//equals number of vertices
	total_est_dist.resize(numOfVertex, INIFINITY);
		//BTW, total_est_dist for a vertex i is: 
		//  distance_traveled[i]+distance_between_hexes(starthex, i)


		//get ready to loop
	distance_traveled[start] = 0; //XXX
	total_est_dist[start] = distance_between_hexes(am.pvm->vertexToHex(start), am.pvm->vertexToHex(finish)); //XXX
	open.push_back(start); //add our starting point to 
	//XXX no longer needed  visited.insert(start); //add to our helper set

	//start the loop
	while (1)
	{
		//XXX
		//use pop_heap on open vector. then current=open.back(), then pop_back to remove it
		unsigned int current;
		//make_heap(open.begin(), open.end(), which_is_closer);
		pop_heap(open.begin(), open.end(), which_is_closer);
		current = open.back();
		open.pop_back();

		if (current == finish)//stopping condition
		//if (closed.size() == numOfVertex)
			return parent;
		//now don't forget to pop it off of open
		//make sure that we don't see this vertex again.

		//for (loop on nbor : neighbors of current) :
		for (auto& nbor : am.neighbors(current))
		{
			if (closed.find(nbor) != closed.end())
			{			
				//don't do it again. We've done it before
				continue;
			}

			int tentative_distance_traveled = 
				distance_traveled[current] + am.weight(current, nbor);
				//distance_between_hexes(am.pvm->vertexToHex(current), am.pvm->vertexToHex(nbor));
			//XXX      if(visited.count(nbor)==0)  
			//XXX      {
			//XXX        //add nbor to visited
			//XXX        //add nbor to the priority queue "open"
			//XXX      }
			//if nbor isnt in open vector
			if (find(open.begin(), open.end(), nbor) == open.end())
			{
				//add nbor to open vector
				open.push_back(nbor);
				//(re)make the heap
				//make_heap(open.begin(), open.end(), which_is_closer);
			}
			else if (tentative_distance_traveled >= distance_traveled[nbor])
			{
				continue; //Nope, visit next neighbor
			}
			parent[am.pvm->vertexToHex(nbor)] = am.pvm->vertexToHex(current); //best predecessor for this neighbor
			distance_traveled[nbor] = tentative_distance_traveled;
			total_est_dist[nbor] = distance_traveled[nbor] + distance_between_hexes(am.pvm->vertexToHex(nbor), am.pvm->vertexToHex(finish));
				//note that nbor and finish are vertices, 
				//but, distance_between_hexes takes two hex numbers.
				//Be sure to use vertexToHex for nbor and finish
				//XXX  here, (re)make_heap
			make_heap(open.begin(), open.end(), which_is_closer);
		}//end for loop		

		closed.insert(current);
	}//end while loop

	return parent;
}