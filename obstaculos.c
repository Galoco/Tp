#include <SDL2/SDL.h>

#include <math.h>
#include <assert.h>

#include "obstaculos.h"
#include "config.h"
#include "fisica.h"

//Esto habria que verificarlo, deberia estar bien
obstaculo_t *obstaculo_crear(FILE *f){    
    obstaculo_t *o = malloc(sizeof(obstaculo_t));
    if(o == NULL) return NULL;
    int16_t *parametros = malloc(3*sizeof(int16_t));
    
    assert(leer_encabezado(f, &(o->color), &(o->movimiento), &(o->geometria)));
    assert(leer_movimiento(f, o->movimiento, parametros, &(o->n_parametros)));
    for(size_t i = 0; i < o->n_parametros; i++) {
        o->parametros[i] = parametros[i];
    }
    o->poligono = leer_geometria(f, o->geometria);
       
    o->eliminado = false;

    free(parametros); 
    return o;
}

void destruir_obstaculo(obstaculo_t *o){
    poligono_destruir(o->poligono);
    free(o);
}

void obstaculo_movimiento(obstaculo_t *o){
    float v = o->parametros[2];
    
    if(o->movimiento == MOV_CIRCULAR)
        poligono_rotar_centrado(o->poligono, o->parametros[0], o->parametros[1], (float)v * DT*10);
        
    //HAY QUE ARREGLAR ESTO PORQ SE MUEVEN SOLO HACIA UN LADO
    if(o->movimiento == MOV_HORIZONTAL){
        o->parametros[1] += (v*DT);
        trasladar(o->poligono, v*DT, 0);
        
        if(o->parametros[1] > o->parametros[0] || o->parametros[1] < 0){
            o->parametros[2] = -v;
        }
       
    }
}

void obstaculo_dibujar(SDL_Renderer *renderer, const obstaculo_t *o){
    if(o->eliminado == false){
        if (o->color == AZUL)
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        if (o->color == NARANJA)
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x9B, 0x00, 0x00);
        if (o->color == VERDE)
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        if (o->color == GRIS)
            SDL_SetRenderDrawColor(renderer, 0x87, 0x87, 0x87, 0x00);
    }
    if(o->eliminado == true)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
    
    poligono_dibujar(renderer, o->poligono);
}

bool obstaculo_reboto(obstaculo_t *o, float x, float y, float *norm_x, float *norm_y){
    return (poligono_distancia(o->poligono, x, y, norm_x, norm_y) < BOLA_RADIO);
}