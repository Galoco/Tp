#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct poligono{
    float (*vertices)[2];
    size_t n;
} poligono_t;

//ver si necesito googlear una formula
double poligono_distancia(const poligono_t *p, float cx, float cy, float *norm_x, float *norm_y){


}

//trasladar + rotar
poligono_rotar_centrado(p, cx, cy, ang);

void trasladar(float poligono[][2], size_t n, float dx, float dy);//
void rotar(float poligono[][2], size_t n, double rad); //
bool poligono_agregar_vertice(poligono_t *poligono, float x, float y);

