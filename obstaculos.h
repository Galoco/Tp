#ifndef _OBSTACULO_H_
#define _OBSTACULO_H_

#include <stdbool.h>

typedef struct obstaculo obstaculo_t;

//Crea un obstaculo leido de f
obstaculo_c_t *obstaculo_crear(FILE *f);

//Libera la memoria asociada al obstaculo o
void destruir_obstaculo(obstaculo_t *o, void (*destruir)(void *));

//Actualiza las variables de estado del obstaculo o segun su movimietno
void obstaculo_movimiento(obstaculo_t *o);

//Grafica el obstaculo o sobre la pantalla
void obstaculo_dibujar(const obstaculo_t *o);

//Testea si el par de coordenadas (x,y) rebota con el obstaculo a
bool obstaculo_rebote(obstaculo_t *o, float, x, float y)

#endif // _OBSTACULO_H
