#include "Clipping.h"
#include <Math.h>
double lerp(double a, double b) {
    return (1 - b) / (b - a);
}

double negativeLerp(double a, double b) {
    return (1 + b) / (b - a);
}

Vertex ReturnMeAMultiplyedVertex(Vertex x , double t){
    return Vertex(x.get_x()*t,x.get_y()*t,x.get_w()*t,x.get_w()*t);
}

double clippingLinearInterpolationValueT (Vertex a, Vertex b){
    double t = (b.get_z()+b.get_w()) / (b.get_z()+b.get_w()) - (a.get_z()+a.get_w());
    return t;
}

Vertex edgeVertex(Vertex c, Vertex a, double t) {
    return a + ((c - a) * t);
}

Vertex allPlanesIntersection(Vertex v, Vertex base, double a, double b) {
    double min_x = -1;
    double max_x = 1;
    double min_y = -1;
    double max_y = 1;
    double min_z = -1;
    double max_z = 1;

    if (v.get_x() < min_x) {
        v = Vertex(min_x, (min_x - base.get_x()) / a + base.get_y(), (min_x - base.get_x()) / (a * b) + base.get_z());
    } else if (v.get_x() > max_x) {
        v = Vertex(max_x, (max_x - base.get_x()) / a + base.get_y(), (max_x - base.get_x()) / (a * b) + base.get_z());
    }

    if (v.get_y() < min_y) {
        v = Vertex(a * (min_y - base.get_y()) + base.get_x(), min_y, (min_y - base.get_y()) / b + base.get_z());
    } else if (v.get_y() > max_y) {
        v = Vertex(a * (max_y - base.get_y()) + base.get_x(), max_y, (max_y - base.get_y()) / b + base.get_z());
    }

    if (v.get_z() < min_z) {
        v = Vertex(a * b * (min_z - base.get_z()) + base.get_x(), b * (min_z - base.get_z()) + base.get_y(), min_z);
    } else if (v.get_z() > max_z) {
        v = Vertex(a * b * (max_z - base.get_z()) + base.get_x(), b * (max_z - base.get_z()) + base.get_y(), max_z);
    }

    // In the paper there is a if to check is the line is completely outside of the space that does a print.


}

Vertex clipInterpolation(Vertex& v1, Vertex& v2) {

    Vertex v = v1;

    double a, b;

    if (v1.get_x() != v2.get_x() && v1.get_y() != v2.get_y() && v1.get_z() != v2.get_z()) { // Line is not parallel to any plane.
         a = (v2.get_x() - v1.get_x()) / (v2.get_y() - v1.get_y());
         b = (v2.get_y() - v1.get_y()) / (v2.get_z() - v1.get_z());

        v1 = allPlanesIntersection(v1, v1, a, b);
        v2 = allPlanesIntersection(v2, v1, a, b);
    }

    return v;
//    double ax = v1.get_x();
//    double ay = v1.get_y();
//    double az = v1.get_z();
//    double lx = ax, ly = ay, lz = az;
//    if (ax < -1) {
//        lx = -1;
//    } else if (ax > 1) {
//        lx = 1;
//    }
//    if (ay < -1) {
//        ly = -1;
//    } else if (ay > 1) {
//        ly = 1;
//    }
//    if (az < -1) {
//        lz = -1;
//    } else if (az > 1) {
//        lz = 1;
//    }

//    return Vertex(lx, ly, lz);
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

double euclidean_distance(Vertex a, Vertex b){
    double  x = (b.get_x())- (a.get_x());
    double  y = (b.get_y())- (a.get_y());
    double  z = (b.get_z())- (a.get_z());
    double sum = (pow(x,2)+pow(y,2)+pow(z,2));
    return sqrt(sum);
}

Vertex closer_vertex(Vertex a, std::list<Vertex> vertices){
    Vertex closer = vertices.front();
    double min_distance = euclidean_distance(a,closer);
    for (auto& v : vertices) {


//    for(int i=1; i< vertices.size();i++){
        double temp;
        temp = euclidean_distance(a, v);
        if(temp<min_distance){
            min_distance=temp;
            closer = v;
        }
    }
    return closer;
}

Vertex farthest_vertex(std::list<Vertex> vertices){
    Vertex farthest = vertices.front();
    double max_distance =0;
    double d=0;
    double somma = 0;
    //for(int i=0; i<vertices.size();i++){
        for (auto& i : vertices) {
    //for(int j =0; j<vertices.size();j++){
        for (auto& j : vertices) {
            d = euclidean_distance(i,j);
            somma = somma+d;
            //		std::cout<<"s:"<<i.str()<<"d:"<<j.str()<<":distance::"<<d<<std::endl;

        }

        //	std::cout<<"-----------somma----------------"<<somma<<std::endl;
        if(somma>max_distance){
            max_distance=somma;
            farthest = i;
            //		std::cout<<"new max point::"<<somma<<std::endl;
        }
        somma=0;
    }
    return farthest;
}

std::list<Vertex> erase_vertex(Vertex a, std::list<Vertex> vertices){
//    for(int i=0; i< vertices.size();i++){
    for (auto& i : vertices) {
        Vertex current = i;
        if(current.get_x()==a.get_x() && current.get_y()==a.get_y() && current.get_z()==a.get_z() && current.get_w()==a.get_w()){
            //elemnto trovato
            vertices.remove(i);
//            vertices.erase(vertices.begin()+i);
            return vertices;
        }
    }
    return vertices;
}

int number_of_triangles(int vertices){
    if(vertices<3){
        return 0;
    }else{
        return 1+number_of_triangles(vertices-1);
    }
}

std::list<Triangle> build_triangles(std::list<Vertex> vertices){
	std::list<Triangle> created_triangles;

    int max_triangles=0;
    //numero massio di triangoli che dobbiamo creare
    max_triangles=number_of_triangles(vertices.size());
//	std::cout<<"Dobiamo creare al massimo : "<<max_triangles<<std::endl;
//	std::cout<<"------start--------"<<std::endl;

    //prendiamo il vertice più lontano da tutti
    Vertex common = farthest_vertex(vertices) ;
    //eliminimamo il vetice selezionato dalla lista
//	std::cout<<"------selected_farthest--------"<<common.str()<<std::endl;
    vertices = erase_vertex(common, vertices);
    //std::cout<<"------extract farthest--------"<<std::endl;
 //   print_list(vertices);
    while(max_triangles>=1){
        //	std::cout<<"------Buid Step --------"<<max_triangles<<std::endl;
        Vertex second = closer_vertex(common,vertices);
        //	std::cout<<"------closser 1--------"<<second.str()<<std::endl;
        vertices = erase_vertex(second, vertices);
        Vertex third = closer_vertex(second,vertices);
        //	std::cout<<"------closser 2--------"<<third.str()<<std::endl;
        created_triangles.push_back({common,second,third});
        //	std::cout<<"------After buiding traingle --------"<<std::endl;
        max_triangles--;
    }

    return created_triangles;
}







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

    vertices.sort([](Vertex& a, Vertex& b) {
        return a.get_x() < b.get_x() && a.get_y() < b.get_y() && a.get_z() < b.get_z();
    });

    Vertex a = vertices.front();
    std::list<Triangle> result;
    vertices.pop_front();
    Vertex b = vertices.front();
    vertices.pop_front();
    do {
        Vertex c = vertices.front();
        result.push_back(Triangle(a, b, c));
        b = c;
        vertices.pop_front();
    } while (!vertices.empty());
    return result;
}


std::list<Triangle> clipTriangleAlex(Triangle &triangle) {

    std::list<Triangle> clippedTriangles;
    clippedTriangles.clear();

    Vertex a, b, c;

    a = triangle.get_a();
    b = triangle.get_b();
    c = triangle.get_c();

    if(!toClipTest(a) && !toClipTest(b) && toClipTest(c)){ // a e b dentro
        c =  ReturnMeAMultiplyedVertex(a,clippingLinearInterpolationValueT(a,b))+ReturnMeAMultiplyedVertex(b,(1-clippingLinearInterpolationValueT(a,b)));
        clippedTriangles.push_back(Triangle (a,b,c));
    }
    if(!toClipTest(b) && !toClipTest(c) && toClipTest(a)){ // b e c dentro
        a =  ReturnMeAMultiplyedVertex(b,clippingLinearInterpolationValueT(b,c))+ReturnMeAMultiplyedVertex(c,(1-clippingLinearInterpolationValueT(b,c)));
        clippedTriangles.push_back(Triangle (a,b,c));
    }
    if(!toClipTest(a) && !toClipTest(c) && toClipTest(b)){ // a e c dentro
        b =  ReturnMeAMultiplyedVertex(a,clippingLinearInterpolationValueT(a,c))+ReturnMeAMultiplyedVertex(c,(1-clippingLinearInterpolationValueT(a,c)));
        clippedTriangles.push_back(Triangle (a,b,c));
    }

    if( !toClipTest(a) && toClipTest(b) && toClipTest(c)){
        b =  ReturnMeAMultiplyedVertex(a,clippingLinearInterpolationValueT(a,b))+ReturnMeAMultiplyedVertex(b,(1-clippingLinearInterpolationValueT(a,b)));
        c =  ReturnMeAMultiplyedVertex(a,clippingLinearInterpolationValueT(a,c))+ReturnMeAMultiplyedVertex(c,(1-clippingLinearInterpolationValueT(a,c)));
        clippedTriangles.push_back(Triangle (a,b,c));
    }
    if( toClipTest(a) && !toClipTest(b) && toClipTest(c)){
        a =  ReturnMeAMultiplyedVertex(a,clippingLinearInterpolationValueT(a,b))+ReturnMeAMultiplyedVertex(b,(1-clippingLinearInterpolationValueT(a,b)));
        c =  ReturnMeAMultiplyedVertex(c,clippingLinearInterpolationValueT(a,c))+ReturnMeAMultiplyedVertex(c,(1-clippingLinearInterpolationValueT(a,c)));
        clippedTriangles.push_back(Triangle (a,b,c));
    }
    if( toClipTest(a) && toClipTest(b) && !toClipTest(c)){
        a =  ReturnMeAMultiplyedVertex(a,clippingLinearInterpolationValueT(a,c))+ReturnMeAMultiplyedVertex(c,(1-clippingLinearInterpolationValueT(a,c)));
        b =  ReturnMeAMultiplyedVertex(b,clippingLinearInterpolationValueT(b,c))+ReturnMeAMultiplyedVertex(c,(1-clippingLinearInterpolationValueT(b,c)));
        clippedTriangles.push_back(Triangle (a,b,c));
    }

    return clippedTriangles;

}

std::list<Triangle> clipTriangle(Triangle &triangle) {
    std::list<Vertex> clippedVertices;

    Vertex a, b, c;
    a = triangle.get_a();
    b = triangle.get_b();
    c = triangle.get_c();
    std::list<Vertex> triangleVertices({a, b, c});

    if (toClipTest(a)) {
        clippedVertices.push_back(clipInterpolation(a, c));
        clippedVertices.push_back(clipInterpolation(a, b));
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
        clippedVertices.push_back(clipInterpolation(c, b));
        clippedVertices.push_back(clipInterpolation(c, a));
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
        for (auto &triClipped : clipped) {
            result.push_front(triClipped);
        }
    }

    return result;
}

std::list<Triangle> Clipping::clip(std::vector<Triangle> &triangles) {
    return clipTriangles(triangles);
}