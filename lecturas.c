#include <lecturas.h>

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

    if(fread(parametros, sizeof(int16_t), 3, f) != 3 ) return NULL;

    poligono_t *p = poligono_crear();
    if(p == NULL) return NULL; // Crear en el origen
    poligono_rotar(p, rotacion);
    poligono_trasladar(p, cx, cy); // Del EJ2
    // Del EJ2
    return p;

    //printf("CIRCULO: x: %u, y: %u, radio: %u \n", parametros[0], parametros[1], parametros[2] );
    
}

poligono_t *leer_geometria_rectangulo(FILE *f){
    if(f == NULL) return false;

    int16_t parametros[5];

    if(fread(parametros, sizeof(int16_t), 5, f) != 5) return NULL;

    poligono_t *p = poligono_crear(...);
    if(p == NULL) return NULL; // Crear en el origen
    poligono_rotar(p, rotacion);
    poligono_trasladar(p, cx, cy); // Del EJ2
    // Del EJ2 
    return p;

    //printf("RECTANGULO: x = %u, y = %u, ancho = %u, alto = %u, angulo = %u\n",parametros[0], parametros[1], parametros[2], parametros[3], parametros[4]);
    
}

poligono_t *leer_geometria_poligono(FILE *f){
    if(f == NULL) return false;

    int16_t n_ptos;
    if(fread(&n_ptos, sizeof(int16_t), 1, f) != 1) return NULL;

    //printf("puntos = %u\n", n_ptos);

    for (size_t i = 1; i < n_ptos*2; i += 2){
        int16_t parametros[2];
        
        if(fread(parametros, sizeof(int16_t), 2, f) != 2) 
            return NULL;

        //printf(" x%zd = %u, y%zd = %u \n", i, parametros[0], i, parametros[1]);
    }
    poligono_t *p = poligono_crear(...);
    if(p == NULL) return NULL; // Crear en el origen
    poligono_rotar(p, rotacion);
    poligono_trasladar(p, cx, cy); // Del EJ2
    // Del EJ2
    return p;
    
}

poligono_t *leer_geometria(FILE*f, geometria_t geometria){// cambiar parametros de salida de las funciones ej 4
    if(f == NULL) return false;

    return geo[geometria](f);
}

