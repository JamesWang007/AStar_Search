#ifndef HEX_MAP_H
#define HEX_MAP_H
#include<queue>
#include<utility>
using std::queue;
class HexMap {
  public:
    HexMap(unsigned int startingHexID);
    ~HexMap();
    void add(unsigned int hexID);
  private:
    queue<unsigned int> path;
};
#endif
