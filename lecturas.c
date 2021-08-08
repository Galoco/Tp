#include <math.h>
#include <assert.h>

#include "lecturas.h"
#include "config.h"

//ACA PARECE ESTAR TODO BIEN
t_mov_t mov[] = { 
    [MOV_INMOVIL] = leer_movimiento_inmovil, 
    [MOV_CIRCULAR] = leer_movimiento_circular, 
    [MOV_HORIZONTAL] = leer_movimiento_horizontal 
    };

t_geo_t geo[] = {
    [GEO_CIRCULO] = leer_geometria_circulo,
    [GEO_RECTANGULO] = leer_geometria_rectangulo,
    [GEO_POLIGONO] = leer_geometria_poligono
    };


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
    return (fread(parametros, sizeof(int16_t), 3, f) == 3);
}

bool leer_movimiento(FILE *f, movimiento_t movimiento, int16_t parametros[], size_t *n_parametros){
    if(f == NULL) return false;

    return mov[movimiento](f, parametros, n_parametros);
}

poligono_t *leer_geometria_circulo(FILE *f){
    if(f == NULL) return false;
    //lo hice dinamico.
    int16_t *parametros = malloc(sizeof(int16_t));
    if(parametros == NULL) return NULL;

    if(fread(parametros, sizeof(int16_t), 3, f) != 3 ) return NULL;//x, y y radio
    
    poligono_t *p = poligono_crear(NULL, 0); 

    for (double ang = 0; ang < 2*PI; ang += (PI/10)){
        float x = parametros[2] * cos(ang);
        float y = parametros[2] * sin(ang);
        
        assert(poligono_agregar_vertice(p, x, y));
    }
        
    trasladar(p, parametros[0], parametros[1]);

    free(parametros);

    return p;
}

poligono_t *leer_geometria_rectangulo(FILE *f){
    if(f == NULL) return false;

    int16_t *parametros = malloc(sizeof(int16_t));
    if(parametros == NULL) return NULL;

    if(fread(parametros, sizeof(int16_t), 5, f) != 5) return NULL;// x, y, ancho, alto, angulo
    
    poligono_t *p = poligono_crear(NULL, 0);
    
    assert(poligono_agregar_vertice (p, ((float)parametros[2]/2), ((float)parametros[3]/2)));
    assert(poligono_agregar_vertice (p, -((float)parametros[2]/2), (float)parametros[3]/2));
    assert(poligono_agregar_vertice (p, -((float)parametros[2]/2), -(float)parametros[3]/2));
    assert(poligono_agregar_vertice (p, ((float)parametros[2]/2), -((float)parametros[3]/2)));
        
        
    rotar(p, parametros[4]*PI/180);
    trasladar(p,parametros[0], parametros[1]);

    free(parametros);
    
    return p;  
}

poligono_t *leer_geometria_poligono(FILE *f){
    if(f == NULL) return false;

    int16_t n_ptos;
    if(fread(&n_ptos, sizeof(int16_t), 1, f) != 1) return NULL;

    poligono_t *p = poligono_crear( NULL, 0);

    for (size_t i = 1; i < n_ptos*2; i += 2){
        int16_t *parametros = malloc(2*sizeof(int16_t));
        if(parametros == NULL) return NULL;
        
        if(fread(parametros, sizeof(int16_t), 2, f) != 2) 
            return NULL;

        assert(poligono_agregar_vertice(p, (float)parametros[0], (float)parametros[1]));
        free(parametros);
    }
    return p;
}

poligono_t *leer_geometria(FILE*f, geometria_t geometria){
    if(f == NULL) return false;

    return geo[geometria](f);
}