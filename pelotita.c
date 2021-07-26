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
	float angulo;
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

bool pelotita_dibujar(pelotita_t * bola)
{
	return graficador_dibujar(DISPARO_SPRITE, 1, bola->x, bola->y, bola->angulo);
}


// LAS FUNCIONES SIGUIENTES DEVUELVEN LOS PARAMETROS
float disparo_get_x(const disparo_t *bola)
{
    return bola->x;
}

float disparo_get_y(const disparo_t *bola)
{
    return bola->y;
}

float disparo_get_angulo(const disparo_t *bola)
{
    return bola->angulo;
}

float disparo_get_tiempo(const disparo_t *bola)
{
	return bola->tiempo;
}
