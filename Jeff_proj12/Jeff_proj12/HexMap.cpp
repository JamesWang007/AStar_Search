#include "HexMap.h"
#include<iostream>
#include<utility>
#include <fstream>
using namespace std;
using std::cout;
using std::endl;
typedef std::pair<unsigned int, unsigned int> Coord;
Coord hex_to_pair(unsigned int hexID)
{
  unsigned int x=hexID/100;
  unsigned int y=hexID%100;
  return(Coord(40+(x-2)*49, 40+(y-1)*56-(x%2)*56/2));
}

HexMap::HexMap(unsigned int startingHexID)
{
  path.push(startingHexID);
}

void HexMap::add(unsigned int hexID)
{
  path.push(hexID);
}

HexMap::~HexMap()
{
	ofstream file;
	file.open("res.html");

	file.precision(3);
	file << std::fixed;

	file << "<!DOCTYPE html>" << endl;
	file << "<html>" << endl;
	file << "<title>Hex Map Pathfinding</title>" << endl;
	file << "<style>" << endl;
	file << "body { " << endl;
	file << "background-image: url(hex_map.jpg); " << endl;
	file << "background-repeat: no-repeat; " << endl;
	file << "}" << endl;
	file << "</style>" << endl;
	file << "<body>" << endl;

	file << "<svg width=\"775\" height=\"573\">" << endl;

	file << "<polyline points=\"";
	while(!path.empty())
	{
		Coord point=hex_to_pair(path.front());
		path.pop();
		file << point.first << "," << point.second << " ";
	}
	file << '\"' << endl;
	file << "style=\"fill:none;stroke:blue;stroke-width:6\" />" << endl;
	file << "</svg>" << endl;
	file << "</body>" << endl;
	file << "</html>" << endl;
}
