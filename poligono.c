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
	
	
	
	
float product_vect(float ax, float ay, float bx, float by ){
	return ((bx-ax)*(py-ay))-((px-ax)*(by-ay));
}

	
	
bool punto_en_triangulo(float px, float py, float ax, float ay, float bx, float by, float cx, float cy){
	float p_vec_ab = ((bx-ax)*(py-ay))-((px-ax)*(by-ay));
	float p_vec_bc = ((cx-bx)*(py-by))-((px-bx)*(cy-by));
	float p_vec_ca = ((ax-cx)*(py-cy))-((px-cx)*(ay-cy));
	return (((p_vec_ab)>=0 && (p_vec_bc)>=0 && (p_vec_ca)>=0))||((p_vec_ab)<=0 && (p_vec_bc)<=0 && ((p_vec_ca)<=0));	
}

	

bool punto_en_poligono(float poligono[][2], size_t n, float px, float py){
	int i;
	for (i=1; i< (n - 1); i++) {
		if (punto_en_triangulo(px, py, pol[0][0], pol[0][1], pol[i][0], pol[i][1], pol[i+1][0], pol[i+1][1])){
			return true;
		}
	}
	return false;
}


