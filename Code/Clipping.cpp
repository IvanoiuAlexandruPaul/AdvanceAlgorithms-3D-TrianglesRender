#include<iostream>
#include <vector>
#include <Triangle.h>
#include <list>



class Clipping {

	public: 
		Clipping(std::vector<Triangle> triangles, double width, double height, double depth){
			this->width = width;
			this->height = height;
			this->depth = depth; 
			this->triangles = triangles;
		}
		
		std::vector<Triangle> get_triangles(){
			return this->triangles; 
		}

		std::vector<Triangle> clip(std::vector<Triangle> triangles);
		void  aux(std::vector<Vertex> vertices, int component_Index,std::vector<Vertex> new_triangles, double axis);
		void BuildTringles(std::vector<Vertex> v);
		

	private: 
		double width; 
		double height; 
		double depth;
		std::vector<Triangle> triangles; 
		std::vector<Triangle> Final_List_of_Triangles;
};


std::vector<Triangle> Clipping::clip(std::vector<Triangle> triangles){
	std::vector<Vertex> auxiliartriangles;
	std::vector<Vertex> all_vertex = {};
	for(Triangle t:triangles){
		for(int i = 0; i < 3; i++)
			aux(t.get_vertex(), i, auxiliartriangles,1.0f);
	}	

	return Final_List_of_Triangles;
};

void Clipping::aux(std::vector<Vertex> vertices, int component_Index ,std::vector<Vertex> result_vertices, double componentFactor){

		Vertex previousVertex = vertices[(vertices.size() - 1)];  //l'ultimo vertex nella lista
		double previousComponent = previousVertex.Get(component_Index) * componentFactor;
		bool previousInside = previousComponent <= previousVertex.get_w(); // se il nostro componente è dentro la zona di clipping


		for(auto& it : vertices){
			Vertex currentVertex = it;
			double currentComponent = currentVertex.Get(component_Index) * componentFactor;
			bool currentInside = currentComponent <= currentVertex.get_w();

			if(currentInside ^ previousInside) // se il nostro current è dentro e il previous non lo è   o viceversa 
			{
				//è la distanza che ci server per poter mettere dentro il punto C - ricordati l'esempio video della retta 
				double lerpAmt = (previousVertex.get_w() - previousComponent) /
					((previousVertex.get_w() - previousComponent) - 
					 (currentVertex.get_w() - currentComponent));

				result_vertices.push_back(previousVertex.Lerp(currentVertex, lerpAmt));
			}

			if(currentInside)
			{
				result_vertices.push_back(currentVertex);
			}
			previousVertex = currentVertex;
			previousComponent = currentComponent;
			previousInside = currentInside;
		}
		buildTriangles(result_vertices);
};

void buildTriangles(std::vector<Vertex> listOfTheVertices){
	
	Vertex tempVertex = listOfTheVertices[0];
	listOfTheVertices.erase(listOfTheVertices.begin()+0);
	for(int i=0; i<=listOfTheVertices.size();++i){
		if(listOfTheVertices.size()>=2){
			Triangle TempTriangle=  Triangle(tempVertex,listOfTheVertices[i],listOfTheVertices[i+1]);
			listOfTheVertices.erase(listOfTheVertices.begin()+0);
			Final_List_of_Triangles.push_back(TempTriangle);
		}	
	}
}
