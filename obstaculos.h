#ifndef _OBSTACULO_H_
#define _OBSTACULO_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "lecturas.h"
#include "pelotita.h"

struct obstaculo{
    color_t color;
    movimiento_t movimiento;
    geometria_t geometria;
    float parametros[3];
    size_t n_parametros;
    poligono_t *poligono;
    bool eliminado;
};

typedef struct obstaculo obstaculo_t;

//Crea un obstaculo leido de f
obstaculo_t *obstaculo_crear(FILE *f);

//Libera la memoria asociada al obstaculo o
void destruir_obstaculo(obstaculo_t *o);

//Actualiza las variables de estado del obstaculo o segun su movimietno
void obstaculo_movimiento(obstaculo_t *o);

//Grafica el obstaculo o sobre la pantalla segun sus variables
void obstaculo_dibujar(SDL_Renderer *renderer, const obstaculo_t *o);

//Testea si el par de coordenadas (x,y) rebota con el obstaculo o y devuelve la normal en el punto más cercano
bool obstaculo_reboto(obstaculo_t *o, float x, float y, float *norm_x, float *norm_y);

#endif // _OBSTACULO_H
