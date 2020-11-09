#include "Clipping.h"

double linearInterpolation(double a, double b) {
    return (1 - a) / (1 - a - (1 - b));
}

Vertex interpolate(Vertex a, Vertex b) {
    double lx = linearInterpolation(a.get_x(), b.get_x());
    double ly = linearInterpolation(a.get_y(), b.get_y());
    double lz = linearInterpolation(a.get_z(), b.get_z());

    return Vertex(lx, ly, lz);
}

std::vector<Triangle> Clipping::clip(std::vector<Triangle> &triangles) {
    std::vector<Vertex> auxiliartriangles;
    std::vector<Triangle> finalListOfTriangles;
    std::vector<Vertex> all_vertex = {};
    for (Triangle t : triangles) {
        for (int i = 0; i <= 3; ++i) {
            std::vector<Vertex> vertex = t.get_vertex();
            aux(vertex, i, auxiliartriangles, finalListOfTriangles);
        }
    }

    return finalListOfTriangles;
};

/*

 for triangolo in triangoli:
    if c'è un vertice fuori da -1, 1:
        - Rompi il triangolo in vertici tutti dentro -1, 1
        - Raggruppa i nuovi vertici in triangoli.

 */

void Clipping::buildTriangles(std::vector<Vertex> &listOfTheVertices, std::vector<Triangle> &finalListOfTriangles) {
    Vertex tempVertex = listOfTheVertices[0];
    listOfTheVertices.erase(listOfTheVertices.begin() + 0);
    for (int i = 0; i <= listOfTheVertices.size() - 1; ++i) {
        Triangle TempTriangle = Triangle(tempVertex, listOfTheVertices[i], listOfTheVertices[i + 1]);
        listOfTheVertices.erase(listOfTheVertices.begin() + 0);
        finalListOfTriangles.push_back(TempTriangle);

    }

}

void Clipping::aux(std::vector<Vertex> &vertices, int component_Index, std::vector<Vertex> &result_vertices,
                   std::vector<Triangle> &finalListOfTriangles) {

    Vertex previousVertex = vertices[(vertices.size() - 1)]; //l'ultimo vertex nella lista
    double previousComponent = previousVertex[component_Index];
    bool previousInside =
            previousComponent <= previousVertex.get_w(); // se il nostro componente è dentro la zona di clipping

    for (auto &it : vertices) {
        Vertex currentVertex = it;
        double currentComponent = currentVertex[component_Index];
        bool currentInside = currentComponent <= currentVertex.get_w();

        if (previousInside && !currentInside) {
            Vertex v = interpolate(previousVertex, currentVertex);
            //This is the vertex that you will find inside the screen not ouside
            result_vertices.push_back(v);
        } else if (currentInside && !previousInside) {
            Vertex v = interpolate(currentVertex, previousVertex);
            result_vertices.push_back(v);
        }
        /*
        if (currentInside ^ previousInside) // se il nostro current è dentro e il previous non lo è o viceversa
        {
            // L = (1-B)/(1-B)-(1-C)
            double lerpAmt = (currentVertex.get_w() - currentComponent) /
                             ((currentVertex.get_w() - currentComponent) -
                              (previousVertex.get_w() - previousComponent));
            Vertex v = interpolate(previousVertex, currentVertex);
            //This is the vertex that you will find inside the screen not ouside
            result_vertices.push_back(v);
        }
        */

        if (currentInside) {
            result_vertices.push_back(currentVertex);
        }

        previousVertex = currentVertex;
        previousComponent = currentComponent;
        previousInside = currentInside;
    }
    buildTriangles(result_vertices, finalListOfTriangles);
};




bool clipTest(Vertex a) {
    double x = a.get_x();
    double y = a.get_y();
    double z = a.get_z();
    return x <= 1 && x >= -1 && y <= 1 && y >= -1 && z <= 1 && z >= -1;
}

bool allGreater(Vertex a, double n) {
    double x = a.get_x();
    double y = a.get_y();
    double z = a.get_z();
    return (x > n && y > n && z > n);
}

std::list<Triangle> clipTriangle(Triangle &triangle) {
    std::list<Triangle> triangles;
    Vertex a, b, c;
    a = triangle.get_a();
    b = triangle.get_b();
    c = triangle.get_c();

}

std::list<Triangle> clipTriangles(std::list<Triangle> &triangles) {
    /* 3D Homogenous Clipping
       In 1D with vertices {A, B, C}
       A >= -1 && A <= 1
       B >= -1 && B <= 1
       C >= -1 && C <= 1 ? No.

       So we take the segment between C and B and we find the point in this segment D
       so that D >= -1 && D <= 1.

       To find D we must interpolate between B and C.
       Linear interpolation is
       B(1 - L) + CL = 1 <==> B - LB + CL + (L - L) = 1 <==> ... <==>
       L = (1 - B) / (1 - B) - (1 - C)
    */
    std::list<Triangle> result;

    for (auto &triangle : triangles) {
        /*
            if (allOut(triangle.get_a(), 1) &&
                    allOut(triangle.get_b(), 1) &&
                    allOut(triangle.get_c(), 1)) {
                continue;
            }

            if (allOut())
            */
    }

    return result;
}