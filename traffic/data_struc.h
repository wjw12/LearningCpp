#ifndef DATA_STRUC_H_
#define DATA_STRUC_H_
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#define DEBUG 1
#define MAXVEX 100

typedef struct {
	std::string name;
} vertex;

class graph {
public:
	graph();
	graph(std::ifstream &ifs);
	bool isAdjacent(vertex &v1, vertex &v2);
	int getDegree(vertex &vex);
	vertex* getNeighbors(vertex &vex);
	vertex* getAllVertices(void);
	int numberOfVertices(void);
	void print(void);
private:
	int getVertexIndex(vertex &vex);
	vertex vertexArray[MAXVEX];
	int nVertices;
	int adjMatrix[MAXVEX][MAXVEX];

};

typedef struct vertexNode{
	vertex theVertex;
	vertexNode* next;
} vertexNode;

class setOfVertex {
public:
	setOfVertex ();
	void addItem(vertex &);
	void removeItem(vertex &);
	bool isIn(vertex &);
	bool isEmpty(void);
	int numberOfItems(void);
	vertex& getItem(void);
private:
	int number;
	vertexNode* head;
	vertexNode* last;
};


#endif /* DATA_STRUC_H_ */