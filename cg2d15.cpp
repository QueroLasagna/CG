#include "Graphics2D.h"
#include <iostream>
int main(){
	std::vector<Vec2Col> P = {
		{{36, 116}, red}, {{108, 90}, green}, {{103, 164}, blue},
		{{-34, -37}, red}, {{32, 78}, green}, {{127, 26}, blue},
		{{145, 43}, red}, {{278, 15}, green}, {{125, -82}, blue}, 
		{{256, 172}, red}, {{271, 69}, green}, {{149, 118}, blue}, 
		{{185, 213}, red}, {{247, 254}, green}, {{229, 188}, blue},
	};

	Triangles T{P.size()};
	std::cout<<P.size();
	Graphics2D G(200, 200);
	G.clear();
	G.draw(P, T);
	G.savePNG("output.png");
}
