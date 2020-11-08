#include "Clipping.h"

std::vector<Triangle> Clipping::clip(std::vector<Triangle>& triangles)
{
	std::vector<Vertex> auxiliartriangles;
	std::vector<Triangle> finalListOfTriangles;
	std::vector<Vertex> all_vertex = {};
	for (Triangle t : triangles)
	{
		for (int i = 0; i <= 3; ++i){
			std::vector<Vertex> vertex = t.get_vertex();
			aux(vertex , i, auxiliartriangles, finalListOfTriangles);
		}
	}

	return finalListOfTriangles;
};

void Clipping::buildTriangles(std::vector<Vertex>& listOfTheVertices, std::vector<Triangle>& finalListOfTriangles)
{

	Vertex tempVertex = listOfTheVertices[0];
	listOfTheVertices.erase(listOfTheVertices.begin() + 0);
	for (int i = 0; i <= listOfTheVertices.size(); ++i)
	{
		if (listOfTheVertices.size() >= 2)
		{
			Triangle TempTriangle = Triangle(tempVertex, listOfTheVertices[i], listOfTheVertices[i + 1]);
			listOfTheVertices.erase(listOfTheVertices.begin() + 0);
			finalListOfTriangles.push_back(TempTriangle);
		}
	}
}

void Clipping::aux(std::vector<Vertex>& vertices, int component_Index, std::vector<Vertex>& result_vertices, std::vector<Triangle>& finalListOfTriangles)
{

	Vertex previousVertex = vertices[(vertices.size() - 1)]; //l'ultimo vertex nella lista
	double previousComponent = previousVertex[component_Index];
	bool previousInside = previousComponent <= previousVertex.get_w(); // se il nostro componente è dentro la zona di clipping

	for (auto &it : vertices)
	{
		Vertex currentVertex = it;
		double currentComponent = currentVertex[component_Index];
		bool currentInside = currentComponent <= currentVertex.get_w();

		if (currentInside ^ previousInside) // se il nostro current è dentro e il previous non lo è   o viceversa
		{
			// L = (1-B)/(1-B)-(1-C)
			double lerpAmt = (currentVertex.get_w() - currentComponent) /
							 ((currentVertex.get_w() - currentComponent) -
							  (previousVertex.get_w() - previousComponent));

			//This is the vertex that you will find inside the screen not ouside
			result_vertices.push_back(lerp(currentVertex, previousVertex, lerpAmt));
		}

		if (currentInside)
		{
			result_vertices.push_back(currentVertex);
		}

		previousVertex = currentVertex;
		previousComponent = currentComponent;
		previousInside = currentInside;
	}
	buildTriangles(result_vertices, finalListOfTriangles);
};
