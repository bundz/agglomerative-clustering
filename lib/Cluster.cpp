#include "Cluster.hpp"

using namespace std;

Cluster::Cluster (Cluster* cluster1, Cluster* cluster2) {

  this->left = cluster1;
  this->right = cluster2;
  this->name = cluster1->name + cluster2->name;
  this->point = centerPoint(cluster1->point, cluster2->point);

}

Cluster::Cluster (Point* point) {

  this->point = point;
  this->name = point->name;

}

Cluster* Cluster::findNearest (vector<Cluster*> clusters) {

  Cluster* nearest;
  float nearestDistance = 9999999;

  for(int i = 0; i < clusters.size(); i++) {

    float actualDistance = this->distance(clusters[i]);

    if(this != clusters[i] && actualDistance < nearestDistance) {

      nearest = clusters[i];
      nearestDistance = actualDistance;

    }

  }

  return nearest;

}
  
float Cluster::distance (Cluster* from) {
  return sqrt(pow((this->point->x - from->point->x), 2) + 
             pow((this->point->y - from->point->y), 2));
}

Point* Cluster::centerPoint(Point* a, Point* b) {
  Point* aux = new Point;
  
  aux->x = (a->x + b->x)/2;
  aux->y = (a->y + b->y)/2;
  
  return aux;
  
}

string Cluster::getName () {
  return this->name;
}

Point* Cluster::getPoint () {
  return this->point;
}

bool Cluster::isThere(vector<Cluster*> clusters) {
  
  for(int i = 0; i < clusters.size(); i++) {
    
    if((this->point->x == clusters[i]->point->x) && (this->point->y == clusters[i]->point->y)) {
      
      return true; 
      
    }
    
  }
  
  return false;
}
