#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <vector>
#include <assert.h>
#include "Graph.h"
#include <fstream>
#include <list>
#include <string>

using namespace std;

static vector<int> total_est_dist;

class TerrainCost
{
public:
	TerrainCost();
	TerrainCost(string);
	~TerrainCost();

	map<char, int> cost;
	int CostCalculator(string);

};

class VertexMapConnection
{
public:
	VertexMapConnection(int src, int dst, string wt)
		: start(src), end(dst), weight_type(wt)
	{
	}

	int start;
	int end;
	string weight_type;
};

class Vertex
{
public:
	Vertex(){}
	Vertex(int id, int index)
		:id(id), index(index)
	{
	}
	int id;
	int index;
};

class VertexManager
{
public:
	VertexManager();
	~VertexManager();

	vector <int> ids;
	vector <Vertex> vts;// vts[index] == id
	map<int, int> vmap;// id, index
	list <VertexMapConnection> cList;
	vector<VertexMapConnection> cVector;

	void LoadEdgeData(string);
	void ListToVector();
	void ParseIds();
	void GenerateVertexes();
	int GenerateNextId();

	int vertexToHex(unsigned index){ return this->vts[index].id; }

private:
	int _length; // total num of edges
};

class AdjacencyMatrix : public Graph{
  public:
    AdjacencyMatrix();
    AdjacencyMatrix(unsigned int);
    void add_edge(unsigned int, unsigned int, unsigned int);
    void display();
    void remove_edge(unsigned int, unsigned int);
    unsigned int add_vertex();
    void remove_vertex(unsigned int);
    unsigned int size();
    unsigned int order();
	int weight(unsigned int x, unsigned int y) { return this->v[x][y]; }
    unsigned int degree(unsigned int);
	std::set<unsigned int> neighbors(unsigned int p);

	//void Controller();
	VertexManager *pvm;
	TerrainCost *ptc;

  private:
    vector<vector<int> > v; 
	int _num_vertices;
};

//#include "AdjacencyMatrix.cpp"
#endif
