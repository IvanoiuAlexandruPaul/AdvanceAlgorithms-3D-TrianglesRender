#include "Clipping.h"

double clippedLinearInterpolation(double a, double b) {
    return (1 - a) / (1 - a - (1 - b));
}

Vertex clipInterpolation(Vertex a, Vertex b) {
    double lx = clippedLinearInterpolation(a.get_x(), b.get_x());
    double ly = clippedLinearInterpolation(a.get_y(), b.get_y());
    double lz = clippedLinearInterpolation(a.get_z(), b.get_z());

    return Vertex(lx, ly, lz);
}




/*std::vector<Triangle> Clipping::clip(std::vector<Triangle> &triangles) {
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
};*/

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
            Vertex v = clipInterpolation(previousVertex, currentVertex);
            //This is the vertex that you will find inside the screen not ouside
            result_vertices.push_back(v);
        } else if (currentInside && !previousInside) {
            Vertex v = clipInterpolation(currentVertex, previousVertex);
            result_vertices.push_back(v);
        }
        /*
        if (currentInside ^ previousInside) // se il nostro current è dentro e il previous non lo è o viceversa
        {
            // L = (1-B)/(1-B)-(1-C)
            double lerpAmt = (currentVertex.get_w() - currentComponent) /
                             ((currentVertex.get_w() - currentComponent) -
                              (previousVertex.get_w() - previousComponent));
            Vertex v = clipInterpolation(previousVertex, currentVertex);
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


bool toClipTest(Vertex a) {
    double x = a.get_x();
    double y = a.get_y();
    double z = a.get_z();
    return !(x <= 1 && x >= -1 && y <= 1 && y >= -1 && z <= 1 && z >= -1);
}


bool allGreater(Vertex a, double n) {
    return a.get_x() > n && a.get_y() > n && a.get_z() > n;
}

bool allGreater(Triangle a, double n) {
    return allGreater(a.get_a(), n) && allGreater(a.get_b(), n) && allGreater(a.get_c(), n);
}

bool allLess(Vertex a, double n) {
    return a.get_x() < n && a.get_y() < n && a.get_z() < n;
}

bool allLess(Triangle a, double n) {
    return allLess(a.get_a(), n) && allLess(a.get_b(), n) && allLess(a.get_c(), n);
}

// Returns true iff the triangle is completely outside of the x, y, z \in [-1; 1] space.
bool outOfBound(Triangle triangle) {

    bool isOut = (triangle.get_a().get_x() > 1 && triangle.get_b().get_x() > 1 && triangle.get_c().get_x() > 1);
    isOut = isOut || (triangle.get_a().get_y() > 1 && triangle.get_b().get_y() > 1 && triangle.get_c().get_y() > 1);
    isOut = isOut || (triangle.get_a().get_z() > 1 && triangle.get_b().get_z() > 1 && triangle.get_c().get_z() > 1);

    isOut = isOut || (triangle.get_a().get_x() < -1 && triangle.get_b().get_x() < -1 && triangle.get_c().get_x() < -1);
    isOut = isOut || (triangle.get_a().get_y() < -1 && triangle.get_b().get_y() < -1 && triangle.get_c().get_y() < -1);
    isOut = isOut || (triangle.get_a().get_z() < -1 && triangle.get_b().get_z() < -1 && triangle.get_c().get_z() < -1);

    return isOut;
}

std::list<Triangle> triangularize(std::list<Vertex> &vertices) {
    Vertex a = vertices.front();
    std::list<Triangle> result;
    vertices.pop_front();
    Vertex b = vertices.front();
    vertices.pop_front();
    do {
        Vertex c = vertices.front();
        result.push_front(Triangle(a, b, c));
        b = c;
        vertices.pop_front();
    } while (!vertices.empty());
    return result;
}

std::list<Triangle> clipTriangle(Triangle &triangle) {
    std::list<Vertex> clippedVertices;

    Vertex a, b, c;
    a = triangle.get_a();
    b = triangle.get_b();
    c = triangle.get_c();
    std::list<Vertex> triangleVertices({a, b, c});

    if (toClipTest(a)) {
        clippedVertices.push_back(clipInterpolation(a, b));
        clippedVertices.push_back(clipInterpolation(a, c));
    } else {
        clippedVertices.push_back(a);
    }

    if (toClipTest(b)) {
        clippedVertices.push_back(clipInterpolation(b, a));
        clippedVertices.push_back(clipInterpolation(b, c));
    } else {
        clippedVertices.push_back(b);
    }

    if (toClipTest(c)) {
        clippedVertices.push_back(clipInterpolation(c, a));
        clippedVertices.push_back(clipInterpolation(c, b));
    } else {
        clippedVertices.push_back(c);
    }

    return triangularize(clippedVertices);
}

/* 3D Homogenous Clipping
       In 1D with vertices {A, B, C}
       A >= -1 && A <= 1
       B >= -1 && B <= 1
       C >= -1 && C <= 1 ? No.

       So we take the segment between C and B and we find the point in this segment D
       so that D >= -1 && D <= 1.

       To find D we must clipInterpolation between B and C.
       Linear interpolation is
       B(1 - L) + CL = 1 <==> B - LB + CL + (L - L) = 1 <==> ... <==>
       L = (1 - B) / (1 - B) - (1 - C)
    */

std::list<Triangle> clipTriangles(std::vector<Triangle> &triangles) {
    std::list<Triangle> result;

    for (auto &triangle : triangles) {
        // Ignora il triangolo se è completamente fuori dai bound
        if (outOfBound(triangle)) continue;

        // Lancia il clipping sul triangolo.
        auto clipped = clipTriangle(triangle);

        // Unisci i risultati.
        for (auto& triClipped : clipped) {
            result.push_front(triClipped);
        }
    }

    return result;
}

std::list<Triangle> Clipping::clip(std::vector<Triangle> &triangles) {
    return clipTriangles(triangles);
}