#ifndef _PELOTITA_H_
#define _PELOTITA_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

#define PELOTITA_SPRITE "SHOT"

typedef struct pelotita pelotita_t;

//Crea un pelotita en la posicion (x,y) de angulo  y radio dado
pelotita_t *pelotita_crear(float x, float y, float angulo, float radio);

//Libera la memoria asociada al pelotita d
void pelotita_destruir(void *d);

//Actualiza las variables de estado del pelotita d segun un intervalo de tiempo dt
void pelotita_mover(pelotita_t *d, float dt);

//Grafica el pelotita d sobre la pantalla
void graficar_pelotita(SDL_Renderer *renderer, pelotita_t * d);
//corrobora si se trabo la pelota 
bool se_trabo (float vel);

#endif // _PELOTITA_H_
