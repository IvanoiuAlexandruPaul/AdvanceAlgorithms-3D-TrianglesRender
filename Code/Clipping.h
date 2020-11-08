#include <iostream>
#include <vector>
#include <list>
#include "Triangle.h"

#ifndef CLIPPING_H
#define CLIPPING_H

class Clipping
{

public:
	Clipping(std::vector<Triangle> triangles, double width, double height, double depth)
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
		this->triangles = triangles;
	}

	std::vector<Triangle> get_triangles()
	{
		return this->triangles;
	}

	std::vector<Triangle> clip(std::vector<Triangle> triangles);
	void aux(std::vector<Vertex> vertices, int component_Index, std::vector<Vertex> new_triangles, std::vector<Triangle> finalListOfTriangles);
	void buildTriangles(std::vector<Vertex> listOfTheVertices, std::vector<Triangle> finalListOfTriangles);

private:
	double width;
	double height;
	double depth;
	std::vector<Triangle> triangles;
};

#endif