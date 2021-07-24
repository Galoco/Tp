#include "obstaculos.h"
#include "graficador.h"
#include "config.h"
#include "fisica.h"
#include "poligono.h"
#include "lecturas.h"

#include <math.h>

struct obstaculo 
{
    float x;
    float y;
    float v;
    float *color;
    float *geometria;
    float *movimiento;
   
};


obstaculo_t *obstaculo_crear(float x, float y, float radio)
{
    
}

void obstaculo_destruir(void * a)
{
	
}

void obstaculo_mover(obstaculo_t * a, float dt)
{
	
}

bool obstaculo_dibujar(const obstaculo_t *a)
{
    
}

bool obstaculo_colision(const obstaculo_t *a, float x, float y)
{
	}

float obstaculo_get_x(const obstaculo_t *a)
{
    //hace una funcion para cada parametro de obstaculo
}


