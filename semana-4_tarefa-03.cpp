#include "Primitives.h"
#include "rasterization.h"
#include "Image.h"

int main(){
    Image Img(500, 400);
    Img.fill(white);

    std::vector<vec2> P = {
        {193, 66},
        {259, 139},
        {340, 54},
        {176, 220},
        {336, 212},
        {261, 311}};

    TriangleStrip T{P.size()};

    for (Triangle<vec2> triangle : assemble(T, P))
        for (Pixel p : rasterizeTriangle(triangle))
            Img(p.x, p.y) = blue;

    Img.savePNG("output_triangle1.png");
    Img.fill(white);

    TriangleFan T2{P.size()};

    for(Triangle<vec2> triangle: assemble(T2, P))
       for(Pixel p: rasterizeTriangle(triangle))
           Img(p.x,p.y) = blue;

    Img.savePNG("output_triangle2.png");
}
