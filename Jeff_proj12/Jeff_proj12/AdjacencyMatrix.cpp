#include <iostream>
#include "AdjacencyMatrix.h"
#include <vector>
#include <assert.h>
#include <set>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix()
{
}

AdjacencyMatrix::AdjacencyMatrix(unsigned int num_vertices)
{
	this->_num_vertices = num_vertices;
	v.resize(num_vertices);
	for(unsigned int i = 0; i < num_vertices; i++)
	{
		v[i].resize(num_vertices, 0);
	}

	this->pvm = NULL;
}

void AdjacencyMatrix::add_edge(unsigned int p, unsigned int q, unsigned w)
{
	if(p < v.size() && q < v.size() && p != q)
	{
		v[p][q] = w;
		v[q][p] = w;
	}
}

void AdjacencyMatrix::display()
{
	Graph::display();
	//  cout << "Graph with " << v.size() << " nodes" << endl;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		for (unsigned int j = 0; j < v[i].size(); j++)
		{
			if (i < j && v[i][j] > 0)
			{
				cout << "(" << i << "," << j << ")" << endl;
			}
		}
	}
}

void AdjacencyMatrix::remove_edge(unsigned int p, unsigned int q)
{
	if(p < v.size() && q < v.size() && p != q);
	{
		v[p][q] = 0;
		v[q][p] = 0;
	}
}

unsigned int AdjacencyMatrix::add_vertex()
{
	this->_num_vertices = v.size() + 1;
	v.resize(this->_num_vertices);
	for (int i = 0; i < this->_num_vertices; i++)
	{
		v[i].resize(this->_num_vertices);
	}
	if (this->pvm == NULL)
	{
		return 0;
	}

	return this->pvm->GenerateNextId(); // ID
}

void AdjacencyMatrix::remove_vertex(unsigned int p)
{	
	for (int i = 0; i < this->_num_vertices; ++i)
	{
		v[i].erase(v[i].begin() + p);		
	}
	v.erase(v.begin() + p);
	this->_num_vertices--;
}

unsigned int AdjacencyMatrix::size()
{
	int n_vertices = 0;
	for(int i = 0; i<v.size(); i++)
		for (int j = 0; j<v[i].size(); j++)
			if(i<j && v[i][j] > 0)
			n_vertices++;
	return n_vertices;
}

unsigned int AdjacencyMatrix::order()
{
	int n_vertices = 0;
	for (int i = 0; i<v.size(); i++)
		for (int j = 0; j<v[i].size(); j++)
			if (i<j && v[i][j] == true)
				n_vertices++;
	return n_vertices;
}

unsigned int AdjacencyMatrix::degree(unsigned int p)
{
	int count=0;
	for(int i=0; i<v[p].size(); i++)
	if(v[p][i] > 0)
		count++;
	return count;
}

set<unsigned int> AdjacencyMatrix::neighbors(unsigned int p)
{
	set<unsigned int>matrix_neighbors;
	for(int i = 0; i < v[p].size(); i++)
	if(v[p][i] > 0)
		matrix_neighbors.insert(i);
	return matrix_neighbors;
}


/*
void AdjacencyMatrix::Controller()
{

}
*/

TerrainCost::TerrainCost()
{
}

TerrainCost::TerrainCost(string path)
{
	ifstream file;
	file.open(path);
	if (!file.is_open())
	{
		cout << path << " file is not open.\n";
		return;
	}
	while (!file.eof())
	{
		char c;
		int cost;

		file >> c >> cost;
		this->cost[c] = cost;
	}

}

TerrainCost::~TerrainCost()
{
}

int TerrainCost::CostCalculator(string str)
{
	if (str == "" || this->cost.size() == 0)
	{
		return 0;
	}
	int sum = 0;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		sum += this->cost[c];
	}
	return sum;
}




VertexManager::VertexManager()
{
}


VertexManager::~VertexManager()
{
}

void VertexManager::LoadEdgeData(string path)
{
	// load mapedges.data
	ifstream mapedges;
	mapedges.open(path);
	if (!mapedges.is_open())
	{
		cout << "file mapedges is not open\n";
		return;
	}

	int src, dst;
	string wt;
	while (!mapedges.eof())
	{
		mapedges >> src >> dst >> wt;
		//cout << src << "\t" << dst << "\t" << ter << endl;
		VertexMapConnection vc(src, dst, wt);
		cList.push_back(vc);
	}
	mapedges.close();

	this->ListToVector();
	this->ParseIds();
	this->GenerateVertexes();
}


void VertexManager::ListToVector()
{
	this->_length = this->cList.size();
	this->cVector.reserve(this->_length);
	for (int i = 0; i < this->_length; i++)
	{
		this->cVector.push_back(this->cList.front());
		this->cList.pop_front();
	}
}

void VertexManager::ParseIds()
{
	for (int i = 0; i < this->cVector.size(); i++)
	{
		bool isin = false;
		for (int j = 0; j < this->ids.size(); j++)
		{
			if (this->ids[j] == this->cVector[i].start)
			{
				isin = true;
				break;
			}
		}
		if (isin)
		{
			continue;
		}
		else
		{
			this->ids.push_back(this->cVector[i].start);
		}
	}
}

void VertexManager::GenerateVertexes()
{
	this->vts.reserve(this->ids.size());
	for (int i = 0; i < this->ids.size(); i++)
	{
		this->vmap[this->ids[i]] = i;
		Vertex vt(this->ids[i], i);
		this->vts.push_back(vt);
	}
}

int VertexManager::GenerateNextId()
{
	if (this->ids.size() == 0)
	{
		return -1;
	}

	int lastId = this->ids.back();
	int first = lastId / 100;
	int second = lastId % 100;

	if (second < 10)
	{
		int newId = first * 100 + second + 1;
		this->ids.push_back(newId);
		int index = this->vts.size();
		Vertex vt(newId, index);
		this->vts.push_back(vt);
		this->vmap[newId] = index;
		return newId;
	}
	else
	{
		int newId = (1 + first) * 100 + 1;
		this->ids.push_back(newId);
		int index = this->vts.size();
		Vertex vt(newId, index);
		this->vts.push_back(vt);
		this->vmap[newId] = index;
		return newId;
	}

}