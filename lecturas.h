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


//funciones de lectura
leer_geometria(); // cambiar parametros de salida de las funciones ej 4
bool leer_encabezado(FILE *f, color_t *color, movimiento_t *movimiento, geometria_t *geometria);

bool leer_movimiento_inmovil(FILE *f, int16_t parametros[], size_t *n_parametros); //para los obstaculos circulares

bool leer_movimiento_circular(FILE *f, int16_t parametros[], size_t *n_parametros); // los parametros deben ser el centro y la velocidad

bool leer_movimiento_horizontal(FILE *f, int16_t parametros[], size_t *n_parametros); //para las plataformas, hay que modificarlo. parametros x1,xi y velocidad.

typedef bool (*t_mov_t)(FILE *f, int16_t parametros[], size_t *n_parametros);

t_mov_t mov[] = { // movimientos de los obstaculos
    [MOV_INMOVIL] = leer_movimiento_inmovil, //puntos
    [MOV_CIRCULAR] = leer_movimiento_circular, //grupos de obstaculos
    [MOV_HORIZONTAL] = leer_movimiento_horizontal //plataformas
    };


bool leer_movimiento(FILE *f, movimiento_t movimiento, int16_t parametros[], size_t *n_parametros);

poligono_t *leer_geometria_circulo(FILE *f);//va a tener que ser tambien asi la pelotita

poligono_t *leer_geometria_rectangulo(FILE *f);//plataformas

poligono_t *leer_geometria_poligono(FILE *f);//???


typedef poligono_t *(*t_geo_t)(FILE *f);

t_geo_t geo[] = {
    [GEO_CIRCULO] = leer_geometria_circulo,
    [GEO_RECTANGULO] = leer_geometria_rectangulo,
    [GEO_POLIGONO] = leer_geometria_poligono
    };


poligono_t *leer_geometria(FILE*f, geometria_t geometria);//tenenmos q crear la geometria dada en un espacio de memoria
