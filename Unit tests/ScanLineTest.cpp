#include "..\acutest.h"
#include "..\rasterization.h"
#include "..\Primitives.h"
#include <iostream>

void test_scanline(){
	vec2 P[] = {
		{100, 300}, {200, 300},  {100, 200},
		{300, 200}, {400, 200},	{400, 300},
		{200, 400},{300, 300},{300, 450},
		{199.5,6.30645},{145,43},{199.5,31.5263},
		{150, 250}, {250, 200}, {350, 50}
	};

    std::vector<Triangle<vec2>> Triangles = {
        {P[0], P[1], P[2]},
        {P[3], P[4], P[5]},
        {P[6], P[7], P[8]},
        {P[9], P[10], P[11]},
        {P[12], P[13], P[14]},
        {P[1], P[1], P[1]},
        {P[3], P[3], P[4]},
        {P[6], P[8], P[8]},
    };

    for(auto T: Triangles){
        std::vector<Pixel> A = simple_rasterize_triangle(T);
        std::vector<Pixel> B = scanline(T);

        TEST_ASSERT( A.size() == B.size() );

        for(unsigned int i = 0; i < A.size(); i++)
            TEST_CHECK( (A[i].x == B[i].x) && (A[i].y == B[i].y) );
    }
}


TEST_LIST = {
    {"scanline", test_scanline},
    {NULL, NULL}
};
