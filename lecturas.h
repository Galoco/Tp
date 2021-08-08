#ifndef _LECTURAS_H_
#define _LECTURAS_H_
#include <stdlib.h>

#include "poligono.h"

#define MASK_COLOR 0xC0
#define MASK_MOVIMIENTO 0x30
#define MASK_GEOMETRIA 0x0F

#define SHIFT_COLOR 6
#define SHIFT_MOVIMIENTO 4
#define SHIFT_GEOMETRIA 0

typedef enum color {AZUL, NARANJA, VERDE, GRIS} color_t;

typedef enum movimiento {MOV_INMOVIL, MOV_CIRCULAR, MOV_HORIZONTAL} movimiento_t;

typedef enum geometria {GEO_CIRCULO, GEO_RECTANGULO, GEO_POLIGONO} geometria_t;

//Lee el encabezado devuelve true si todo es correcto y su color, movimiento y geometria
bool leer_encabezado(FILE *f, color_t *color, movimiento_t *movimiento, geometria_t *geometria);
//Lee,  devuelve true si todo es correcto y los parametros
bool leer_movimiento_inmovil(FILE *f, int16_t parametros[], size_t *n_parametros);
//Lee,  devuelve true si todo es correcto y los parametros del movimiento circular
bool leer_movimiento_circular(FILE *f, int16_t parametros[], size_t *n_parametros); 
//Lee,  devuelve true si todo es correcto y los parametros del movimiento horizontal
bool leer_movimiento_horizontal(FILE *f, int16_t parametros[], size_t *n_parametros);

typedef bool (*t_mov_t)(FILE *f, int16_t parametros[], size_t *n_parametros);


//Lee el movimiento dado y devuelve true si todo es correcto
bool leer_movimiento(FILE *f, movimiento_t movimiento, int16_t parametros[], size_t *n_parametros);
//Lee y devuelve el poligono circular leido
poligono_t *leer_geometria_circulo(FILE *f);
//Lee y devuelve el poligono rectangular leido
poligono_t *leer_geometria_rectangulo(FILE *f);
//Lee y devuelve el poligono poligonal leido
poligono_t *leer_geometria_poligono(FILE *f);

typedef poligono_t *(*t_geo_t)(FILE *f);


//Lee y devuelve un poligono de la geometria dada
poligono_t *leer_geometria(FILE*f, geometria_t geometria);

#endif