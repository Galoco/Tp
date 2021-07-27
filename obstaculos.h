#ifndef _OBSTACULO_H_
#define _OBSTACULO_H_

#include <stdbool.h>

typedef struct obstaculo obstaculo_t;

//Crea un obstaculo en la posicion (x,y) de radio r
obstaculo_t *obstaculo_crear(float x, float y, float r);

//Libera la memoria asociada al obstaculo a
void obstaculo_destruir(void * a);

//Actualiza las variables de estado del obstaculo a segun un intervalo de tiempo dt
void obstaculo_mover(obstaculo_t * a, float dt);

//Grafica el obstaculo a sobre la pantalla
bool obstaculo_dibujar(const obstaculo_t *a);

//Testea si el par de coordenadas (x,y) rebota con el obstaculo a
bool obstaculo_rebote(const obstaculo_t *a, float x, float y);

//Devuelve la coordenada x del obstaculo a
float obstaculo_get_x(const obstaculo_t *a);

//Devuelve la coordenada y del obstaculo a
float obstaculo_get_y(const obstaculo_t *a);

//Devuelve el radio del obstaculo a
float obstaculo_get_radio(const obstaculo_t *a);

void rebote();

#endif // _OBSTACULO_H
