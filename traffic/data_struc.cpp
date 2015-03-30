#include "data_struc.h"

using namespace std;

graph::graph(ifstream &ifs) {
	int i,j,n;
	ifs >> n;
	this->nVertices = n;
	for (i = 0; i < n; i++) 
		ifs >> this->vertexArray[i].name;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			ifs >> this->adjMatrix[i][j];
		assert (this->adjMatrix[i][i] == 0);
	}
	if (DEBUG)
		this->print();
}

graph::graph() {
	int i,j,n;
	cout << "Input number of vertices" << endl;
	cin >> n;
	assert (n < MAXVEX);
	this->nVertices = n;
	cout << "Input name of vertices (separated by space)"<< endl;
	for (i = 0; i < n; i++) 
		cin >> this->vertexArray[i].name;
	cout << "Input data of adjacent matrix " << endl;
	for (j = 0; j < n; j++) 
		cout << this->vertexArray[j].name << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) 
			cin >> this->adjMatrix[i][j];
		assert (this->adjMatrix[i][i] == 0);
	}
	cout << "Input finished" << endl;
}


int graph::getVertexIndex(vertex &vex) {
	int i;
	for (i = 0; i < this->nVertices; i++) 
		if (vex.name == this->vertexArray[i].name)
			break;
	if (i >= this->nVertices) //if vertex not found
		return -1;
	return i;
}

bool graph::isAdjacent(vertex &v1, vertex &v2) {
	int v1_index = this->getVertexIndex(v1);
	int v2_index = this->getVertexIndex(v2);
	if (this->adjMatrix[v1_index][v2_index] == 1 || this->adjMatrix[v2_index][v1_index] == 1)
		return true;
	else
		return false;
}

int graph::getDegree(vertex &vex) {
	int i, count=0;
	int index = this->getVertexIndex(vex);
	for(i=0; i<this->nVertices; i++) 
		if (this->adjMatrix[index][i])
			count++;
	return count;
}

vertex* graph::getNeighbors(vertex &vex) {
	int degree = this->getDegree(vex);
	int i,j;
	int index = this->getVertexIndex(vex);
	if (degree == 0)
		return NULL;
	vertex* vertices = new vertex[degree];
	for (i = 0, j = 0; i < this->nVertices; i++) { //iterate over adjMatrix
		if (this->adjMatrix[index][i] == 1) {
			vertices[j] = this->vertexArray[i];
			j++;
		}
	}
	return vertices;
}

int graph::numberOfVertices(void) {
	return this->nVertices;
}

vertex* graph::getAllVertices(void) {
	vertex* vertices = new vertex[nVertices];
	for (int i=0; i<nVertices; i++) 
		vertices[i] = this->vertexArray[i];
	return vertices;
}

void graph::print(void) {
	int i,j;
	for (i=0; i < this->nVertices; i++) {
		vertex &theVex = this->vertexArray[i];
		vertex *neighborVertices = this->getNeighbors(theVex);
		int neighborsCount = this->getDegree(theVex);
		if (neighborsCount == 0)
			cout << theVex.name << " has no neighbors "<< endl;
		else {
			j=0; // index of neighborVertices
			cout << theVex.name << " has neighbor(s): ";
			while (j < neighborsCount) {
				cout << neighborVertices[j].name << " ";
				j++;
			}
			cout << endl;
		}
		delete[] neighborVertices;
	}
}

setOfVertex::setOfVertex() {
	number = 0;
	head = NULL;
	last = NULL;
}

void setOfVertex::addItem(vertex & vex) {
	if (!isIn(vex)) {
		if (head == NULL) {
			head = new vertexNode;
			head->theVertex = vex;
			head->next = NULL;
			last = head;
		}
		else {
			last->next = new vertexNode;
			last = last->next;
			last->theVertex = vex;
			last->next = NULL;
		}
		number++ ;
	}
}

void setOfVertex::removeItem(vertex &vex) {
	if (isIn(vex)) {
		if (head->next == NULL) {
			number = 0; //if there is only one item
			delete head;
			head = NULL;
			last = NULL;
		}
		else if (head->theVertex.name == vex.name) { //if remove the head
			head = head->next;
			number--;
		}
		else {
			vertexNode* v = head;
			vertexNode* vNext = v->next;
			do {
				if (vNext->theVertex.name == vex.name) {
					v->next = vNext->next;
					number--;
					break;
				}
				v = v->next;
				vNext = vNext->next;
			} while (vNext != NULL);
			if (v->next == NULL) //if last is removed
				last = v;
		}
	}
}

bool setOfVertex::isIn(vertex &vex) {
	if (head == NULL)
		return false;

	vertexNode* v = head;
	do {
		if (v->theVertex.name == vex.name)
			return true;
		v = v->next;
	} while (v != NULL);
	return false;
}

bool setOfVertex::isEmpty(void) {
	return (this->head == NULL);
}

int setOfVertex::numberOfItems (void) {
	return this->number;
}

vertex& setOfVertex::getItem(void) {
	assert (head != NULL);
	return head->theVertex;
}