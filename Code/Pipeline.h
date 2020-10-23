template <target_t>
class Pipeline {
    private: 
        WorldTransform wt_;
        ViewTransform vt_;
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
}

template<target_t>
class Window {
    public:
        void show(target_t target);
}

Type applyAll(std::vector<Transform> transforms) {
    Type a;
    for (Transform t : transforms) { // TODO verify
        a = t.apply(a);
    }
    return a;
}

class Transform {
    Type apply(Type);
}

class WorldTransform : Transform {

}

class ViewTransform : Transform {

}

class ProjectionTransform : Transform {

}

class Clipper(GLdouble xLeft, GLdouble xRight, GLdouble yBottom, GLdouble yTop, GLdouble zNear, GLdouble zFar) {
    
    Matrix Perspective1(float left, float right, float top, float bottom, float near, float far) {
        Matrix4 result;
        result.m[0] = 2.0f * near / (right - left);
        result.m[8] = (right + left) / (right - left);
        result.m[5] = 2.0f * near / (top - bottom);
        result.m[9] = (top + bottom) / (top - bottom);
        result.m[10] = -(far + near) / (far - near);
        result.m[14] = -2.0f * far * near / (far - near);
        result.m[11] = -1.0f;
        //result.m[15] = 1.0f;
        return result;
    }

    Matrix Perspectiv1(float fov, float aspect, float near, float far) {
        float f = 1.0f / tan(fov / 2.0f);
        Matrix4 result;
        result.m[0] = f / aspect;
        result.m[5] = f;
        result.m[10] = (far + near) / (near - far);
        result.m[14] = 2 * far*near / (near - far);
        result.m[11] = -1.0f;
        return result;
    }
}

class ScreenMapping() {

    void mapScreenPixelsToCartesian(int screenx, int screeny,int screenWidth, int screenHight,double &CoordinateX, double &CoordinateY){
        CoordinateX = screenx - screenwidth / 2;
        CoordinateY = -screeny + screenheight / 2;
    }
    
}

template <target_t>
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
    }
}