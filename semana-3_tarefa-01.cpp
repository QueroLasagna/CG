#include "Image.h"

int main(){
	
    Image img(600, 600);

    // Se imagem é 600 x 600 então cada quadrado tem 75 x 75
            
	img.fill(white);

    bool paintItBlack = false;

    int count_x = 0, count_y = 0;

	for(int y = 0; y < 600; y++){
		
        if(count_y > 75){
            paintItBlack = !paintItBlack;
            count_y = 0;
        }
        
        for(int x = 0; x < 600; x++){

            if(count_x > 75){
                paintItBlack = !paintItBlack;
                count_x = 0;
            }

            if (paintItBlack)
                img(x,y) = black;

            count_x++;
        }
        count_y++;
    }
	img.savePNG("chess.png");

    return 0; 
}
