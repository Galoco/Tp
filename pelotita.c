#include "pelotita.h"
#include "graficador.h"
#include "config.h"
#include "fisica.h"

#include <math.h>

typedef struct pelotita
{
	float x;
	float y;
	float vx;
	float vy;
	float radio;
	float tiempo;
}pelotita_t;


pelotita_t *pelotita_crear(float x, float y, float angulo)
{
	pelotita_t * bola = malloc(sizeof(pelotita_t));
	if(bola == NULL){
		return NULL
    }

	bola->x = x;
	bola->y = y;
	bola->angulo = angulo;

	bola->vx = BOLA_VI* cos(angulo);
	bola->vy = BOLA_VI * sin(angulo);

	bola->tiempo = 0;

	return bola;
}

void pelotita_destruir(void *bola)
{
	free (bola);
}

void pelotita_mover(pelotita_t * bola, float dt)
{
	bola->x = computar_posicion(bola->x, bola->vx, dt);
	bola->y = computar_posicion(bola->y, bola->vy, dt);
	bola->tiempo += dt;
	graficador_ajustar_variables(&(bola->x), &(bola->y));	
}

void graficar_pelotita(pelotita_t * bola){
    float angulo=0;
    for (size_t i = 0 ; i< 720; i++){
        angulo+= grados_a_radianes (0.5);
		float coseno=(bola->radio * cos(angulo));
		float seno = (bola->radio * sin (angulo));
        SDL_RenderDrawLine(renderer, (bola->x + coseno), (bola->y + seno), bola->x, bola->y);
    }
}


// LAS FUNCIONES SIGUIENTES DEVUELVEN LOS PARAMETROS
float pelotita_get_x(const pelotita_t *bola)
{
    return bola->x;
}

float pelotita_get_y(const pelotita_t *bola)
{
    return bola->y;
}

float pelotita_get_radio(const pelotita_t *bola)
{
    return bola->radio;
}


float pelotita_get_tiempo(const pelotita_t *bola)
{
	return bola->tiempo;
}
