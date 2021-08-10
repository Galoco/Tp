#ifndef _PELOTITA_H_
#define _PELOTITA_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

#define PELOTITA_SPRITE "SHOT"

typedef struct pelotita pelotita_t;

//Crea un pelotita en la posicion (x,y) de radio dado
pelotita_t *pelotita_crear(float x, float y, float radio);

//Libera la memoria asociada al pelotita d
void pelotita_destruir(void *d);

//Grafica el pelotita d sobre la pantalla
void graficar_pelotita(SDL_Renderer *renderer, pelotita_t * d);

//Corrobora si se trabo la pelota 
bool se_trabo (float vel);

#endif // _PELOTITA_H_
