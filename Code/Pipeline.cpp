#include "Pipeline.h"

// Full constructor with the field of view coordinates
Projection::Projection(float left, float right, float top, float bottom, float near, float far)
{
    std::vector<std::vector<double>> result(
        4,
        std::vector<double>(4, 0));
    result[0][0] = 2.0f * near / (right - left);
    result[0][3] = (right + left) / (right - left);
    result[1][1] = 2.0f * near / (top - bottom);
    result[1][2] = (top + bottom) / (top - bottom);
    result[1][3] = -(far + near) / (far - near);
    result[2][3] = -2.0f * far * near / (far - near);
    result[2][3] = -1.0f;
    //result[3][3] = 0.0f;
    mt = Matrix(4, 4, result);
}

// Constructor for trigonometric
Projection::Projection(float fov, float aspect, float near, float far)
{
    float focal = 1.0f / tan(fov / 2.0f); //cotan(fov/2)
    //in teoria dovrebbe essere ((height or width) / 2) * cotan(fov/2)
    std::vector<std::vector<double>> result(
        4,
        std::vector<double>(4, 0));
    result[0][0] = focal / aspect;
    result[1][1] = focal;
    result[2][2] = (far + near) / (near - far);
    result[3][3] = 2 * far * near / (near - far);
    result[3][2] = -1.0f;
    mt = Matrix(4, 4, result);
}

std::vector<Triangle> Projection::project(std::vector<Triangle> triangles)
{
    std::vector<Triangle> new_triangles;
    // Matrix mt = perspective(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    for (Triangle t : triangles)
    {
        std::vector<Vertex> nv;
        for (Vertex v : t.get_vertex())
        {
            Matrix vc = Matrix(4, 1, {{v.get_x()}, {v.get_y()}, {v.get_z()}, {v.get_w()}});
            Matrix nc = mt.product(mt, vc);
            nv.push_back({nc(0, 0), nc(1, 0), nc(2, 0)});
        }
        new_triangles.push_back({nv.at(0), nv.at(1), nv.at(2)});
    }
    return new_triangles;
}

template <typename target_t>
Pipeline<target_t>::Pipeline(Projection pt, ScreenMapping sm, Clipping cl, FragmentShader<target_t> fs)
{
    // mt_ = mt;
    pt_ = pt;
    sm_ = sm;
    cl_ = cl;
    fs_ = fs;
}

template <typename target_t>
void Pipeline<target_t>::render(std::vector<Triangle> primitives)
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

ScreenMapping::ScreenMapping(int screenWidth, int screenHeight)
{
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
}

void ScreenMapping::mapScreenPixelsToCartesian(int screenx, int screeny, double *coordinateX, double *coordinateY)
{
    *coordinateX = screenx - screenWidth / 2;
    *coordinateY = -screeny + screenHeight / 2;
}

void ScreenMapping::mapCartesianToScreenPixels(double x, double y, double *pixelRow, double *pixelCol)
{
    *pixelRow = floor((screenWidth / 2) + x);
    *pixelCol = floor((screenHeight / 2) - y);
}

int ScreenMapping::get_screenWidth()
{
    return screenWidth;
}

int ScreenMapping::get_screenHeight()
{
    return screenHeight;
}

