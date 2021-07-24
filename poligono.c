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

void poligono_rotar_centrado(poligono_t *p, float cx, float cy, float ang)//trasladar + rotar+ trasladar (Diseñarla nosotros)
{
    //trasladarlo el largo del objeto al centro - el largo por el sen(ang)
	trasladar(p, p->n, ((1-sen(ang)*cx), 0);  
    //luego rotarlo ang
	rotar (p, p->n, ang);
    // luego trasladarlo hacia abajo cos(ang)
	trasladar (p,p->n,0, (cy*cos(ang)));

/*podria hacerse con la norma?, 
double r = sqrt((pow(cx,2)) + (pow (cy,2)));
trasladar (p, p->n, r*cos(ang), r*sen(ang));
rotar (p, p->n, ang); 
*/
		  
}
double distancia(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
		  
double producto_interno (double ax, double bx, double ay, double by){
return (ax * bx)  + (ay * by);
}
		
		  
/*
Para encontrar la distancia de un punto a una recta se proyecta el punto
ortogonalmente sobre la recta.
El producto [(X.P) / (X.X)] X es la proyección del punto P sobre X.
El coeficiente entre corchetes será la proporción de P sobre X.
Como estamos trabajando con segmentos de recta, si el coeficiente es menor a
cero o mayor a uno nos caímos del segmento.
*/
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

/*
Reflejamos según P' = P - 2 D(P.D)
*/
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

        if(di < d) {
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

poligono_t *poligono_crear(float vertices[][2], size_t n){ //vamos a ponerle de nombre poligono a estas funciones parra generalizar
	poligono_t *poligono= NULL;
    poligono = malloc (sizeof (poligono_t));
    if  ((poligono== NULL)){
        return NULL;
    }
    poligono->vertices = malloc (2*n*sizeof(float));
    if(poligono-> vertices==NULL){
        free (poligono);
        return NULL;
    }
    for (size_t i=0; i< n; i++){
        for (size_t j=0; j< 2; j++){
            poligono->vertices[i][j]= vertices[i][j];
        }
    }
    (poligono->n) = n;
    return poligono;
}


	
void poligono_destruir(poligono_t *poligono){
	free(poligono->vertices);
	free(poligono);
}



bool poligono_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y);
=======
bool poligono_obtener_vertice(const poligono_t *poligono, size_t pos, float *x, float *y){
	if ((pos<0)||(pos>=(poligono->n))||(poligono->vertices==NULL)){
        return false;
    }
    else{
        *x= (poligono->vertices [pos][0]);
        *y= (poligono->vertices [pos][1]);
        return true;
    }

	
	
	
poligono_t *poligono_clonar(const poligono_t *poligono){
	if ((pos<0)||(pos>=(poligono->n))||(poligono->vertices==NULL)){
        return false;
    }
    else{
        *x= (poligono->vertices [pos][0]);
        *y= (poligono->vertices [pos][1]);
        return true;
    }
	
	
	
//Lo necesitamos?	
float product_vect(float ax, float ay, float bx, float by ){
	return ((bx-ax)*(py-ay))-((px-ax)*(by-ay));
}


