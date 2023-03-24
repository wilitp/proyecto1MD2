#include <stdlib.h>
#include <assert.h>

#include "vertice.h"
#include "../EstructuraGrafo23.h"
#include "../list/list.h"

vertice vertice_empty(u32 nombre) {
  vertice v = malloc(sizeof(struct vertice_t));

  v->vecinos = list_empty();
  v->grado = 0;
  v->nombre = nombre;

  return v;
}

u32 vertice_nombre(vertice v){
  assert(v != NULL);
  return v->nombre;
}

u32 vertice_grado(vertice v) {
  assert(v != NULL);
  return v->grado;
}

vertice vertice_set_grado(vertice v, u32 grado) {
  assert(v != NULL);
  v->grado = grado;
  return v;
}

vertice vertice_add_vecino(vertice v, u32 vecino) {
  assert(v != NULL);
  u32 *vecino_en_lista = malloc(sizeof(u32));
  v->vecinos = list_push(v->vecinos, vecino_en_lista);
  
  return v;
}

vertice vertice_destroy(vertice v) {
  // TODO: destruir cada vecino de la lista o cambiar la lista para que reciba una funcion destructora para cada vecino
  list_destroy(v->vecinos);
  free(v);
  return NULL;
}
