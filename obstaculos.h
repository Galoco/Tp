
typedef enum color {AZUL, NARANJA, VERDE, GRIS} color_t;

typedef enum movimiento {MOV_INMOVIL, MOV_CIRCULAR, MOV_HORIZONTAL} movimiento_t;

typedef enum geometria {GEO_CIRCULO, GEO_RECTANGULO, GEO_POLIGONO} geometria_t;

typedef struct poligono{
    float (*vertices)[2];
    size_t n;
} poligono_t;




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

poligono_t *objeto_clonar(const poligono_t *poligono);
