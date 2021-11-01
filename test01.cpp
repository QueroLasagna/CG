#include "vec.h"

int main(){
	vec2 u = {2, 1};
	vec2 v = {4, 3};
	vec2 w1 = u + v;
	vec2 w2 = 2*u - 3*v;

	vec3 m = {1, 2, 3};

	vec4 n = {1, 2, 3, 4};

	w1(0) = 1;
	w2(1)++;

	print("u", u);
	print("v", v);
	print("w1", w1);
	print("w2", w2);
	print("m", m);
	print("n", n);

	printf("dot(u,v) = %g\n", dot(u, v));
	printf("norm(u) = %g\n", norm(u));
	print("u normalizado", normalize(u));
}