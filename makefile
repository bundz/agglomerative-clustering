all:
	g++-5 main.cpp lib/*.cpp -o main -ltbb -fopenmp -fcilkplus
