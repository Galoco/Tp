#include <poligono.h>

void trasladar(float poligono[][2], size_t n, float dx, float dy){
    for (int i = 0; i < n; i++){
        poligono[i][0] += dx;
        poligono[i][1] += dy;
    } 
}

void rotar(float poligono[][2], size_t n, double rad){
    double cosn = cos(rad);
    double sen = sin(rad);
    
    for (int i = 0; i < n; i++){

        float x = poligono[i][0] * cosn - poligono[i][1] * sen;
		float y = poligono[i][0] * sen + poligono[i][1] * cosn;

        poligono[i][0] = x;
		poligono[i][1] = y;
    }   
}

poligono_rotar_centrado(poligono_t *p, float cx, float cy, float ang)//trasladar + rotar+ trasladar (Diseñarla nosotros)
{
    //trasladarlo el largo del objeto al centro - el largo por el sen(ang)
    //luego rotarlo ang
    // luego trasladarlo hacia abajo cos(ang)
}

//ver si necesito googlear una formula
double poligono_distancia(const poligono_t *p, float cx, float cy, float *norm_x, float *norm_y){
    //usar poligono_en_poligono  para verificar q el pto este afuera
    double *dist = malloc();//pedir memoria para la cantidad de puntos a verificar;
    for (size_t i = 0; i < p->n; i++){
        dist[i] = ;//usar formula de distancia, conviene hacer una funcion aparte

    }
    //extraer el valor menor de dist y guardarlo
    //liberar el resto de valores de la memoria
    *norm_x = cx-/*coordenada mas cercana x*/ ;
    *norm_y = cy - /*coordenada mas cercana y*/;
    
    return /*valor guardado*/;
}

poligono_t *poligono_crear(float vertices[][2], size_t n); //vamos a ponerle de nombre poligono a estas funciones parra generalizar

void poligono_destruir(poligono_t *poligono);

bool poligono_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y);

poligono_t *poligono_clonar(const poligono_t *poligono);

float product_vect(float ax, float ay, float bx, float by );

bool punto_en_triangulo(float px, float py, float ax, float ay, float bx, float by, float cx, float cy);

bool punto_en_poligono(float poligono[][2], size_t n, float px, float py);

