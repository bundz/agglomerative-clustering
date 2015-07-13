#include "utils.hpp"

vector<Point*> generatePoints (int num) {
  
  vector<Point*> points (0);
  Point* point;
  
  for(int i = 0; i < num; i++) {
    
    point = new Point;
    
    point->x = rand() % 10000;
    point->y = rand() % 10000;
    
    stringstream ss;
    
    ss << i;
    
    point->name = "p" + ss.str();
    
    if (!vectorHas(points, point)) {
      
      points.push_back(point);
      
    } else {
     
      i--;
      
    }
    
    
    
  }
  
  return points;
  
}

bool vectorHas (vector<Point*> points, Point* point) {
  
  for(int i = 0; i < points.size(); i++) {
   
    if ((points[i]->x == point->x) && (points[i]->y == point->y) ) {
      return true;
    }
    
  }
  
  return false;
  
}

