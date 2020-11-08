#include <vector>
#include <math.h>
#include <list>
#include <algorithm>
#include "Triangle.h"
#include "Clipping.cpp"


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
    Pipeline( Projection pt, ScreenMapping sm, Clipping cl, FragmentShader<target_t> fs)
    {
        // mt_ = mt;
        pt_ = pt;
        sm_ = sm;
        cl_ = cl;
        fs_ = fs;
    }

    void render(std::vector<Triangle> primitives)
    {
        primitives = pt_.project(primitives);
        primitives = cl_.clip(primitives);

        std::list<Fragment> fragments;
        for (Triangle &triangle : primitives)
        {
            fragments.push_back(rasterizeTriangle(triangle));
        }

        fragments = zbuffering(fragments);
        target_t *frame = createEmptyFragmentBuffer(sm_);

        for (int x = 0; x < sm_.get_screenHeight(), ++x)
        {
            for (int y = 0; y < sm_.get_screenWidth(), ++y)
            {
                for (Fragment &fragment : fragments)
                {
                    if (fragment.get_x() == x && fragment.get_y() == y)
                    {
                        frame[x][y] = fs_.shade(fragment);
                    }
                }
            }
        }

        show(frame, sm_);
    }

    void show(target_t *frame, ScreenMapping mapping);

    target_t *createEmptyFragmentBuffer(ScreenMapping screenMapping);
};



class TrianglesTransform
{
public:
    std::vector<Triangle> apply(std::vector<Triangle> triangles);
};



class Normalize
{

public:
    std::vector<Triangle> normalizeTriangles(std::vector<Triangle> triangles)
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

    std::vector<Vertex> normalizeVertices(std::vector<Vertex> vertices)
    {
        std::vector<Vertex> new_vertices;
        for (Vertex v : vertices)
        {
            new_vertices.push_back(Vertex(v.get_x() / v.get_w(), v.get_y() / v.get_w(), v.get_z() / v.get_w(), 1.0));
        }
        return new_vertices;
    }
};

class ScreenMapping
{
public:
    ScreenMapping(int screenWidth, int screenHeight)
    {
        this->screenHeight = screenHeight;
        this->screenWidth = screenWidth;
    }

    void mapScreenPixelsToCartesian(int screenx, int screeny, double *coordinateX, double *coordinateY)
    {
        *coordinateX = screenx - screenWidth / 2;
        *coordinateY = -screeny + screenHeight / 2;
    }

    void mapCartesianToScreenPixels(double x, double y, double *pixelRow, double *pixelCol)
    {
        *pixelRow = floor((screenWidth / 2) + x);
        *pixelCol = floor((screenHeight / 2) - y);
    }

    int get_screenWidth()
    {
        return screenWidth;
    }

    int get_screenHeight()
    {
        return screenHeight;
    }

private:
    int screenWidth;
    int screenHeight;
};

class Fragment
{
public:
    Fragment(int pixel_x, int pixel_y, double z)
    {
        this->pixel_x = pixel_x;
        this->pixel_y = pixel_y;
        this->z = z;
    }

    int get_x()
    {
        return pixel_x;
    }

    int get_y()
    {
        return pixel_y;
    }

    double get_z()
    {
        return z;
    }

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



double edge(double p_x, double p_y, double a_x, double a_y, double b_x, double b_y)
{
    return (p_x - a_x) * (b_y - a_y) -
           (p_y - a_y) * (b_x - a_x);
}

bool edgeTest(double p_x, double p_y, Vertex a, Vertex b, Vertex c)
{

    double t_ab = edge(p_x, p_y, a.get_x(), a.get_y(), b.get_x(), b.get_y());
    double t_bc = edge(p_x, p_y, b.get_x(), b.get_y(), c.get_x(), c.get_y());
    double t_ca = edge(p_x, p_y, c.get_x(), c.get_y(), a.get_x(), a.get_y());
}

// Insertion in a list is more efficient rather than vector.
std::list<Fragment> rasterizeTriangle(Triangle t, ScreenMapping sm)
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

int fragmentComparator(Fragment a, Fragment b)
{
    if (a.get_x() <= b.get_x())
    {
        if (a.get_y() >= b.get_y())
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

std::list<Fragment> zbuffering(std::list<Fragment> fragments)
{

    std::sort(fragments.begin(), fragments.end(), fragmentComparator);

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

class CharFragmentShader : FragmentShader<char>
{
    char shade(Fragment fragment)
    {
        return '#'; // TODO per farlo come quello del prof bisogna trovare il primo decimale di fragment.get_z().
    }
};

class CharPipeline : Pipeline<char>
{
    void show(char *frame, ScreenMapping mapping)
    {
        printBuffer(frame, mapping.get_screenWidth(), mapping.get_screenHeight());
    }

    char *createEmptyFragmentBuffer(ScreenMapping mapping)
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
};