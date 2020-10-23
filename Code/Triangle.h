#include <xmatrix.h>

class Triangle {

    public:
    Triangle(Vertex normals, Vertex a, Vertex b, Vertex c, Vertex a_uv, Vertex b_uv, Vertex c_uv);

    private:
        Vertex normals;
        Vertex a;
        Vertex b;
        Vertex c;
        Vertex a_uv;
        Vertex b_uv;
        Vertex c_uv;
}