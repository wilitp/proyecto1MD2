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
  v->vecinos = list_push(v->vecinos, vecino);
  
  return v;
}

vertice vertice_destroy(vertice v) {
  list_destroy(v->vecinos);
  free(v);
  return NULL;
}
