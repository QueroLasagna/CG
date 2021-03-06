#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix.h"
#include "vec.h"

inline mat4 loadIdentity(){
    return Id<4>();
}

inline mat4 translate(vec3 u){
	return {
		1, 0, 0, u(0),
		0, 1, 0, u(1),
		0, 0, 1, u(2),
		0, 0, 0,    1
	};
}

inline mat4 translate(float x, float y, float z){
    return translate(vec3{x, y, z});
}

inline mat4 scale(float x, float y, float z){
	return {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}

inline mat4 rotate_x(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		1, 0,  0, 0,
		0, c, -s, 0,
		0, s,  c, 0,
		0, 0,  0, 1
	};
}

inline mat4 rotate_y(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		 c, 0, s, 0,
		 0, 1, 0, 0,
		-s, 0, c, 0,
		 0, 0, 0, 1
	};
}

inline mat4 rotate_z(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		c, -s, 0, 0,
		s,  c, 0, 0,
		0,  0, 1, 0,
		0,  0, 0, 1
	};
}

inline mat4 rotate(vec3 n, float theta){
	/* TAREFA - aula 10 */
	vec3 vx={1,0,0};
    vec3 vy={0,1,0};
    vec3 vz={0,0,1};
    n=normalize(n);

    auto r1=(1-cos(theta))*(dot(n,vx)*n) +(cos(theta)*vx) + (sin(theta)*(cross(n,vx)));
    auto r2=(1-cos(theta))*(dot(n,vy)*n) +(cos(theta)*vy) + (sin(theta)*(cross(n,vy)));
    auto r3=(1-cos(theta))*(dot(n,vz)*n) +(cos(theta)*vz) + (sin(theta)*(cross(n,vz)));

	mat4 final={r1(0),r2(0),r3(0),0,
                r1(1),r2(1),r3(1),0,
                r1(2),r2(2),r3(2),0,
                0,0,0,1
    };
	return final;
}

inline mat4 lookAt(vec3 eye, vec3 center, vec3 up){
	up = normalize(up);
	vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f,up));
    vec3 u = cross(s,f);

    mat4 M1 =
            {
                    s(0),     s(1),     s(2),     0.0,
                    u(0),     u(1),     u(2),     0.0,
                    -f(0),    -f(1),    -f(2),     0.0,
                    0.0,     0.0,     0.0,     1.0
            };

    mat4 M2 =
            {
                    1.0,  0.0,  0.0,  -eye(0),
                    0.0,  1.0,  0.0,  -eye(1),
                    0.0,  0.0,  1.0,  -eye(2),
                    0.0,  0.0,  0.0,   1.0
            };


	return M1*M2;
}

inline mat4 orthogonal(float l, float r, float b, float t, float n, float f){
	return {
		2/(r-l),      0,     0,      (l+r)/(l-r),
			0,  2/(t-b),     0,      (b+t)/(b-t),
			0,        0, -2/(f-n),   (n+f)/(n-f),
			0,        0,      0,               1
	};	
}

inline mat4 frustum(float l, float r, float b, float t, float n, float f){
	mat4 Persp = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-(n+f)/n, -f,
		0, 0, -1/n, 0
	};
	mat4 Volume = {
		2/(r-l),      0,     0,      (l+r)/(l-r),
			0,  2/(t-b),     0,      (b+t)/(b-t),
			0,        0, 2/(f-n),    (n+f)/(n-f),
			0,        0,      0,               1
	};	
	return Volume*Persp;
}

inline mat4 perspective(float fovy, float aspect, float Near, float Far){
	float rad = (M_PI*fovy)/180;
	float n=Near*tan(rad/2);
	float b =-n;
	float r= n*aspect;
	float l =-r;
	return frustum(l,r,b,n,-Near,-Far);
}

#endif