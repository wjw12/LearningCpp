#include "traffic.h"

using namespace std;

int traffic::solve(void) {
	int color = 0;
	vertex* vertices = this->getAllVertices();
	int num = this->numberOfVertices();
	setOfVertex solved;
	int i,j;
	while (solved.numberOfItems() != num) {
		setOfVertex unavail;
		for (i=0; i<num; i++) { //iterate over all vertices
			vertex curr = vertices[i];
			if(solved.isIn(curr)) //skip if already solved
				continue;
			if( ! unavail.isIn(curr)){ //if current vertex can be colored
				solutionSet[color].addItem(curr);
				solved.addItem(curr);
				int degree = this->getDegree(curr);
				vertex* neighbors = this->getNeighbors(curr);
				for (int j=0; j<degree; j++)
					unavail.addItem(neighbors[j]); //set neighbors as unavailable
			}
		}
		color++;
	}
	this->colors = color;
	return color;
}

void traffic::printSolution(void) {
	cout<<"There are "<<colors<<" groups in total"<<endl;
	for (int i=0; i<colors; i++) {
		cout<<"Group "<<i+1<<" : ";
		while( ! solutionSet[i].isEmpty()) {
			vertex &item = solutionSet[i].getItem();
			cout<< item.name << ' ';
			solutionSet[i].removeItem(item);
		}
		cout<<'\n';
	}
}