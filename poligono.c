#include <math.h>
#include <SDL2/SDL.h>

#include "poligono.h"
#include "config.h"

//ACA PARECE ESTAR TODO BIEN AHORA, CAMBIE UN PAR DE COSAS
poligono_t *poligono_crear(float vertices[][2], size_t n){ 
	poligono_t *poligono = malloc (sizeof (poligono_t));
    if  ((poligono== NULL)) return NULL;
    
    if(n != 0){
        poligono->vertices = malloc (2 * n *sizeof(float));
        if(poligono->vertices == NULL){
            free (poligono);
            return NULL;
        }

        (poligono->n) = n;

        for (size_t i=0; i< poligono->n; i++)
            for (size_t j=0; j< 2; j++)
                poligono->vertices[i][j]= vertices[i][j];
        return poligono;
    }
    poligono->n = n;
    poligono->vertices = NULL;
    
    return poligono;
}

void poligono_destruir(poligono_t *poligono){
	free(poligono->vertices);
	free(poligono);
}

bool poligono_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y){
	if ((pos < 0)||(pos >= poligono->n)||(poligono->vertices == NULL))
        return false;
    
    *x = (poligono->vertices [pos][0]);
    *y = (poligono->vertices [pos][1]);

    return true;
}

bool poligono_agregar_vertice(poligono_t *poligono, float x, float y){
    size_t largo = poligono->n;

    float (*aux)[2] = realloc(poligono->vertices, 2*(largo+1)*sizeof(float));
    if(aux == NULL){
        free(aux);
        return false;
    }

    poligono->vertices = aux;
    poligono->n = largo + 1;

    poligono->vertices[largo][0]=x;
    poligono->vertices[largo][1]=y;

    return true;
}

void poligono_dibujar(SDL_Renderer *renderer, poligono_t *poligono){
    SDL_RenderDrawLine(renderer, poligono->vertices[0][0], poligono->vertices[0][1], poligono->vertices[poligono->n - 1][0], poligono->vertices[poligono->n - 1][1]);
    
    for (size_t i = 1; i < poligono->n; i++)
        SDL_RenderDrawLine(renderer, poligono->vertices[i-1][0], poligono->vertices[i-1][1], poligono->vertices[i][0], poligono->vertices[i][1]);
}

void trasladar(poligono_t *poligono, float dx, float dy){
    for (int i = 0; i < poligono->n;i++){
        poligono->vertices[i][0] += dx;
        poligono->vertices[i][1] += dy;
    } 
}

void rotar(poligono_t *poligono, double rad){
    double cosn = cos(rad);
    double sen = sin(rad);
    
    for (int i = 0; i < poligono->n; i++){
        float x = poligono->vertices[i][0]*cosn - poligono->vertices[i][1]*sen;
		float y = poligono->vertices[i][0]*sen + poligono->vertices[i][1]*cosn;
        poligono->vertices[i][0] = x;
        poligono->vertices[i][1] = y;
    }   
}

void poligono_rotar_centrado(poligono_t *p, float cx, float cy, float ang){  
	trasladar(p, -cx, -cy);
	rotar(p, ang*PI/180);
	trasladar(p,cx,cy);	  
}

double distancia(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
		  
double producto_interno (double ax, double bx, double ay, double by){
    return (ax * bx)  + (ay * by);
}
		
void punto_mas_cercano(float x0, float y0, float x1, float y1, float xp, float yp, float *x, float *y) {
    float ax = xp - x0;
    float ay = yp - y0;
    float bx = x1 - x0;
    float by = y1 - y0;

    float alfa = producto_interno(ax, ay, bx, by) / producto_interno(bx, by, bx, by);

    if(alfa <= 0) {
        *x = x0;
        *y = y0;
    }
    else if(alfa >= 1) {
        *x = x1;
        *y = y1;
    }
    else {
        *x = alfa * bx + x0;
        *y = alfa * by + y0;
    }
}

void reflejar(float norm_x, float norm_y, float *cx, float *cy, float *vx, float *vy) {
    float proy = producto_interno(norm_x, norm_y, *vx, *vy);

    if(proy >= 0)
        return;

    *vx -= 2 * norm_x * proy;
    *vy -= 2 * norm_y * proy;

    // Además empujamos a la bola hacia afuera para que no se pegue
    *cx += norm_x * 0.1;
    *cy += norm_y * 0.1;
}
		  		  
double poligono_distancia(const poligono_t *p, float xp, float yp, float *nor_x, float *nor_y) {
    double d = 1 / 0.0;
    size_t idx = 0;

    for(size_t i = 0; i < p->n; i++) {
        float xi, yi;
        punto_mas_cercano(p->vertices[i][0], p->vertices[i][1], p->vertices[(i + 1) % p->n][0], p->vertices[(i + 1) % p->n][1], xp, yp, &xi, &yi);
        double di = distancia(xp, yp, xi, yi);

        if(di < d){
            d = di;
            idx = i;
        }
    }

    float nx = p->vertices[(idx + 1) % p->n][1] - p->vertices[idx][1];
    float ny = p->vertices[idx][0] - p->vertices[(idx + 1) % p->n][0];
    float dn = distancia(nx, ny, 0, 0);

    nx /= dn;
    ny /= dn;

    *nor_x = nx;
    *nor_y = ny;

    return d;
}