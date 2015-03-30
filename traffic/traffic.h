#ifndef TRAFFIC_H_
#define TRAFFIC_H_
#include "data_struc.h"

class traffic : public graph {
public:
	traffic(std::ifstream &ifs) : graph (ifs) {}
	int solve(void);
	void printSolution(void);
private:
	int colors;
	setOfVertex solutionSet[10];
};

#endif