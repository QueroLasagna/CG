
#include "Image.h"

float F(float x, float y){
	return x - 3*y + 200;
}

int main(){
	Image img(600, 600);
	img.fill(white);
	for(int y = 0; y < 600; y++)
		for(int x = 0; x < 600; x++)
			if(F(x,y) <= 0)
				img(x,y) = red;
		

	img.savePNG("output.png");
}
