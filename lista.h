#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdbool.h>
#include <stdlib.h>

struct lista;
struct lista_iterador;

typedef struct lista lista_t;
typedef struct lista_iterador lista_iterador_t;
// Crea una lista
lista_t *lista_crear();
// Verifica si la lista es vacía
bool lista_esta_vacia(const lista_t *l);
// Agrega un elemento al principio de la lista
bool lista_insertar_primero(lista_t *l, void *d);
// Agrega un elemento al final de la lista
bool lista_insertar_ultimo(lista_t *l, void *d);
// Borra el primer elemento de la lista. En caso de lista vacía devuelve NULL.
void *lista_borrar_primero(lista_t *l);
// Devuelve el contenido de dato del primer nodo, en caso de lista vacía devuelve NULL.
void *lista_ver_primero(const lista_t *l);
// Obtener largo
size_t lista_largo(const lista_t *l);
// Destruye la lista
void lista_destruir(lista_t *l, void (*destruir_dato)(void *d));

// Obtiene un iterador de la lista
lista_iterador_t *lista_iterador_crear(lista_t *l);
// Avanza una posición en la lista. Devuelve false si ya está al final de la lista
bool lista_iterador_siguiente(lista_iterador_t *li);
// Almacena en dato el valor que se encuentra en la posición actual. Devuelve false si está al final de la lista
void *lista_iterador_actual(const lista_iterador_t *li);
// Verifica si ya está al final de la lista
bool lista_iterador_termino(const lista_iterador_t *li);
// Destruye el iterador de la lista
void lista_iterador_destruir(lista_iterador_t *li);
// Agrega un elemento en la posición actual
bool lista_iterador_insertar(lista_iterador_t *li, void *dato);
// Elimina el elemento de la posición actual. Devuelve NULL si el iterador está al final de la lista
void *lista_iterador_eliminar(lista_iterador_t *li);
// Iterador interno de la lista.
// Recorre la lista y para cada elemento de la misma llama a 
// la función visitar, pasándole por parámetro el elemento de la lista
// (dato) y el parámetro extra.
// El parámetro extra sirve para que la función visitar pueda recibir
// información adicional. Puede ser NULL.
// La función visitar debe devolver true si se debe seguir iterando,
// false para cortar la iteración. No puede agregar ni quitar elementos
// a la lista).
void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra);


#endif // _LISTA_H_