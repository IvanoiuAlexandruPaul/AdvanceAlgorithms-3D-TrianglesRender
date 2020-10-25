#include <vector>
#include <Triangle.h>

template <typename target_t>
class Pipeline {
    private: 

        //Ignora, non necessario nella prima parte 
        ModelTransform vt_;


        ProjectionTransform pt_;
        ScreenMapping sm_;
        Clipper cl_;
        RasterSubsystem<target_t> rs_;
    
    target_t render(Type primitives) { // Understand what type
        transformed = applyAll(std::vector({
            wt_,
            vt_,
            pt_
        }));
        
        ClippedType clipped = clipper.clip(transformed);
        return rs_.rasterize(clipped, sm_); 
    }
};

template<typename target_t>
class Window {
    public:
        void show(target_t target);
};

std::vector<Triangle> applyAll(std::vector<TrianglesTransform> transforms) {
    std::vector<Triangle> a;
    for (TrianglesTransform t : transforms) { // TODO verify
        a = t.apply(a);
    }
    return a;
};

class TrianglesTransform {
    public:
        std::vector<Triangle> apply(std::vector<Triangle> triangles);
};

class ModelTransform : TrianglesTransform {

    public: 
        std::vector<Triangle> Identity(std::vector<Triangle> triangles, Vertex vector) {
	        Matrix result;
	        result.m[0] = 1.0f;
	        result.m[5] = 1.0f;
	        result.m[10] = 1.0f;
	        result.m[15] = 1.0f;
	        return result;
        }

         std::vector<Triangle> Translation(std::vector<Triangle> triangles, Vertex vector){
                Matrix result = Matrix::Identity();
                result.m[12] = x;
                result.m[13] = y;
                result.m[14] = z;
                return result;
         }

         std::vector<Triangle> Rotation(std::vector<Triangle> triangles, double theta){
                Matrix result;
                result.m[0] = 1.0f;
                result.m[5] = cos(theta);
                result.m[9] = -sin(theta);
                result.m[6] = sin(theta);
                result.m[10] = cos(theta);
                result.m[15] = 1.0f;
                return result;              
         }
         
         std::vector<Triangle> Scale(std::vector<Triangle> trinagles, Vertex vector){
                Matrix result;
                result.m[0] = x;
                result.m[5] = y;
                result.m[10] = z;
                result.m[15] = 1.0f;
                return result;
         }

    private:

};

class ProjectionTransform : TrianglesTransform {

};

class Clipper{
    friend Matrix;
    Matrix Perspective1(float left, float right, float top, float bottom, float near, float far) {
        Matrix result;
        result[0] = 2.0f * near / (right - left);
        result[8] = (right + left) / (right - left);
        result[5] = 2.0f * near / (top - bottom);
        result[9] = (top + bottom) / (top - bottom);
        result[10] = -(far + near) / (far - near);
        result[14] = -2.0f * far * near / (far - near);
        result[11] = -1.0f;
        Matrix->mat_[1];
        //result.m[15] = 1.0f;
        return result;
    };

    Matrix Perspectiv1(float fov, float aspect, float near, float far) {
        float f = 1.0f / tan(fov / 2.0f);
        Matrix result;
        result.m[0] = f / aspect;
        result.m[5] = f;
        result.m[10] = (far + near) / (near - far);
        result.m[14] = 2 * far*near / (near - far);
        result.m[11] = -1.0f;
        return result;
    };
};

class ScreenMapping {

    void mapScreenPixelsToCartesian(int screenx, int screeny,int screenWidth, int screenHight,double &CoordinateX, double &CoordinateY){
        CoordinateX = screenx - screenWidth / 2;
        CoordinateY = -screeny + screenHight / 2;
    };
    
};

template <typename target_t>
class RasterSubsystem {
    int buffer_width, buffer_height;

    target_t createEmptyBuffer();

    target_t z_bufferize(std::vector<target_t> buffers, std::vector<Primitive> primitives); // TODO define primitives primitives in signatures.

    target_t rasterize(ClippedType clipped, ScreenMapping sm) {

        target_t buffer = createEmptyBuffer();
        std::vector<target_t> buffers;
        for(auto& primitive : clipped) {
            for(int x=0; x < buffer_width; x++) {
                for (int y=0; y < buffer_height; y++) {
                    double cartesian_x, cartesian_y;
                    sm.mapScreenPixlesToCartesian(x, y, buffer_width, buffer_height, cartesian_x, cartesian_y);
                    SomeType piece = clipped.get(cartesian_x, cartesian_y);
                    buffer[x, y] = magia(piece);
                }
            }
        }
        
        buffers.append(buffer);
        return  z_bufferize(buffers, clipped);
    };
};

