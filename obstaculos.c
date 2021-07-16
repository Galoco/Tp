//funciones para obstaculos
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
    trasladar(p->vertices, p->n, )//trasladarlo el largo del objeto al sentro - el largo por el sen(ang)
    //luego rotarlo ang
    // luego trasladarlo hacia abajo cos(ang)
}



//ver si necesito googlear una formula
double poligono_distancia(const poligono_t *p, float cx, float cy, float *norm_x, float *norm_y){
    //usar poligono_en_poligono  para verificar q el pto este afuera
    double *dist = malloc()//pedir memoria para la cantidad de puntos a verificar;
    for (size_t i = 0; i < p->n; i++){
        dist[i] = //usar formula de distancia, conviene hacer una funcion aparte

    }
  
    //extraer el valor menor de dist y guardarlo CREO QUE ESTO VA BIEN ASI, COMPARO CADA VALOR Y DEVUELVO EL MENOR
    double dist_menor= dist[0];
    for (size_t i=0; i< /*cantidad de puntos*/; i++){
        if (dist[i]<dist_menor){
            dist_menor= dist[i];
        }
    }   //valor guardado en double dist_menor

    //liberar el resto de valores de la memoria
    free (dist);

    *norm_x = cx-/*coordenada mas cercana x*/ ;
    *norm_y = cy - /*coordenada mas cercana y*/;
    
    return /*valor guardado*/;
}

