#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include "./lib/Config.hpp"
#include "./lib/Point.hpp"
#include "./lib/Cluster.hpp"
#include "./lib/AgglomerativeClustering.hpp"
#include "./lib/utils.hpp"
#include "tbb/tbb.h"
#include "tbb/tick_count.h"

using namespace std;

int main (int argc, char* argv[]) {
   
  Config config = new Config(argc, argv);
  
  tbb::tick_count tick_start, tick_end;
  vector<Point*> points;
  AgglomerativeClustering* AC;
  Cluster* c;
  clock_t start,end;
  int num_threads = 1;
  int num_points = 10;
  int times = 0;
  
  cout << "Points,Threads,SequentialTime,TBB,OPENMP,CILK_PLUS" << endl;
  
  for(num_points = 10; num_points < 1000000; num_points = num_points * 10) {
        
    points = generatePoints(num_points);
    
    
    for(num_threads = 1; num_threads < 10; num_threads = num_threads * 2) {
      
      tbb::task_scheduler_init init(num_threads);
     
      for(times = 0; times < 30; times++) {
       
        cout << num_points << "," << num_threads << ",";
        
        AC = new AgglomerativeClustering(points);
        start = clock();
        c = AC->start();
        end = clock();
        
        cout << ((double) end-start) / CLOCKS_PER_SEC << ",";
        
        AC = new AgglomerativeClustering(points);
        
        tick_start = tbb::tick_count::now();
        c = AC->TBBStart();
        tick_end = tbb::tick_count::now();
        
        cout << (tick_end - tick_start).seconds() << ",";
		  
		AC = new AgglomerativeClustering(points);
        
	  	start = clock();
        c = AC->openMPStart();
		end = clock();
        
        cout << ((double) end - start) / CLOCKS_PER_SEC << ",";
        
        AC = new AgglomerativeClustering(points);
        
	  	start = clock();
        c = AC->cilkStart();
		end = clock();
        
        cout << ((double) end - start) / CLOCKS_PER_SEC << endl;
        
      }
      
      
    }
    
  }
  
}

