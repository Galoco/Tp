#include "lista.h"
//ACA ESTA TODO OK!!
struct lista {
	struct nodo *prim;
};

struct lista_iterador {
	lista_t *l;
	struct nodo *actual;
	struct nodo *anterior;
};

typedef struct nodo {
	struct nodo *sig;
	void *dato;
} nodo_t;

static nodo_t *nodo_crear(void *d)
{
	nodo_t *nuevo = malloc(sizeof(nodo_t));
	if(nuevo == NULL)
		return NULL;

	nuevo->sig = NULL;
	nuevo->dato = d;

	return nuevo;
}

lista_t *lista_crear()
{
	lista_t *l = malloc(sizeof(lista_t));
	if(l == NULL)
		return NULL;

	l->prim = NULL;
	return l;
}

bool lista_esta_vacia(const lista_t *l)
{
	return l->prim == NULL;
}

bool lista_insertar_primero(lista_t *l, void *d)
{
	nodo_t *nuevo = nodo_crear(d);
	if(nuevo == NULL)
		return false;

	nuevo->sig = l->prim;
	l->prim = nuevo;

	return true;
}

bool lista_insertar_ultimo(lista_t *l, void *d)
{
	nodo_t *nuevo = nodo_crear(d);
	if(nuevo == NULL)
		return false;
	nuevo->sig = NULL;

	// Si está vacía inserto al principio:
	if(l->prim == NULL) {
		l->prim = nuevo;
		return true;
	}

	// La lista no estaba vacía:
	nodo_t *actual = l->prim;
	while(actual->sig != NULL)
		actual = actual->sig;

	actual->sig = nuevo;

	return true;
}

void *lista_borrar_primero(lista_t *l){
	if(lista_esta_vacia(l))
		return NULL;

	void *dato = l->prim->dato;

    struct nodo *aux = l->prim;
    l->prim = l->prim->sig;

    free(aux);

    return dato;
}

void *lista_ver_primero(const lista_t *l){
	if(lista_esta_vacia(l))
		return NULL;

	nodo_t *actual = l->prim;

	return actual->dato;
}

size_t lista_largo(const lista_t *l){
	if(lista_esta_vacia(l))
		return 0;

	nodo_t * actual = l->prim;
	size_t largo = 1;
	while(actual->sig->sig != NULL){
		actual = actual->sig;
		largo++;
	}
	return largo;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *d))
{
	if(l == NULL)
		return;

	nodo_t *actual = l->prim;
	while(actual != NULL)
	{
		nodo_t *proximo = actual->sig;

		if(destruir_dato != NULL)
			destruir_dato(actual->dato);

		free(actual);

		actual = proximo;
	}

	free(l);
}

lista_iterador_t *lista_iterador_crear(lista_t *l)
{
	lista_iterador_t *li = malloc(sizeof(lista_iterador_t));
	if(li == NULL)
		return NULL;

	li->l = l;
	li->actual = l->prim;
	li->anterior = NULL;

	return li;
}

bool lista_iterador_siguiente(lista_iterador_t *li)
{
	if(li->actual == NULL)
		return false;

	li->anterior = li->actual;
	li->actual = li->actual->sig;

	return true;
}

void *lista_iterador_actual(const lista_iterador_t *li)
{
	if(li->actual == NULL)
		return NULL;

	return li->actual->dato;
}

bool lista_iterador_termino(const lista_iterador_t *li)
{
	return li->actual == NULL;
}

void lista_iterador_destruir(lista_iterador_t *li)
{
	free(li);
}

bool lista_iterador_insertar(lista_iterador_t *li, void *dato)
{
	if(lista_esta_vacia(li->l)) {
		lista_insertar_primero(li->l, dato);
		return true;
	}

	if(li->actual == NULL)
		return false;

	nodo_t *nuevo = nodo_crear(dato);
	if(nuevo == NULL)
		return false;

	nodo_t *proximo = li->actual->sig;
	li->actual->sig = nuevo;
	nuevo->sig = proximo;

	return true;
}

void *lista_iterador_eliminar(lista_iterador_t *li)
{
	if(li->actual == NULL)
		return NULL;

	if(li->anterior == NULL) {
		li->actual = li->actual->sig;
		return lista_borrar_primero(li->l);
	}

	void *d = li->actual->dato;

	li->anterior->sig = li->actual->sig;
	struct nodo *proximo = li->actual->sig;
	free(li->actual);
	li->actual = proximo;

	return d;
}

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra)
{
	nodo_t *actual = l->prim;
	while(actual != NULL)
	{
		if(!visitar(actual->dato, extra))
			return;
		actual = actual->sig;
	}
}