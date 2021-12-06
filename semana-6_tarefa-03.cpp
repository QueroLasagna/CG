#include "Graphics2D.h"
#include "Clip2D.h"
#include <iostream>

//Teste do drawPrimitive
int main(){
	ClipRectangle R = {100, 200, 500, 400};

	std::vector<Vec2Col> P = {
		Vec2Col{{75, 280}, red},
		Vec2Col{{443, 124}, green},
		Vec2Col{{574, 470}, magenta}
	};

	TriangleFan T{P.size()};

	std::vector<vec2> RP = {
		{R.x0, R.y0},  {R.x1, R.y0},
		{R.x1, R.y1},  {R.x0, R.y1},
	};
	LineLoop LR{4};

	Graphics2D G(600, 600);
	G.clear();
	G.draw(P, T);
	G.draw(RP, LR, blue);

	G.savePNG("output5.png");

}