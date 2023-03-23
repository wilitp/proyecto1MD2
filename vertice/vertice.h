#ifndef vertice_H
#define vertice_H

#include "../EstructuraGrafo23.h"
#include "../list/list.h"

struct vertice_t{
  u32 nombre; 
  u32 grado; 
  list vecinos; 
} ;

typedef struct vertice_t* vertice;

vertice vertice_empty(u32 nombre);

u32 vertice_grado(vertice v);

u32 vertice_nombre(vertice v);

vertice vertice_set_grado(vertice v, u32 grado);

vertice vertice_add_vecino(vertice v, u32 vecino);

vertice vertice_destroy(vertice v);

#endif




