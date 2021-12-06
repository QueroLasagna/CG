#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include <algorithm>
#include <cmath>
#include "vec.h"
#include "geometry.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////

struct Pixel{
	int x, y;
};

struct Coeficientes{
	float a;
	float b;
	bool vertical, horizontal;
	float x, y;
};

inline Pixel toPixel(vec2 u){
	return { (int)round(u(0)), (int)round(u(1)) };
}

inline vec2 toVec2(Pixel p){
	return {(float)p.x, (float)p.y};
}

//////////////////////////////////////////////////////////////////////////////

template<class Line>
std::vector<Pixel> rasterizeLine(const Line& P){
	//return simple(P[0], P[1]);

	return dda(P[0], P[1]);

	//return bresenham(toPixel(P[0]), toPixel(P[1]));
}

//////////////////////////////////////////////////////////////////////////////

inline std::vector<Pixel> simple(vec2 A, vec2 B){
	std::vector<Pixel> out;
	vec2 d = B - A;
	float m = d(1)/d(0);
	float b = A(1) - m*A(0);

	int x0 = std::round(A(0));
	int x1 = std::round(B(0));

	for(int x=x0; x <= x1; x++){
		int y = round(m*x + b);
		out.push_back({x, y});
	}
	return out;
}

//////////////////////////////////////////////////////////////////////////////

inline std::vector<Pixel> dda(vec2 A, vec2 B){
	vec2 dif = B - A;
	float delta = std::max(fabs(dif(0)), fabs(dif(1)));

	vec2 d = (1/delta)*dif;
	vec2 p = A;

	std::vector<Pixel> out;
	for(int i = 0; i <= delta; i++){
		out.push_back(toPixel(p));
		p = p + d;
	}
	return out;
}

//////////////////////////////////////////////////////////////////////////////

inline std::vector<Pixel> bresenham_base(int dx, int dy){
	std::vector<Pixel> out;

	int D = 2*dy - dx; 
	int y = 0;
	for(int x = 0; x <= dx; x++){
		out.push_back({x, y});
		if(D > 0){
			y++;
			D -= 2*dx;
		}
		D += 2*dy;
	}
	return out;
}

inline std::vector<Pixel> bresenham(int dx, int dy){
	std::vector<Pixel> out;

	if(dx >= dy){
		out = bresenham_base(dx, dy);
	}else{
		out = bresenham_base(dy, dx);
		for(Pixel& p: out)
			p = {p.y, p.x};
	}
	return out;
}

inline std::vector<Pixel> bresenham(Pixel p0, Pixel p1){
	if(p0.x > p1.x)
		std::swap(p0, p1);

	std::vector<Pixel> out = bresenham(p1.x - p0.x, abs(p1.y - p0.y));

	int s = (p0.y <= p1.y)? 1: -1;

	for(Pixel& p: out)
		p = {p0.x + p.x, p0.y + s*p.y};

	return out;
}

//////////////////////////////////////////////////////////////////////////////

template<class Tri>
std::vector<Pixel> rasterizeTriangle(const Tri& P){
	//return simple_rasterize_triangle(P);
	return scanline(P);
}

//////////////////////////////////////////////////////////////////////////////
template<class Tri>
std::vector<Pixel> simple_rasterize_triangle(const Tri& P){
	vec2 A = P[0];
	vec2 B = P[1];
	vec2 C = P[2];

	int xmin =  ceil(std::min({A(0), B(0), C(0)}));
	int xmax = floor(std::max({A(0), B(0), C(0)}));
	int ymin =  ceil(std::min({A(1), B(1), C(1)}));
	int ymax = floor(std::max({A(1), B(1), C(1)}));

	std::vector<Pixel> out;
	Pixel p;
	for(p.y = ymin; p.y <= ymax; p.y++)
		for(p.x = xmin; p.x <= xmax; p.x++)
			if(is_inside(toVec2(p), P))
				out.push_back(p);
	return out;
}

bool mesmoPonto(vec2 ponto1, vec2 ponto2){

}

//////////////////////////////////////////////////////////////////////////////
template<class Tri>
std::vector<Pixel> scanline(const Tri& T){
	/* TAREFA */
    std::vector<Pixel> out; 
    // Se triangulo for degenerado, sair
    bool degenerado = false;

    int xmin =  ceil(std::min({T[0](0), T[1](0), T[2](0)}));
	int xmax = floor(std::max({T[0](0), T[1](0), T[2](0)}));
    int ymin =  ceil(std::min({T[0](1), T[1](1), T[2](1)}));
	int ymax = floor(std::max({T[0](1), T[1](1), T[2](1)}));

	// Testando casos de degeneração
    if (xmin == xmax || ymin == ymax){
        degenerado = true;
    }
    if (degenerado){
        return out;
    }
    //cout << xmin << endl << xmax << endl;
    std::vector<Coeficientes> coeficientes;
	for (int i = 0; i < 3; i++){
		// Pra controlar as variáveis 	
		int p1, p2;
		// montando os pares de pontos que formarão
		// as 3 faces (ou retas) do triangulo
		if (i + 1 >= 3){
			p1 = i;
			p2 = 0;
		} else {
			p1 = i;
			p2 = i + 1;
		}	
		// Calculando os coeficientes das 3 retas...
		// E armazenando num vetor...
		Coeficientes c;
        //
        //      struct Coeficientes{
	    //      float a;
	    //      float b;
	    //      bool vertical, horizontal;
	    //      float x;
        //      float y;
        //      };
        //
        // Se Diferença em x é zero, a reta é vertical
        if (T[p2](0) - T[p1](0) == 0 || T[p1](0) - T[p2](0) == 0){
            c.vertical = true;
            c.horizontal = false;
            // Guardar o x da reta
            c.x = (float)T[p2](0);
        // Se Diferença em y é zero, a reta é horizontal
        } else if (T[p2](1) - T[p1](1) == 0 || T[p1](1) - T[p2](1) == 0){
            c.vertical = false;
            c.horizontal = true;
            // Guardar o y da reta
            c.y = (float)T[p2](1);
        // Se nenhum dos casos acima ocorrer, a equação da reta pode ser calculada a seguir
        } else {	
			c.a = (T[p2](1) - T[p1](1)) / (T[p2](0) - T[p1](0));
			c.b = - (c.a * T[p1](0)) + T[p1](1);
			c.vertical = false;
            c.horizontal = false;
        }
		coeficientes.push_back(c);
	}
    Pixel p;
    std::vector<float> pontosDeIntersecao;
    bool pararIteracao;
    // Para cada reta y, calcular os pontos de interseção
    for (int y = ymin; y <= ymax; y++){
        // Resets
        pontosDeIntersecao.clear();
        pararIteracao = false;
        // Para cada reta do triangulo ...
        for(Coeficientes c: coeficientes){
			// Se a reta for horizontal
            // e o y analisado é o mesmo da reta (Ou concidente)
            // Então basta adicionar todos aqueles pixeis no "out"
            if (c.horizontal && c.y == y){
                for (int x = xmin; x <= xmax; x++){
                    p.x = x;
                    p.y = y;
                    out.push_back(p);
                }
                // Pular para o próximo y da iteração
                pararIteracao = true;
                break;
            }
            // Se a reta for vertical, então o ponto de interseção
            // é o próprio x dessa reta
            else if (c.vertical){
                pontosDeIntersecao.push_back(c.x);
            }
            // Se a reta tiver um coeficiente angular diferente de zero, calcular...
            else {
				// calculando o x que tem interseção com a equaçao da reta dada
				float x = ((y - c.b) / c.a);
				// ax + b = y
				// ax = y - b
				// x = (y - b) / a
				// Se o ponto encontrado estiver dentro do escopo do triangulo,
				// ele é adicionado como um ponto válido
				if (x >= xmin && x <= xmax){
					pontosDeIntersecao.push_back(x);
				}
			}
        }
        // Pular para o próximo y da iteração
        if (pararIteracao){
            continue;
        }
        // Se não, calcular o min e max dos pontos de interseção e
        // adicionar os pixeis entre eles no "out"
        else {
            float minimo = pontosDeIntersecao[0];
            float maximo = minimo;
            for(float x: pontosDeIntersecao){
                if (x <= minimo){
                    minimo = x;
                } else if (x > maximo){
                    maximo = x;
                }
            }
            int xMinimo = ceil(minimo);
            int xMaximo = floor(maximo);
            for (int i = xMinimo; i <= xMaximo; i++){
                p.x = i;
                out.push_back({p.x, y});
            }
        }
    }
	return out;
}


#endif
