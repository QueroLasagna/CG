#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <vector>
#include "geometry.h"
#include "Image.h"
#include "VertexUtils.h"
#include "Primitives.h"
#include "rasterization.h"
#include "Clip2D.h"
	
class Graphics2D{
	Image img;

	public:
	Graphics2D(int w, int h) : img{w, h}{}

	void clear(Color col = white){
		img.fill(col);
	}
	
	void savePNG(std::string filename){
		img.savePNG(filename);	
	}
	
	template<class Prims>
	void draw(const std::vector<vec2>& V, const Prims& P, Color color){
		std::vector<Vec2Col> VC;
		for(vec2 v: V)
			VC.push_back({v, color});
		draw(VC, P);
	}

	template<class Prims>
	void draw(const std::vector<Vec2Col>& V, const Prims& P){
		ClipRectangle R = {-0.5f, -0.5f, img.width-0.5f, img.height-0.5f};
		for(auto primitive: clip(assemble(P, V), R))
			drawPrimitive(primitive);
	}

	void paint(Pixel p, Color c){
		if(p.x >= 0 && p.y >= 0 && p.x < img.width && p.y < img.height)
			img(p.x,p.y) = c;
	}

	void drawPrimitive(Line<Vec2Col> line){
		vec2  L[] = { line[0].position, line[1].position };
		Color C[] = { line[0].color,    line[1].color    };

		for(Pixel p: rasterizeLine(L)){
			float t = find_mix_param(toVec2(p), L[0], L[1]);
			Color color = lerp(t, C[0], C[1]);
			paint(p, color);
		};
	}

	void drawPrimitive(Triangle<Vec2Col> tri){
	/**************** TAREFA - AULA 09 **************/
		vec2 v0 = tri[0].position, v1 = tri[1].position, v2 = tri[2].position;
		Color c0 = tri[0].color, c1 = tri[1].color, c2 = tri[2].color;

        std::array<vec2, 3> pontos = {v0,v1,v2};
        for(Pixel p: rasterizeTriangle(pontos)){
            vec2 v = {(float)p.x, (float)p.y};
			vec3 resultado = barycentric(v, pontos);
			Color color = toColor((resultado[0]*toVec3(c0)) + (resultado[1]*toVec3(c1)) + (resultado[2]*toVec3(c2)));
			paint(p, color);
		}
	}
};

#endif
