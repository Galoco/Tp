#include "obstaculos.h"
#include "graficador.h"
#include "config.h"
#include "fisica.h"
#include "poligono.h"
#include "lecturas.h"

#include <math.h>

void obstaculo_movimiento(poligono_t *p, FILE *f, movimiento_t movimiento, int16_t parametros[], size_t *n_parametros )
{
	if(leer_movimiento(f, movimiento, parametros, *n_parametros))
        if(movimiento == MOV_CIRCULAR)
            while(p != NULL){
                poligono_rotar_centrado(p, parametros[0], parametros[1], parametros[2]/DT);
            }
        if(movimiento == MOV_HORIZONTAL)
            while(p != NULL){
                trasladar(p, p->n, parametros[1], 0);
                while((parametros[1] != parametros[0]) && (parametros[1] =! 0)){
                        trasladar(p, p->n, parametros[2]/DT, 0);
                    if((parametros[1] != parametros[0]) && (parametros[1] =! 0))
                        trasladar(p, p->n, -parametros[2]/DT, 0);

                }
            } 
}


bool obstaculo_dibujar(const poligono_t *p)
{
    
}

bool obstaculo_rebote(const poligono_t *p, float x, float y)
{

}



