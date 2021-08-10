#include <SDL2/SDL.h>
#include <assert.h>

#include "lecturas.h"
#include "config.h"
#include "obstaculos.h"
#include "fisica.h"
#include "lista.h"

#define MAX_NIVELES 6

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

//Crea e inicializa todos los obstaculos para cada nivel leido de f agregandolos a la lista_t lista, 7
//devolviendo la cantidad de obstaculos naranjas en cada nivel
int inicializacion_obst(FILE *f, lista_t *lista);

//funcion que hace que se efectuen los rebotes entre los objetos y la pelotita
void rebote(obstaculo_t *o, float *x, float *y, float *vx, float *vy);

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

    // BEGIN cÃ³digo del alumno 1

    if(argc != 2) {
        fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
        return 1;
    }
    //ACA TIENE QUE IR LA FUNCION PARA LEER EL ARCHIVO
    FILE* f = fopen (argv[1], "rb");
    if (f==NULL){
        fprintf(stderr, "No se pudo abrir el archivo %s \n",  argv[1]);
        return 1;
    }
  
    size_t nivel= 0;
    while (nivel< MAX_NIVELES){
        float canon_angulo = 0; 
        bool cayendo = false;   

        float cx, cy, vx, vy;
        cx = cy = vx = vy = 0;

        
        lista_t *lObstaculos = lista_crear();
        if(lObstaculos == NULL){
            fputs("Error de asignacion de memoria.\n", stderr);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
        
            fclose(f);
            SDL_Quit();
            return 1;
        }
        int naranjas = inicializacion_obst(f, lObstaculos);
        if(naranjas == -1){
            fputs("Error de asignacion de memoria.\n", stderr);

            lista_destruir(lObstaculos, free);

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
        
            fclose(f);
            SDL_Quit();
            return 1;
        }
        
        // END cÃ³digo del alumno
        unsigned int ticks = SDL_GetTicks();

        while(1) {
            if(naranjas == 0){
                break;
            }
            if(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)
                    break;

                // BEGIN cÃ³digo del alumno 2
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


            // BEGIN cÃ³digo del alumno 3
#ifdef TTF
            escribir_texto(renderer, font, "Peggle", 100, 20);
#endif

            if(naranjas != 0){
                lista_iterador_t *iterador = lista_iterador_crear(lObstaculos); 

                while (!lista_iterador_termino(iterador)){
                    obstaculo_t *obstaculo = lista_iterador_actual(iterador);
                    
                    obstaculo_movimiento(obstaculo);
                    rebote(obstaculo, &cx, &cy, &vx, &vy);
                    obstaculo_dibujar (renderer, obstaculo);
                    
                    lista_iterador_siguiente(iterador);
                }

                lista_iterador_destruir(iterador);

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

                // Rebote contra las paredes:
                if(cx < MIN_X + BOLA_RADIO || cx > MAX_X - BOLA_RADIO) vx = - vx;
                if(cy < MIN_Y + BOLA_RADIO) vy = -vy;

                //si se traba la bola
                if (se_trabo(vx)){
                    cayendo = false;
                    lista_iterador_t *iter = lista_iterador_crear(lObstaculos);

                    while(!lista_iterador_termino(iter)) {
                        obstaculo_t *o = lista_iterador_actual(iter);

                        if(o->color == NARANJA && o->eliminado){
                            naranjas -= 1;
                        } 
                        if(o->eliminado && o->color != GRIS) {
                            destruir_obstaculo(o);
                            lista_iterador_eliminar(iter);
                        }

                        lista_iterador_siguiente(iter);
                    }
                    lista_iterador_destruir(iter);
                }

                // Se saliÃ³ de la pantalla:
                if(cy > MAX_Y - BOLA_RADIO){
                    cayendo = false;
                    lista_iterador_t *iter = lista_iterador_crear(lObstaculos);

                    while(!lista_iterador_termino(iter)) {
                        obstaculo_t *o = lista_iterador_actual(iter);
                        
                        if(o->color == NARANJA && o->eliminado){
                            naranjas -= 1;
                        } 
                        if(o->eliminado && o->color != GRIS) {
                            destruir_obstaculo(o);
                            lista_iterador_eliminar(iter);
                        }
                        
                        else
                            lista_iterador_siguiente(iter);
                    }
                    lista_iterador_destruir(iter);    
                }
                // Dibujamos el caÃ±Ã³n:
                SDL_SetRenderDrawColor(renderer, 0x00, 0xaa, 0xe4, 0x00);
                SDL_RenderDrawLine(renderer, CANON_X, CANON_Y, CANON_X + sin(canon_angulo) * CANON_LARGO, CANON_Y + cos(canon_angulo) * CANON_LARGO);

                // Dibujamos la bola
                pelotita_t *pelotita = pelotita_crear (cx, cy, BOLA_RADIO);
                graficar_pelotita (renderer, pelotita);
                pelotita_destruir (pelotita);

                // Dibujamos las paredes:
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
                SDL_RenderDrawLine(renderer, MIN_X, MIN_Y, MAX_X, MIN_Y);
                SDL_RenderDrawLine(renderer, MIN_X, MAX_Y, MAX_X, MAX_Y);
                SDL_RenderDrawLine(renderer, MIN_X, MAX_Y, MIN_X, MIN_Y);
                SDL_RenderDrawLine(renderer, MAX_X, MAX_Y, MAX_X, MIN_Y);

                // Dibujamos el vector de velocidad:
                SDL_RenderDrawLine(renderer, cx, cy, cx + vx, cy + vy);

            }//end if de naranjas != 0
            
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

        }//While juego

        // BEGIN cÃ³digo del alumno 4
        // frees
        lista_iterador_t *iter = lista_iterador_crear(lObstaculos);

        while(!lista_iterador_termino(iter)){
            obstaculo_t *o = lista_iterador_actual(iter);

            destruir_obstaculo(o);
            lista_iterador_eliminar(iter);  
        }
        lista_iterador_destruir(iter);

        lista_destruir(lObstaculos, free);

        nivel++;
    }//While de cada nivel
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
   
    fclose(f);
    // END cÃ³digo del alumno
#ifdef TTF
    TTF_CloseFont(font);
    TTF_Quit();
#endif
    SDL_Quit();
    return 0;
}

int inicializacion_obst(FILE *f, lista_t *lista){
    int naranjas = 0;
    int16_t cantidad_de_obstaculos = 0;
    if(!fread(&cantidad_de_obstaculos, sizeof(int16_t), 1, f)) fprintf(stderr, "Error de lectura");
            
    for(size_t n = 0; n < cantidad_de_obstaculos; n++) {
        obstaculo_t *obstaculo = obstaculo_crear(f);
        if(obstaculo == NULL) return -1;
        
        if(obstaculo->color == NARANJA) naranjas++;

        lista_insertar_primero(lista, obstaculo);
    }

    return naranjas;
}

void rebote(obstaculo_t *o, float *x, float *y, float *vx, float *vy){
    float norm_x = 0;
    float norm_y = 0;
    if(poligono_distancia(o->poligono, *x, *y, &norm_x, &norm_y) < BOLA_RADIO){
        if(o->color != GRIS)
            o->eliminado = true;

        *vy *= PLASTICIDAD;
        *vx *= PLASTICIDAD;

        reflejar(norm_x, norm_y, x, y, vx, vy);   
    } 
}