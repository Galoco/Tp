#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct poligono{
    float (*vertices)[2];
    size_t n;
};
typedef struct poligono poligono_t;

//Crea el poligono de la cantidad de vertices que se requieran
poligono_t *poligono_crear(float vertices[][2], size_t n);
//libera la memoria utilizada para el poligono anteriormente creado
void poligono_destruir(poligono_t *poligono);
//devuelve el vertice pedido
bool poligono_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y);
//copia el contenido de un poligono en otro nuevo
// poligono_t *poligono_clonar(const poligono_t *poligono);
// //añade un vertice al poligono 
bool poligono_agregar_vertice(poligono_t *poligono, float x, float y);
//Dibuja el poligono dado
void poligono_dibujar(SDL_Renderer *renderer, poligono_t *poligono);
//FUNCIONES AUXILIARES PARA MOVER, CALCULAR, CREAR Y CAMBIAR VARIABLES(podriamos hacer otro .h)
//tralada el poligono en ejes los ejes x e y
void trasladar(poligono_t *poligono, float dx, float dy);
//rota el poligono en rad angulos (valor en radianes)
void rotar(poligono_t *poligono, double rad); 
//rota ang (en angulos) alrededor de un punto con centro en (cx, cy) 
void poligono_rotar_centrado(poligono_t *p, float cx, float cy, float ang);
//devuelve la norma del vector distancia entre dos puntos
double distancia(int x1, int y1, int x2, int y2);
//devuelve el valor del producto interno entre los puntos (ax, ay) y (bx, by)
double producto_interno (double ax, double bx, double ay, double by);
//devuelve el punto mas cercano dentro de un conjunto
void punto_mas_cercano(float x0, float y0, float x1, float y1, float xp, float yp, float *x, float *y);
//refleja la direccion
void reflejar(float norm_x, float norm_y, float *cx, float *cy, float *vx, float *vy);
//devuelve la distancia al punto mas cercano de un poligono
double poligono_distancia(const poligono_t *p, float cx, float cy, float *norm_x, float *norm_y);