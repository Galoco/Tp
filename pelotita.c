#include <SDL2/SDL.h>
#include <math.h>

#include "pelotita.h"
#include "config.h"
#include "fisica.h"

#define VEL_MIN 0.5

struct pelotita
{
	float x;
	float y;
	float radio;
};


pelotita_t *pelotita_crear(float x, float y, float radio){
	pelotita_t * bola = malloc(sizeof(pelotita_t));
	if(bola == NULL)
		return NULL;
    
	bola->x = x;
	bola->y = y;

	bola->radio = radio;

	return bola;
}

void pelotita_destruir(void *bola){
	free (bola);
}

void graficar_pelotita(SDL_Renderer* renderer, pelotita_t * bola){
    float angulo=0;
    for (size_t i = 0 ; i< 720; i++){
        angulo +=  (0.5*PI/180);
		float coseno = (bola->radio * cos(angulo));
		float seno = (bola->radio * sin (angulo));
        SDL_RenderDrawLine(renderer, (bola->x + coseno), (bola->y + seno), bola->x, bola->y);
    }
}

bool se_trabo (float vel){
    float a = pow(vel, 2);
    float vel_minima = VEL_MIN;
    return (a <= vel_minima && a!= 0);
}
