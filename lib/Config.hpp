class Config {
 
  private:
    
    bool hasTBB; 
    bool hasCpp11; 
    bool hasCilk; 
    bool hasOpenMP; 
    bool hasSequential; 
    int threadsNum;
    int pointsNum;
  
  public:
    
    Config (int argc, char* argv[]);
    bool hasTBB(); 
    bool hasCpp11(); 
    bool hasCilk(); 
    bool hasOpenMP(); 
    bool hasSequential(); 
    int getThreadsNumber(); 
    int getPointsNumber(); 
  
};