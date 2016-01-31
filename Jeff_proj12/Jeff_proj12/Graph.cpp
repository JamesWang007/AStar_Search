#include"Graph.h"
#include<iostream>
#include<queue>
#include<map>
#include<limits>
using namespace std;
void Graph::display()
{
  cout << "Graph with " << order() << " nodes and " << size() << " edges." << endl;
}

Graph::~Graph()
{
}
