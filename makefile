all:
	g++ main.cpp lib/*.cpp -o main -ltbb -fopenmp