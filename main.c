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

void inicializacion_obst(FILE *f, lista_t *lista);
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

/*Inicializar el graficador y ver si funciona,
inicializar la pelotita y ver si funciona
pelotita_crear(float x, float y, float angulo)
inicializar los obstaculos como una lista de obstaculos y ver si funciona*/
/*Inicializar las variables del juego
como: si quedan obstaculos, tiempo de espera para crear otra pelotita, 
el puntaje, el mejor puntaje etc.*/  
    
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
  
    //fijarme en config si hay un MAX niveles
    for (size_t nivel= 0; nivel< MAX_NIVELES; nivel++){
        float canon_angulo = 0; // Ãngulo del caÃ±Ã³n
        bool cayendo = false;   // Â¿Hay bola disparada?

        float cx, cy;   // Centro de la bola
        float vx, vy;   // Velocidad de la bola

        //creo lista y la defino
        lista_t *lObstaculos = lista_crear();
        inicializacion_obst(f, lObstaculos);
        
// END cÃ³digo del alumno
        unsigned int ticks = SDL_GetTicks();

        while(1) {
            if(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)
                    break;

                // BEGIN cÃ³digo del alumno 2
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


            // BEGIN cÃ³digo del alumno 3
#ifdef TTF
            escribir_texto(renderer, font, "Peggle", 100, 20);
#endif

            /*Esto seria como se ejecuta el juego, es decir que pasa mientras estoy jugando
            Tengo que crear un iterador de objetos (de la lista) dibujar cada uno y ver si hay un impacto
            con la pelotita 
            Despues de eso destruimos el iterador de la lista
            Luego chequeamos si quedan objetos por destuir--- si no quedan se pasa al siguiente nivel sino
            se sigue el mismo*/

            //iterador para los obstaculos
            lista_iterador_t *iterador = lista_iterador_crear(lObstaculos); 

            while (!lista_iterador_termino(iterador)){
                obstaculo_t *obstaculo = lista_iterador_actual(iterador);
                obstaculo_movimiento(obstaculo);
                //printf ("ok_movimientoO\n");
                rebote(obstaculo, &cx, &cy, &vx, &vy);
                //printf ("okrebote %d\n", j);
                obstaculo_dibujar (renderer, obstaculo);
                //printf ("ok_dibujado %d\n", j);
                lista_iterador_siguiente(iterador);
                
                
            }

            lista_iterador_destruir(iterador);
            //printf ("ok_destruccion_iterador\n");


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
                //cayendo = false;
                //Esto esta copiado de mis amigos, hay que ver si se puede hacer de otra forma
                lista_iterador_t *iter = lista_iterador_crear(lObstaculos);

                while(lista_iterador_termino(iter) != true) {
                    obstaculo_t *o = lista_iterador_actual(iter);

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

                while(lista_iterador_termino(iter) != true) {
                    obstaculo_t *o = lista_iterador_actual(iter);

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
            pelotita_t *pelotita = pelotita_crear (cx, cy, canon_angulo, BOLA_RADIO);
            graficar_pelotita (renderer, pelotita);
            pelotita_destruir (pelotita);
            //esto porq se hace asi? estamos creando una bola y a las dos lineas la liberamos??
            
            

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

        // BEGIN cÃ³digo del alumno 4
        // free lista, destruir todo, imprimir puntaje y fclose
        //lista_destruir(lObstaculos, free);
    }//For de cada nivel
    
    SDL_DestroyRenderer(renderer);/*//Aca hay que liberar toda la mamoria que se haya usado, hacer una funcion para eso*/
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

/*Ver si hay que implementar funciones en el main, casi seguro que si porq hay cosas que no se
pueden hacer sino */

void inicializacion_obst(FILE *f, lista_t *lista){
            int16_t cantidad_de_obstaculos;
            if(!fread(&cantidad_de_obstaculos, sizeof(int16_t), 1, f)) return;
            
            printf("Nivel , Cantidad de obstaculos: %u\n", cantidad_de_obstaculos);
            
            //este for crea cada obstaculo
            for(size_t n = 0; n < cantidad_de_obstaculos; n++) {
                obstaculo_t *obstaculo = obstaculo_crear(f);
                lista_insertar_primero(lista, obstaculo);
            }
        
}

void rebote(obstaculo_t *o, float *x, float *y, float *vx, float *vy){
    // float *norm_x = malloc(sizeof(float));
    // if  ((norm_x == NULL)) fprintf(stderr, "Fallo el pedido de memoria");

    // float *norm_y = malloc(sizeof(float));
    // if  ((norm_y == NULL)) fprintf(stderr, "Fallo el pedido de memoria");
    float norm_x, norm_y;
    if(poligono_distancia(o->poligono, *x, *y, &norm_x, &norm_y) < BOLA_RADIO){
            //printf ("ok_entra en el if\n");
        if(o->color != GRIS)
            o->eliminado = true;
                    
        reflejar(norm_x, norm_y, x, y, vx, vy);
        *vy *= PLASTICIDAD;
        *vx *= PLASTICIDAD; 
    }

    // free(norm_x);
    // free(norm_y);
}