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
	    
        }

        std::vector<Triangle> Translation(std::vector<Triangle> triangles, Vertex vector){
            std::vector<Triangle> new_triangles; 
            for(Triangle t:triangles){
                std::vector<Vertex> nv; 
                
                for(Vertex v: t.get_vertex()){
                    Matrix mt = Matrix(4, 4, 
                        {{1,0,0, vector.get_x()},
                         {0,1,0, vector.get_y()},
                         {0,0,1, vector.get_z()},
                         {0,0,0, vector.get_w()}
                         });
                    Matrix vc = Matrix(4,1,{{v.get_x()},{v.get_y()},{v.get_z()},{v.get_w()}});
                    Matrix nc = mt.product(mt,vc); 
                    nv.push_back({nc(0,0),nc(1,0),nc(2,0)}); 
                }
                new_triangles.push_back({nv.at(0),nv.at(1),nv.at(2)}); 
            }
            return new_triangles;
        }


        std::vector<Triangle> Rotation(std::vector<Triangle> triangles, double theta){
         
        std::vector<Triangle> Scale(std::vector<Triangle> trinagles, Vertex vector){
            
        }

class ProjectionTransform : TrianglesTransform {

};

class Clipper {
    //Perspective1(-1,1,1,-1,0.1f,100.0f);
    Matrix Perspective1(float left, float right, float top, float bottom, float near, float far) {
        std::vector<std::vector<double>> result(
            4,
            std::vector<double>(4, 0)
        );
        result[0][0] = 2.0f * near / (right - left);
        result[0][3] = (right + left) / (right - left);
        result[1][1] = 2.0f * near / (top - bottom);
        result[1][2] = (top + bottom) / (top - bottom);
        result[1][3] = -(far + near) / (far - near);
        result[2][3] = -2.0f * far * near / (far - near);
        result[2][3] = -1.0f;
        //result[15] = 1.0f;
        return Matrix(4, 4, result);
    };

    Matrix Perspectiv1(float fov, float aspect, float near, float far) {
        float f = 1.0f / tan(fov / 2.0f);
        std::vector<std::vector<double>> result (
            4,
            std::vector<double>(4, 0)
        );
        result[0][0] = f / aspect;
        result[1][1] = f;
        result[2][2] = (far + near) / (near - far);
        result[3][3] = 2 * far*near / (near - far);
        result[3][2] = -1.0f;
        return Matrix(4, 4, result);
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
    protected:
        int buffer_width, buffer_height;

    virtual target_t createEmptyBuffer();

    virtual target_t z_bufferize(std::vector<target_t> buffers, std::vector<Triangle> primitives);

    virtual target_t rasterize(ClippedType clipped, ScreenMapping sm) {
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

class CharRasterSubsystem : RasterSubsystem<char*> {
    char* createEmptyBuffer() {
        char* buffer =  new char[buffer_width * buffer_height];
        for (int row = 0; row < buffer_height; row++) {
            for (int col = 0; col < buffer_width; col++)
                buffer[row * buffer_width + col] = '.'; 
        }
        return buffer;
    }

    char* z_bufferize(std::vector<char*> buffers, std::vector<Triangle> primitives) {

    }
};

void printBuffer(char * buffer, int buffer_width, int buffer_height) {
    for (int row = 0; row < buffer_height; row++) {
        for (int col = 0; col < buffer_width; col++) {
            std::cout << buffer[row * buffer_width + col];
        }
        std::cout << std::endl;
    }
}