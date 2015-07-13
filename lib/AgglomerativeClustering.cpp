#include "AgglomerativeClustering.hpp"
#include <iostream>

using namespace std;

AgglomerativeClustering::AgglomerativeClustering (vector<Point*> points) {
  this->clusters = this->fromPointsToClusters(points);
}
  
Cluster* AgglomerativeClustering::start () {
  
  while (this->clusters.size() != 1) {

    vector<Cluster*> clusters_aux (0);
    int i = 0;

    while (i < this->clusters.size()) {
      Cluster* nearest = this->clusters[i]->findNearest(this->clusters);

      if(nearest->findNearest(this->clusters) == this->clusters[i]) {
        
        
        Cluster* cluster = new Cluster(nearest, this->clusters[i]);
        
        if(!cluster->isThere(clusters_aux)) {
          
          clusters_aux.push_back(cluster);
          
        }
        
        
      } else {
        
        clusters_aux.push_back(clusters[i]);  
        
      }

      i++;
    }

    this->clusters = clusters_aux;
    
  }

  return this->clusters[0];

}

struct Clusterize {
  
  vector<Cluster*> in_clusters; 
  vector<Cluster*>* out_clusters;
  
  void operator () (const tbb::blocked_range<int>& range) const {
    
    for(int i = range.begin(); i != range.end(); i++) {
      
      Cluster* nearest = in_clusters[i]->findNearest(in_clusters);

      if(nearest->findNearest(in_clusters) == in_clusters[i]) {
        
        Cluster* cluster = new Cluster(nearest, in_clusters[i]);
        (*out_clusters)[i] = cluster;
        
      } else {
        
        (*out_clusters)[i] = in_clusters[i];  
        
      }
      
    }
    
  }
  
};

Cluster* AgglomerativeClustering::TBBStart () {
  
  while (this->clusters.size() != 1) {
    
    vector<Cluster*> clusters_aux (this->clusters.size());
    
    Clusterize clusterize;
    
    clusterize.in_clusters = this->clusters;
    clusterize.out_clusters = &clusters_aux;
 
    tbb::parallel_for(tbb::blocked_range<int>(0, this->clusters.size()), clusterize); 
    
    this->clusters = clusters_aux;
    
    this->removeRepetitions();
    
  }

  return this->clusters[0];
}

Cluster* AgglomerativeClustering::openMPStart() {
  
    while (this->clusters.size() != 1) {

      vector<Cluster*> clusters_aux (0);
      
      #pragma omp parallel for shared(clusters_aux)
      for (int i = 0; i < this->clusters.size(); i++) {

        Cluster* nearest = this->clusters[i]->findNearest(this->clusters);

        if(nearest->findNearest(this->clusters) == this->clusters[i]) {

          Cluster* cluster = new Cluster(nearest, this->clusters[i]);
          #pragma omp critical(dataupdate)
          {
            clusters_aux.push_back(cluster);
          }
        } else {
          
          #pragma omp critical(dataupdate)
          {
            clusters_aux.push_back(this->clusters[i]);  
          }
        }
        
      }
      
      
      #pragma omp barrier
      
      this->clusters = clusters_aux;

      this->removeRepetitions();

    }
  
  return this->clusters[0];
}

Cluster* AgglomerativeClustering::cilkStart() {
  
    while (this->clusters.size() != 1) {
  
      vector<Cluster*> clusters_aux (0);
      
      cilk_for(int i = 0; i < this->clusters.size(); i++) {

        Cluster* nearest = this->clusters[i]->findNearest(this->clusters);

        if(nearest->findNearest(this->clusters) == this->clusters[i]) {

          Cluster* cluster = new Cluster(nearest, this->clusters[i]);
          
          mutex.lock();
          clusters_aux.push_back(cluster);
          mutex.unlock();
          
        } else {
          
          mutex.lock();
          clusters_aux.push_back(this->clusters[i]);  
          mutex.unlock();
      
        }
        
      }

      this->clusters = clusters_aux;

      this->removeRepetitions();

    }
  
  return this->clusters[0];
}


vector<Cluster*> AgglomerativeClustering::fromPointsToClusters (vector<Point*> points) {
  
  vector<Cluster*> newClusters (0);
  
  for(int i = 0; i < points.size(); i++) {
    
    newClusters.push_back(new Cluster(points[i]));
  
  }
  
  return newClusters;
  
}

vector<Cluster*> AgglomerativeClustering::getClusters() {
  return this->clusters;
}
                      
void AgglomerativeClustering::removeRepetitions() {

  
  for(int i = 0; i < this->clusters.size(); i++) {
   
    Cluster* cluster = this->clusters[i];
    vector<int> toRemove (0);
    
    for(int j = 0; j < this->clusters.size(); j++) {
      
      if(j != i && (cluster->getPoint()->x == this->clusters[j]->getPoint()->x) && 
        (cluster->getPoint()->y == this->clusters[j]->getPoint()->y)) {
        
        toRemove.push_back(j);
        
      }
      
    }
    
    for(int i = toRemove.size() - 1; i > -1; i--) {
      
      this->clusters.erase((this->clusters.begin() + toRemove[i]));
      
    }
    
  }
  
}
