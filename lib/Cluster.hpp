#include <string>
#include <vector>
#include <cmath>
#include "Point.hpp"

using namespace std;

#ifndef cluster_class
#define cluster_class

class Cluster {
  
  private:
  
    Cluster* left;
    Cluster* right;
    Point* point;
    string name;
    float distance (Cluster* from);
    Point* centerPoint(Point* a, Point* b);

  public:
  
    Cluster (Point* point);
    Cluster (Cluster* cluster1, Cluster* cluster2);
    Cluster* findNearest (vector<Cluster*> clusters);
    string getName();
    Point* getPoint();
    bool isThere(vector<Cluster*> clusters);
  
};

#endif
