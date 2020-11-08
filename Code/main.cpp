#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Pipeline.h"

bool loadObjFile(std::string filename, std::vector<Triangle> output){
    std::ifstream file(filename);
    if(!file.is_open())
        return false;
     std::stringstream ss;
     std::string line;
     std::string vertex;
    while(!file.eof()){
        getline(std::cin, line);
        //if(line[0] == "v")
        /* while(std::getline(ss, vertex, 'v')){
            double x,y,z,w;
            char c;
            
        }  */
    }
    return true;
};

int main()
{

    Projection p(-1.0f,1.0f,1.0f,-1.0f,0.1f,100.0f);
    ScreenMapping sm(80, 80);
    CharFragmentShader shader;
    Clipping c;

    CharPipeline pipeline(p, sm, c, shader);
    
    Vertex v1( 1, -1, 1.5);
    Vertex v2( 1,  1, 1.1);
    Vertex v3(-1, 1, 1.5);
    Vertex v4(-1,-1, 1.9);
    // creare triangoli
    Triangle t1(v1, v2, v3);
    Triangle t2(v1, v3, v4);
    std::vector<Triangle> triangles = {t1, t2};
    pipeline.render(triangles);

    std::cout << "Hello" << std::endl;

    return 0;
}