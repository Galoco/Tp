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
/*poligono_t *p = poligono_crear(...);
    if(p == NULL) return NULL; // Crear en el origen
    poligono_rotar(p, rotacion);
    poligono_trasladar(p, cx, cy); // Del EJ2
    // Del EJ2
    return p;*/

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


