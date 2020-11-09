#include <vector>
#include <list>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "Triangle.h"
#include "Clipping.h"
#include "Matrix.h"
#include "Projection.h"
#include "ScreenMapping.h"
#include "Fragment.h"


#ifndef PIPELINE_H
#define PIPELINE_H

// Projection pipeline step

template <typename target_t>
class FragmentShader
{
    public:
        virtual target_t shade(Fragment& fragment);
};


template <typename target_t>
class Pipeline
{
protected:
    //Ignora, non necessario nella prima parte
    // ModelTransform wt_; // TODO Capire come usarla nella pipeline.
    Projection& pt_;
    ScreenMapping& sm_;
    Clipping& cl_;
    FragmentShader<target_t>& fs_;

public:
    Pipeline(Projection& pt, ScreenMapping& sm, Clipping& cl, FragmentShader<target_t>& fs);

    virtual void render(std::vector<Triangle>& primitives);

    virtual void show(target_t * frame, ScreenMapping& mapping) = 0;

    virtual target_t *createEmptyFragmentBuffer(ScreenMapping& screenMapping) = 0;
};

std::vector<Triangle> normalizeTriangles(std::vector<Triangle>& triangles);

std::vector<Vertex> normalizeVertices(std::vector<Vertex>& vertices);

double edge(double p_x, double p_y, double a_x, double a_y, double b_x, double b_y);

bool edgeTest(double p_x, double p_y, Vertex& a, Vertex& b, Vertex& c);

// TODO valutare se farlo diventare un metodo di ScreenMapping.
// Insertion in a list is more efficient rather than vector.
std::list<Fragment> rasterizeTriangle(Triangle& t, ScreenMapping& sm);

std::list<Fragment> zbuffering(std::list<Fragment>& fragments);

void printBuffer(char *buffer, int buffer_width, int buffer_height);

// TODO Discutere se tenere come classe anche se senza stato.
class CharFragmentShader : public FragmentShader<char>
{
    public:
        char shade(Fragment& fragment) override;
};

class CharPipeline : public Pipeline<char>
{
    using Pipeline<char>::Pipeline;
    // using Pipeline<char>::show;
    // using Pipeline<char>::createEmptyFragmentBuffer;
    // using Pipeline<char>::render;
    
    public:
        virtual void show(char *frame, ScreenMapping& mapping);
        virtual char *createEmptyFragmentBuffer(ScreenMapping& mapping); // TODO Valutare se muovere questo in ScreenMapping...
        // virtual void render(std::vector<Triangle>& triangles);
};




// Full constructor with the field of view coordinates

template <typename target_t>
Pipeline<target_t>::Pipeline(Projection& pt, ScreenMapping& sm, Clipping& cl, FragmentShader<target_t>& fs) :
pt_(pt), sm_(sm), cl_(cl), fs_(fs)
{
    // mt_ = mt;
    // pt_ = pt;
    // sm_ = sm;
    // cl_ = cl;
    // fs_ = fs;
}

void printTriangles(std::vector<Triangle>& primitives) {
    for (Triangle &triangle : primitives) {
        std::cout << triangle.get_a().get_x() << std::endl;   
    }
}

template <typename target_t>
void Pipeline<target_t>::render(std::vector<Triangle>& primitives)
{
    
    primitives = pt_.project(primitives);
    std::cout << "After Projection" << std::endl;
    for (auto& triangle: primitives) {
        std::cout << triangle.str() << std::endl;
    }
    std::list<Triangle> clippedPrimitives = cl_.clip(primitives);
    std::cout << "After Clipping" << std::endl;
    for (auto& triangle: clippedPrimitives) {
        std::cout << triangle.str() << std::endl;
    }
    std::list<Fragment> fragments;
    for (Triangle &triangle : clippedPrimitives)
    {
        std::list<Fragment> rasterized = rasterizeTriangle(triangle, sm_);
        for (Fragment &fragment : rasterized)
        {
            // TODO improve.
            fragments.push_back(fragment);
        }
    }

    fragments = zbuffering(fragments);
    target_t *frame = createEmptyFragmentBuffer(sm_);

    for (int x = 0; x < sm_.get_screenHeight(); ++x)
    {
        for (int y = 0; y < sm_.get_screenWidth(); ++y)
        {
            for (Fragment &fragment : fragments)
            {
                if (fragment.get_x() == x && fragment.get_y() == y)
                {
                    frame[x * sm_.get_screenHeight() + y] = fs_.shade(fragment);
                }
            }
        }
    }

    show(frame, sm_);
}

std::vector<Triangle> normalizeTriangles(std::vector<Triangle>& triangles)
{
    std::vector<Triangle> new_triangles;
    for (Triangle t : triangles)
    {
        std::vector<Vertex> vL;
        for (Vertex v : t.get_vertex())
        {
            vL.push_back(Vertex(v.get_x() / v.get_w(), v.get_y() / v.get_w(), v.get_z() / v.get_w(), 1.0));
        }
        new_triangles.push_back(Triangle(vL[0], vL[1], vL[2]));
    }
    return new_triangles;
}

std::vector<Vertex> normalizeVertices(std::vector<Vertex>& vertices)
{
    std::vector<Vertex> new_vertices;
    for (Vertex v : vertices)
    {
        new_vertices.push_back(Vertex(v.get_x() / v.get_w(), v.get_y() / v.get_w(), v.get_z() / v.get_w(), 1.0));
    }
    return new_vertices;
}

double edge(double p_x, double p_y, double a_x, double a_y, double b_x, double b_y)
{
    return (p_x - a_x) * (b_y - a_y) -
           (p_y - a_y) * (b_x - a_x);
}

bool edgeTest(double p_x, double p_y, Vertex& a, Vertex& b, Vertex& c)
{

    double t_ab = edge(p_x, p_y, a.get_x(), a.get_y(), b.get_x(), b.get_y());
    double t_bc = edge(p_x, p_y, b.get_x(), b.get_y(), c.get_x(), c.get_y());
    double t_ca = edge(p_x, p_y, c.get_x(), c.get_y(), a.get_x(), a.get_y());

    return (t_ab >= 0) && (t_bc >= 0) && (t_ca >= 0);
}

std::list<Fragment> rasterizeTriangle(Triangle& t, ScreenMapping& sm)
{

    std::list<Fragment> fragments;

    double max_x, max_y, min_x, min_y;
    Vertex a = t.get_a();
    Vertex b = t.get_b();
    Vertex c = t.get_c();

    // Find the conscribed square around the triangle in cartesian coordinates.
    max_x = std::max(std::max(a.get_x(), b.get_x()), c.get_x());
    min_x = std::min(std::min(a.get_x(), b.get_x()), c.get_x());
    max_y = std::max(std::max(a.get_y(), b.get_y()), c.get_y());
    min_y = std::min(std::min(a.get_y(), b.get_y()), c.get_y());

    // Convert coordinates to pixel coordinates.
    sm.mapCartesianToScreenPixels(max_x, max_y, &max_x, &max_y);
    sm.mapCartesianToScreenPixels(min_x, min_y, &min_x, &min_y);

    // P: x_p * x + z_p * z + y_p * y + w_p * w = 0
    Vertex plane = planePassingPoints(a, b, c);

    for (int row = min_x; row < max_x; ++row)
    {
        for (int col = min_y; col < max_y; ++col)
        {
            double p_x, p_y;
            sm.mapScreenPixelsToCartesian(row, col, &p_x, &p_y);

            // Edge test to find out if the pixel is in the triangle.
            if (edgeTest(p_x, p_y, a, b, c))
            {
                // Create fragment:

                // Calculate z = (- x_p * x - y_p * y - w_p) / z_p.
                double p_z = (-plane.get_x() * p_x - plane.get_y() * p_y - plane.get_w()) / plane.get_z();

                // Instantiate Fragment and prepare to return.
                Fragment f(row, col, p_z);

                fragments.push_back(f);
            }
        }
    }

    return fragments;
}

bool fragmentComparator(const Fragment& a, const Fragment& b)
{
   return a.get_x() <= b.get_x() && a.get_y() <= b.get_y();
}

std::list<Fragment> zbuffering(std::list<Fragment>& fragments)
{

    fragments.sort([](const Fragment& a, const Fragment& b) {
        return a.get_x() <= b.get_x() && a.get_y() <= b.get_y();
    });

    Fragment tmp = fragments.front();

    std::list<Fragment> result;
    for (Fragment &fragment : fragments)
    {
        if (tmp.get_x() != fragment.get_x() || tmp.get_y() != fragment.get_y())
        {
            result.push_back(tmp);
            tmp = fragment;
        }
        else
        {
            if (tmp.get_z() > fragment.get_z())
            {
                tmp = fragment;
            }
        }
    }

    return result;
}

void printBuffer(char *buffer, int buffer_width, int buffer_height)
{
    for (int row = 0; row < buffer_height; ++row)
    {
        for (int col = 0; col < buffer_width; ++col)
        {
            std::cout << buffer[row * buffer_width + col];
        }
        std::cout << std::endl;
    }
}

char CharFragmentShader::shade(Fragment& fragment)
{
    return '#'; // TODO per farlo come quello del prof bisogna trovare il primo decimale di fragment.get_z().
}

void CharPipeline::show(char *frame, ScreenMapping& mapping)
{
    printBuffer(frame, mapping.get_screenWidth(), mapping.get_screenHeight());
}

char *CharPipeline::createEmptyFragmentBuffer(ScreenMapping& mapping)
{
    int buffer_width = mapping.get_screenWidth();
    int buffer_height = mapping.get_screenHeight();

    char *buffer = new char[buffer_width * buffer_height];
    for (int row = 0; row < buffer_height; ++row)
    {
        for (int col = 0; col < buffer_width; ++col)
            buffer[row * buffer_width + col] = '.';
    }
    return buffer;
}

// CharPipeline::CharPipeline(Projection p, ScreenMapping sm, Clipping c, FragmentShader<char> shader) {
//     this->pt_ = p;
//     this->sm_ = sm;
//     this->cl_ = c;
//     this->fs_ = shader;
// }



#endif