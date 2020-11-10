#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Pipeline.h"
#include <math.h>

bool loadObjFile(const std::string &filename, std::vector<Triangle> &output) {
    std::ifstream file(filename);
    if (!file.is_open())
        return false;
    std::string line;
    while (!file.eof()) {
        getline(std::cin, line);
        if (line.rfind('v', 0) == 0) {
            std::stringstream ss(line);
            std::string component;
            double x, y, z, w;
            int i;
            std::vector<Vertex> vecV;
            for (i = 0; getline(ss, component, ' '); ++i) {
                switch (i) {
                    case 0:
                        x = std::stod(component);
                        break;
                    case 1:
                        y = std::stod(component);
                        break;
                    case 2:
                        z = std::stod(component);
                        break;
                    case 3:
                        w = std::stod(component);
                        break;
                    default:
                        x = 1;
                        y = 1;
                        z = 1;
                        w = 1;
                        break;
                }
            }
            if (i == 3)
                w = 1;
            Vertex v(x, y, z, w);
            vecV.push_back(v);
        }
    }
    return true;
};

int main() {
//float left, float right, float top, float bottom, float near, float far
    Projection p(-1, 1, -1, 1, 1, 2);
    ScreenMapping sm(150, 50);
    CharFragmentShader shader;
    Clipping c;

    CharPipeline pipeline(p, sm, c, shader);

    Vertex v1(1, -1, 1.5);
    Vertex v2(1, 1, 1.1);
    Vertex v3(-1, 1, 1.5);
    Vertex v4(-1, -50, 1.9);


    // creare triangoli
    Triangle t1(v1, v2, v3);
    Triangle t2(v1, v3, v4);

    std::vector<Triangle> triangles = {t1, t2};
    pipeline.render(triangles);

    /*Vertex v1(-1, -1, 1.5);
    Vertex v2(-1, 1, 1.5);
    Vertex v3(1, 1, 1.5);

    Triangle t1(v1, v3, v2);

    std::list<Fragment> fragments = pipeline.rasterizeTriangle(t1);
    char* frame = pipeline.createEmptyFragmentBuffer();
    pipeline.populateBuffer(frame, fragments);
    pipeline.show(frame);*/

    return 0;
}