#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

//MACROS
#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define VENTANA_ANCHO 800
#define VENTANA_ALTO 600

#define MIN_X 77
#define MAX_X 721
#define MIN_Y 52
#define MAX_Y 592

#define CANON_X 401
#define CANON_Y 71
#define CANON_LARGO 93
#define CANON_MAX 1.6790669176553528

#define BOLA_RADIO 6
#define BOLA_VI 450

#define JUEGO_FPS 200

#define G 600
#define PLASTICIDAD 0.8
#define ROZAMIENTO 0.9999

#endif // _CONFIG_H_

#define MASK_COLOR 0xC0
#define MASK_MOVIMIENTO 0x30
#define MASK_GEOMETRIA 0x0F

#define SHIFT_COLOR 6
#define SHIFT_MOVIMIENTO 4
#define SHIFT_GEOMETRIA 0


typedef enum color {AZUL, NARANJA, VERDE, GRIS} color_t;

typedef enum movimiento {MOV_INMOVIL, MOV_CIRCULAR, MOV_HORIZONTAL} movimiento_t;

typedef enum geometria {GEO_CIRCULO, GEO_RECTANGULO, GEO_POLIGONO} geometria_t;

typedef struct poligono{
    float (*vertices)[2];
    size_t n;
} poligono_t;

//Funciones de la pelotita(se genera cada vez q se mueve)
/*double computar_velocidad (double vi, double a, double dt);
double computar_posicion (double pi, double vi, double dt);

void posicion (double v, double ax, double ay, double dt, double h, double ang);//ESTE NOS SIRVE??
//leer_geometria_circulo, objeto_crear, objeto_destruir.




//funciones para obstaculos
void trasladar(float poligono[][2], size_t n, float dx, float dy);//
void rotar(float poligono[][2], size_t n, double rad); //

poligono_rotar_centrado(p, cx, cy, ang)//trasladar + rotar+ trasladar (Diseñarla nosotros)


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


poligono_t *objeto_crear(float vertices[][2], size_t n); //vamos a ponerle de nombre objeto a estas funciones parra generalizar

void objeto_destruir(poligono_t *poligono);

bool objeto_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y);

poligono_t *objeto_clonar(const poligono_t *poligono);*/ //LAS DEJO COMENTADAS PORQUE YA HICE EL .h






// funciones para entorno*******
void angulos_cambiados()// la pantalla arranca arriba iz con x e y crecientes hacia derecha y arriba
//objeto_crear

//FUNCIONES INTERACTIVAS

void rebote(){
    //vamos a usar la funcion tal de tal ej
}
double poligono_distancia(const poligono_t *p, float cx, float cy, float *norm_x, float *norm_y)//ver si necesito googlear una formula
void reflejar(float norm_x, float norm_y, float *cx, float *cy, float *vx, float *vy)//ver si necesito googlear una formula

float product_vect(float ax, float ay, float bx, float by );

bool punto_en_triangulo(float px, float py, float ax, float ay, float bx, float by, float cx, float cy);

bool punto_en_poligono(float poligono[][2], size_t n, float px, float py);

//funciones de lectura
leer_geometria() // cambiar parametros de salida de las funciones ej 4
bool leer_encabezado(FILE *f, color_t *color, movimiento_t *movimiento, geometria_t *geometria);




computacion_de_ptos()//

//verificar siempre velocidad pelota

eliminar_obstaculo()//cuando golpeo un objeto eliminable

reiniciar_juego()// arranca de nuevo con los objetos ya eliminados

//
