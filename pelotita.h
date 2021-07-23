#ifndef _PELOTITA_H_
#define _PELOTITA_H_

#include <stdbool.h>

#define PELOTITA_SPRITE "SHOT"

typedef struct pelotita pelotita_t;

//Crea un pelotita en la posicion (x,y) de angulo a
pelotita_t * pelotita_crear(float x, float y, float a);

//Libera la memoria asociada al pelotita d
void pelotita_destruir(void *d);

//Actualiza las variables de estado del pelotita d segun un intervalo de tiempo dt
void pelotita_mover(pelotita_t * d, float dt);

//Grafica el pelotita d sobre la pantalla
bool pelotita_dibujar(pelotita_t * d);

//Devuelve la coordenada x del pelotita d
float pelotita_get_x(const pelotita_t *d);

//Devuelve la coordenada y del pelotita d
float pelotita_get_y(const pelotita_t *d);

//Devuelve el angulo del pelotita d
float pelotita_get_angulo(const pelotita_t *d);

//Devuelve el tiempo de vida del pelotita d
float pelotita_get_tiempo(const pelotita_t *d);

#endif // _PELOTITA_H_