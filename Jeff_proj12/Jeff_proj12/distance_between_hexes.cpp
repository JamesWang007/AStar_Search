#include "distance_between_hexes.h"
#include<algorithm> // std::max
#include<cstdlib>   // std::abs
int distance_between_hexes(unsigned int starthex, unsigned int endhex)
{
  int firstA=starthex/100;
  int secondA=starthex%100;
  int firstB=endhex/100;
  int secondB=endhex%100;
  int xA=secondA-(firstA+1)/2;   
  int yA=firstA;
  int xB=secondB-(firstB+1)/2;
  int yB=firstB;
  int dx=xB-xA;
  int dy=yB-yA;
  return(std::max(std::abs(dx), std::max(std::abs(dy), std::abs(dx+dy))));
}
