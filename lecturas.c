#include <lecturas.h>

leer_geometria(); // cambiar parametros de salida de las funciones ej 4
bool leer_encabezado(FILE *f, color_t *color, movimiento_t *movimiento, geometria_t *geometria);

bool leer_movimiento_inmovil(FILE *f, int16_t parametros[], size_t *n_parametros); //para los obstaculos circulares

bool leer_movimiento_circular(FILE *f, int16_t parametros[], size_t *n_parametros); // los parametros deben ser el centro y la velocidad

bool leer_movimiento_horizontal(FILE *f, int16_t parametros[], size_t *n_parametros); //para las plataformas, hay que modificarlo. parametros x1,xi y velocidad.



bool leer_movimiento(FILE *f, movimiento_t movimiento, int16_t parametros[], size_t *n_parametros);

poligono_t *leer_geometria_circulo(FILE *f);//va a tener que ser tambien asi la pelotita

poligono_t *leer_geometria_rectangulo(FILE *f);//plataformas

poligono_t *leer_geometria_poligono(FILE *f);//???


poligono_t *leer_geometria(FILE*f, geometria_t geometria);//tenenmos q crear la geometria dada en un espacio de memoria
