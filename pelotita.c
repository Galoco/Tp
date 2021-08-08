#include <SDL2/SDL.h>
#include <math.h>

#include "pelotita.h"
#include "config.h"
#include "fisica.h"


struct pelotita
{
	float x;
	float y;
	float vx;
	float vy;
	float radio;
	float tiempo;
};


pelotita_t *pelotita_crear(float x, float y, float angulo, float radio)
{
	pelotita_t * bola = malloc(sizeof(pelotita_t));
	if(bola == NULL)
		return NULL;
    

	bola->x = x;
	bola->y = y;

	bola->vx = BOLA_VI * cos(angulo);
	bola->vy = BOLA_VI * sin(angulo);

	bola->radio = radio;

	bola->tiempo = 0;

	return bola;
}

void pelotita_destruir(void *bola)
{
	free (bola);
}

void pelotita_mover(pelotita_t * bola, float dt)
{
	bola->vy = computar_velocidad(bola->vy, G, dt);
	bola->vx *= ROZAMIENTO;
    bola->vy *= ROZAMIENTO;
	bola->x = computar_posicion(bola->x, bola->vx, dt);
	bola->y = computar_posicion(bola->y, bola->vy, dt);

	bola->tiempo += dt;
		
}

void graficar_pelotita(SDL_Renderer* renderer, pelotita_t * bola){
    float angulo=0;
    for (size_t i = 0 ; i< 720; i++){
        angulo+=  (0.5*PI/180);
		float coseno =(bola->radio * cos(angulo));
		float seno = (bola->radio * sin (angulo));
        SDL_RenderDrawLine(renderer, (bola->x + coseno), (bola->y + seno), bola->x, bola->y);
    }
}
bool se_trabo (float vel){
    float a = pow(vel, 2);
    float vel_minima = 0.01;
    return (a <= vel_minima);
}
