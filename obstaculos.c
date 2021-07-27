#include <SDL2/SDL.h>
#include <math.h>

#include "obstaculos.h"
#include "graficador.h"
#include "config.h"
#include "fisica.h"
#include "poligono.h"
#include "lecturas.h"


struct obstaculo{
    color_t color;
    movimiento_t movimiento;
    geometria_t geometria;
    int16_t parametros[3];
    size_t n_parametros;
    poligono_t *poligono;
    bool eliminado;
};


obstaculo_c_t *obstaculo_crear(FILE *f){
    obstaculo_c_t *o = malloc(sizeof(obstaculo_t));
    if(o == NULL) return NULL;

    if(leer_encabezado(f, &(o->color), &(o->movimiento), &(o->geometria)))
        if (leer_movimiento(f, o->movimiento, o->parametos, &(o->n_parametros)))
            o->poligono = leer_geometria(f, o->geometira);
        
    o->eliminado = false;
    
    return o;
}

void destruir_obstaculo(obstaculo_t *o, void (*destruir)(void *)){
    if (destruir != NULL)
        for (size_t i = 0; i < o->poligono->n; i++)
            destruir(o->poligono->vertices[i]);
        
    poligono_destruir(o->poligono);
    free(o);
}

void obstaculo_movimiento(obstaculo_t *o){
    if(o->movimiento == MOV_CIRCULAR)
        while(o->eliminado != true){
            poligono_rotar_centrado(o->poligono, o->parametros[0], o->parametros[1], o->parametros[2] * DT);
        }
    if(o->movimiento == MOV_HORIZONTAL)
        while(o->eliminado != true){
            float norm_x, norm_y;
            trasladar(o->poligono, o->poligono->n, poligono_distancia(o->poligono, o->parametros[1], 0, &norm_x, norm_y), 0);
            while(1){
                float v = parametros[2];
                trasladar(o->poligono, o->poligono->n, v/DT, 0);
                if((o->poligono[0][0] != o->parametros[0]) && (o->poligono[2][0] =! 0))
                    v = -v;
            }
        } 
}

void obstaculo_dibujar(const obstaculo_t *o){
    if(o->eliminado == false){
        if (o->color == AZUL)
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        if (o->color == NARANJA)
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x9B, 0x00, 0x00);
        if (o->color == VERDE)
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        if (o->color == GRIS)
            SDL_SetRenderDrawColor(renderer, 0x87, 0x87, 0x87, 0x00);

        SDL_RenderDrawLine(renderer, o->poligono->vertices[0][0], o->poligono->vertices[0][1], 
                                        o->poligono->vertices[o->poligono->n - 1][0], o->poligono->vertices[o->poligono->n - 1][1]);
        for (size_t i = 1; i <= o->poligono->n - 1; i++)
            SDL_RenderDrawLine(renderer, o->poligono->vertices[i-1][0], o->poligono->vertices[i-1][1], 
                                        o->poligono->vertices[i][0], o->poligono->vertices[i][1]);       
    } 
}

bool obstaculo_rebote(obstaculo_t *o, float, x, float y){
    if(o->color != GRIS){
        if (o->geometria == GEO_RECTANGULO){
            bool reboto = (sqrt((x - o->x)*(x - o->x) + (y - o->y)*(y - o->y)) <= (o->poligono->vertices[0][0] - o->poligono->vertices[1][0]))||
                            (sqrt((x - o->x)*(x - o->x) + (y - o->y)*(y - o->y)) <= (o->poligono->vertices[1][1] - o->poligono->vertices[2][1]));
            
            destruir_obstaculo(o, free);    
        }

        if (o->geometria == GEO_CIRCULO){
            bool reboto = sqrt((x - o->x)*(x - o->x) + (y - o->y)*(y - o->y)) <= distancia(o->poligono->vertices[0][0], o->poligono->vertices[0][1], o->poligono->vertices[(o->poligono->n/2)-1][0], o->poligono->vertices[(o->poligono->n/2)-1][1]);
            
            destruir_obstaculo(o, free);
        }
        return reboto;
    }

    if (o->geometria == GEO_RECTANGULO)
        bool reboto = (sqrt((x - o->x)*(x - o->x) + (y - o->y)*(y - o->y)) <= (o->poligono->vertices[0][0] - o->poligono->vertices[1][0]))||
                        (sqrt((x - o->x)*(x - o->x) + (y - o->y)*(y - o->y)) <= (o->poligono->vertices[1][1] - o->poligono->vertices[2][1]));
            
    if (o->geometria == GEO_CIRCULO)
        bool reboto = sqrt((x - o->x)*(x - o->x) + (y - o->y)*(y - o->y)) <= distancia(o->poligono->vertices[0][0], o->poligono->vertices[0][1], o->poligono->vertices[(o->poligono->n/2)-1][0], o->poligono->vertices[(o->poligono->n/2)-1][1]);
        
    return reboto;
}



