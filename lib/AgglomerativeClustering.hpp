#include <vector>
#include "Cluster.hpp"
#include "Point.hpp"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/mutex.h"
#include "cilk/cilk.h"

using namespace std;

#ifndef agglomerative_class
#define agglomerative_class

class AgglomerativeClustering {
 
  private:
    
    vector<Cluster*> clusters;
    vector<Cluster*> fromPointsToClusters (vector<Point*> points);
    tbb::mutex mutex;
  
  public:
    
    AgglomerativeClustering (vector<Point*> points);
    Cluster* start();
    Cluster* parallelStart();
    Cluster* openMPStart();
    Cluster* cilkStart();
    vector<Cluster*> getClusters();
    void removeRepetitions();
  
};

#endif
