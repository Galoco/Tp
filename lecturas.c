#include <math.h>

#include "lecturas.h"
#include "poligono.h"
#include "config.h"


bool leer_encabezado(FILE *f, color_t *color, movimiento_t *movimiento, geometria_t *geometria){
    if(f == NULL) return false;
    
    uint8_t enc;
    
    if (fread(&enc, sizeof(char), 1, f) != 1)
        return false;
    
    *color = (enc & MASK_COLOR) >> SHIFT_COLOR;
    *movimiento = (enc & MASK_MOVIMIENTO) >> SHIFT_MOVIMIENTO;
    *geometria = (enc & MASK_GEOMETRIA) >> SHIFT_GEOMETRIA;

    if( *movimiento > 2 || *geometria > 2) return false;
    
    return true;
}

bool leer_movimiento_inmovil(FILE *f, int16_t parametros[], size_t *n_parametros){
    if(f == NULL) return false;

    *n_parametros = 0;
    return true;
}

bool leer_movimiento_circular(FILE *f, int16_t parametros[], size_t *n_parametros){
    if(f == NULL) return false;

    *n_parametros = 3;//cx, cy y velocidad
    return (fread(parametros, sizeof(int16_t), 3, f) == 3);
}

bool leer_movimiento_horizontal(FILE *f, int16_t parametros[], size_t *n_parametros){
    if(f == NULL) return false;

    *n_parametros = 3;//x1, xi y velocidad
    return (fread(parametros, sizeof(int16_t), 4, f) == 4);
}

bool leer_movimiento(FILE *f, movimiento_t movimiento, int16_t parametros[], size_t *n_parametros){
    if(f == NULL) return false;

    return mov[movimiento](f, parametros, n_parametros);
}

poligono_t *leer_geometria_circulo(FILE *f){
    if(f == NULL) return false;

    int16_t parametros[3];

    if(fread(parametros, sizeof(int16_t), 3, f) != 3 ) return NULL;//x, y y radio
    
    poligono_t *p = poligono_crear( NULL, 0);
    if(p == NULL) return NULL; 

    float ang = 0;
    for (size_t i = 0; i < 20; i++){
        float x = (parametros[0] + parametros[2])*cos (ang);
        float y = (parametros[1] + parametros[2])*sen (ang);

        poligono_agregar_vertice (p, x, y);
        ang += 18*PI/180;

        p->n= (p->n) + 1;
    } 
        
    poligono_trasladar(p, parametros[0], parametros[1]); 
    
    return p;
}

poligono_t *leer_geometria_rectangulo(FILE *f){
    if(f == NULL) return false;

    int16_t parametros[5];

    if(fread(parametros, sizeof(int16_t), 5, f) != 5) return NULL;// x, y, ancho, alto, angulo
    
    poligono_t *p = poligono_crear( NULL, 0);
    if(p == NULL) return NULL; 
     
    
    poligono_agregar_vertice (p, (parametros[2]/2), parametros[3]/2);
    poligono_agregar_vertice (p, -(parametros[2]/2), parametros[3]/2);
    poligono_agregar_vertice (p, -(parametros[2]/2), -parametros[3]/2);
    poligono_agregar_vertice (p, (parametros[2]/2), -parametros[3]/2);
        
    poligono_rotar(p, parametros[4]);
    poligono_trasladar(p, parametros[0], parametros[1]); 
    
    return p;  
}


poligono_t *leer_geometria(FILE*f, geometria_t geometria){// cambiar parametros de salida de las funciones ej 4
    if(f == NULL) return false;

    return geo[geometria](f);
}

