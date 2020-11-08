#include <vector>
#include <math.h>
#include <list>
#include <algorithm>
#include "Triangle.h"
#include "Clipping.cpp"
#include "Matrix.h"

#ifndef PIPELINE_H
#define PIPELINE_H

// Projection pipeline step
class Projection
{

private:
    Matrix mt;

public:
    std::vector<Triangle> project(std::vector<Triangle> triangles);

    //perspective(-1.0f,1.0f,1.0f,-1.0f,0.1f,100.0f);
    Projection(float left, float right, float top, float bottom, float near, float far);

    //perspectiv3(π/2, (16.0f/9.0f), 0.1f, 100.0f);
    Projection(float fov, float aspect, float near, float far);
};

// TODO Valutare se cambiare nome. Magari ScreenContext o ScreenManager?
class ScreenMapping
{
public:
    ScreenMapping(int screenWidth, int screenHeight);

    void mapScreenPixelsToCartesian(int screenx, int screeny, double *coordinateX, double *coordinateY);

    void mapCartesianToScreenPixels(double x, double y, double *pixelRow, double *pixelCol);

    int get_screenWidth();

    int get_screenHeight();

private:
    int screenWidth;
    int screenHeight;
};

class Fragment
{
public:
    Fragment(int pixel_x, int pixel_y, double z);

    int get_x() const;

    int get_y() const;

    double get_z() const;

private:
    int pixel_x;
    int pixel_y;
    double z;
};

template <typename target_t>
class FragmentShader
{
    virtual target_t shade(Fragment fragment);
};

template <typename target_t>
class Pipeline
{
private:
    //Ignora, non necessario nella prima parte
    // ModelTransform wt_; // TODO Capire come usarla nella pipeline.
    Projection pt_;
    ScreenMapping sm_;
    Clipping cl_;
    FragmentShader<target_t> fs_;

public:
    Pipeline(Projection pt, ScreenMapping sm, Clipping cl, FragmentShader<target_t> fs);

    void render(std::vector<Triangle> primitives);

    void show(target_t *frame, ScreenMapping mapping);

    target_t *createEmptyFragmentBuffer(ScreenMapping screenMapping);
};

std::vector<Triangle> normalizeTriangles(std::vector<Triangle> triangles);

std::vector<Vertex> normalizeVertices(std::vector<Vertex> vertices);

double edge(double p_x, double p_y, double a_x, double a_y, double b_x, double b_y);

bool edgeTest(double p_x, double p_y, Vertex a, Vertex b, Vertex c);

// TODO valutare se farlo diventare un metodo di ScreenMapping.
// Insertion in a list is more efficient rather than vector.
std::list<Fragment> rasterizeTriangle(Triangle t, ScreenMapping sm);


std::list<Fragment> zbuffering(std::list<Fragment> fragments);

void printBuffer(char *buffer, int buffer_width, int buffer_height);

// TODO Discutere se tenere come classe anche se senza stato.
class CharFragmentShader : FragmentShader<char> 
{
    char shade(Fragment fragment);
};

class CharPipeline : Pipeline<char>
{
    void show(char *frame, ScreenMapping mapping);

    char *createEmptyFragmentBuffer(ScreenMapping mapping); // TODO Valutare se muovere questo in ScreenMapping...
};

#endif