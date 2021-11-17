#include "Color.h"
#include "vec.h"
#include "Image.h"

int main() {
    Image imagem(600,600);
    
    Color
    A = {255, 0, 0},
    B = {0, 255, 0},
    C = {0, 0, 255},
    D = {255, 0, 255};
    
    for(int x = 0; x < 600; x++) {
        for(int y = 0; y < 600; y++) {
            imagem(x, y) = bilerp((float)x/600.0, (float)y/600.0, C, D, A,  B);
        }
    }

    imagem.savePNG("interpolacao.png");
    return 0;
}