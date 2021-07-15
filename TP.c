#include <.h>

//ver si necesito googlear una formula
double poligono_distancia(const poligono_t *p, float cx, float cy, float *norm_x, float *norm_y){


}

//ver si necesito googlear una formula
void reflejar(float norm_x, float norm_y, float *cx, float *cy, float *vx, float *vy){

}

//trasladar + rotar
poligono_rotar_centrado(p, cx, cy, ang){

}

// la pantalla arranca arriba iz con x e y crecientes hacia derecha y arriba
void angulos_cambiados(){


}

// cambiar parametros de salida de las funciones ej 4
leer_geometria()

computacion_de_ptos(){


}

//verificar siempre velocidad pelota

//cuando golpeo un objeto eliminable
eliminar_obstaculo(){


}
// arranca de nuevo con los objetos ya eliminados

reiniciar_juego(){
  
}
//

#ifdef TTF
#include <SDL2/SDL_ttf.h>

void escribir_texto(SDL_Renderer *renderer, TTF_Font *font, const char *s, int x, int y) {
    SDL_Color color = {255, 255, 255};  // EstarÃ­a bueno si la funciÃ³n recibe un enumerativo con el color, Â¿no?
    SDL_Surface *surface = TTF_RenderText_Solid(font, s, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
#endif


// PARTE DE SDL2 QUE USO SANTISI

//ESTE MAIN DEBERIA IR EN EL main.c
int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

#ifdef TTF
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("FreeSansBold.ttf", 24);
#endif

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Peggle");

    int dormir = 0;

    // BEGIN cÃ³digo del alumno
    float canon_angulo = 0; // Ãngulo del caÃ±Ã³n
    bool cayendo = false;   // Â¿Hay bola disparada?

    float cx, cy;   // Centro de la bola
    float vx, vy;   // Velocidad de la bola
    // END cÃ³digo del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;

            // BEGIN cÃ³digo del alumno
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(! cayendo)
                    cayendo = true;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                canon_angulo = atan2(event.motion.x - CANON_X, event.motion.y - CANON_Y);
                if(canon_angulo > CANON_MAX)
                    canon_angulo = CANON_MAX;
                if(canon_angulo < -CANON_MAX)
                    canon_angulo = -CANON_MAX;
            }
            // END cÃ³digo del alumno

            continue;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


        // BEGIN cÃ³digo del alumno
#ifdef TTF
        escribir_texto(renderer, font, "Peggle", 100, 20);
#endif

        if(cayendo) {
            // Si la bola estÃ¡ cayendo actualizamos su posiciÃ³n
            vy = computar_velocidad(vy, G, DT);
            vx *= ROZAMIENTO;
            vy *= ROZAMIENTO;
            cx = computar_posicion(cx, vx, DT);
            cy = computar_posicion(cy, vy, DT);
        }
        else {
            // Si la bola no se disparÃ³ establecemos condiciones iniciales
            cx = CANON_X + CANON_LARGO * sin(canon_angulo);
            cy = CANON_Y + CANON_LARGO * cos(canon_angulo);
            vx = BOLA_VI * sin(canon_angulo);
            vy = BOLA_VI * cos(canon_angulo);
        }

        // Rebote contra las paredes://PENSAR EN EL REBOTE CONTRA LOS OBJETOS A PARTIR DE ESTO
        if(cx < MIN_X + BOLA_RADIO || cx > MAX_X - BOLA_RADIO) vx = - vx;
        if(cy < MIN_Y + BOLA_RADIO) vy = -vy;

        // Se saliÃ³ de la pantalla:
        if(cy > MAX_Y - BOLA_RADIO)
            cayendo = false;


        // Dibujamos el caÃ±Ã³n:
        SDL_RenderDrawLine(renderer, CANON_X, CANON_Y, CANON_X + sin(canon_angulo) * CANON_LARGO, CANON_Y + cos(canon_angulo) * CANON_LARGO);

        // Dibujamos la bola://ESTA BOLA ES CUADRAD LA NUESTRA TIENE Q SER CIRCULAR
        SDL_RenderDrawLine(renderer, cx - BOLA_RADIO, cy, cx, cy + BOLA_RADIO);
        SDL_RenderDrawLine(renderer, cx, cy + BOLA_RADIO, cx + BOLA_RADIO, cy);
        SDL_RenderDrawLine(renderer, cx + BOLA_RADIO, cy, cx, cy - BOLA_RADIO);
        SDL_RenderDrawLine(renderer, cx, cy - BOLA_RADIO, cx - BOLA_RADIO, cy);

        // Dibujamos las paredes:
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        SDL_RenderDrawLine(renderer, MIN_X, MIN_Y, MAX_X, MIN_Y);
        SDL_RenderDrawLine(renderer, MIN_X, MAX_Y, MAX_X, MAX_Y);
        SDL_RenderDrawLine(renderer, MIN_X, MAX_Y, MIN_X, MIN_Y);
        SDL_RenderDrawLine(renderer, MAX_X, MAX_Y, MAX_X, MIN_Y);

        // Dibujamos el vector de velocidad:
        SDL_RenderDrawLine(renderer, cx, cy, cx + vx, cy + vy);
        // END cÃ³digo del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    // BEGIN cÃ³digo del alumno
    // END cÃ³digo del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

#ifdef TTF
    TTF_CloseFont(font);
    TTF_Quit();
#endif
    SDL_Quit();
    return 0;
}

//funciones para la pelotita
double computar_velocidad (double vi, double a, double dt, double rozamiento){
    return  (dt * a + vi)/rozamiento;//ESTA BIEN ESTO??
}

double computar_posicion (double pi, double vi, double dt){
    return  dt * vi + pi;
}

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
    //extraer el valor menor de dist y guardarlo
    //liberar el resto de valores de la memoria
    *norm_x = cx-/*coordenada mas cercana x*/ ;
    *norm_y = cy - /*coordenada mas cercana y*/;
    
    return /*valor guardado*/;
}

