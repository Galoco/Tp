#include <SDL2/SDL.h>

#include "lecturas.h"
#include "config.h"
#include "obstaculos.h"
#include "pelotita.h"
#include "fisica.h"

#define DT (1.0 / JUEGO_FPS)


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
/*Inicializar el graficador y ver si funciona,
inicializar la pelotita y ver si funciona
inicializar los obstaculos como una lista de obstaculos y ver si funciona*/
/*Inicializar las variables del juego
como: si quedan obstaculos, tiempo de espera para crear otra pelotita, 
el puntaje, el mejor puntaje etc.*/  
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
            /*Aca nos fijamos que hace cada movimiento del mouse, es decir 
            que hace nuestra pelotita cuando hacemos diferntes cosas con el mouse
            */
           /*Luego de eso veo de reinciciar el juego con menos objetos que antes,
           es decir veo los objetos que fueron eliminados y los elimino
           Igualmente creo que esta bastante completo esto ya, habria que ver lo del reincio
           del juego nomas*/
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
/*Esto seria como se ejecuta el juego, es decir que pasa mientras estoy jugando
Tengo que crear un iterador de objetos (de la lista) dibujar cada uno y ver si hay un impacto
con la pelotita 
Despues de eso destruimos el iterador de la lista
Luego chequeamos si quedan objetos por destuir--- si no quedan se pasa al siguiente nivel sino
se sigue el mismo*/
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
    /*Aca hay que liberar toda la mamoria que se haya usado, hacer una funcion para eso*/
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

/*Ver si hay que implementar funciones en el main, casi seguro que si porq hay cosas que no se
pueden hacer sino */

void reflejar(float norm_x, float norm_y, float *cx, float *cy, float *vx, float *vy){//ver si necesito googlear una formula
    
}