#include <iostream>
#include <vector>
#include <list>
#include "Triangle.h"

#ifndef CLIPPING_H
#define CLIPPING_H

class Clipping
{

public:
	Clipping() {}

	std::list<Triangle> clip(std::vector<Triangle>& triangles);
	void aux(std::vector<Vertex>& vertices, int component_Index, std::vector<Vertex>& new_triangles, std::vector<Triangle>& finalListOfTriangles);
	void buildTriangles(std::vector<Vertex>& listOfTheVertices, std::vector<Triangle>& finalListOfTriangles);
};

#endif