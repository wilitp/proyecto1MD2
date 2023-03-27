#include <stdio.h>
#include <stdlib.h>

#include "EstructuraGrafo23.h"
#include "apig23.h"
#include "vertice/vertice.h"

#define MAX_LINE_LENGTH 1024

Grafo ConstruirGrafo() {

  // Grafo g = malloc(sizeof(Grafo));
  return NULL;
};

struct ParsedEdges {
  u32 **tuplas;
  u32 n;
  u32 m;
};

void *parseEdges() {
  char line[MAX_LINE_LENGTH];
  
  u32 numVertices;

  // Estos tienen que matchear luego de leer los aristas
  u32 numAristas;
  // Contador de aristas que leimos
  u32 aristasLeidos = 0;

  // Variables para leer cada tupla antes de guardar en memoria dinamica
  u32 vertice;
  u32 vecino;

  // Primero avanzamos hasta el p
  while(fgets(line, MAX_LINE_LENGTH, stdin)) {
    if(line[0] == 'p') {
      scanf("p edge %u %u", &numVertices, &numAristas);
      break;
    } else if (line[0] == 'e') {
      // Hay un arista antes que el encabezado del grafo
      return NULL;
    }
  }

  // Arreglo de tuplas en memoria dinamica 
  // Duplicamos el tamanio pq las insertamos rotadas tambien
  u32 **tuplas = malloc(numAristas * 2 * sizeof(u32*));

  while(fgets(line, MAX_LINE_LENGTH, stdin) && aristasLeidos <= numAristas) {
    if (line[0] == 'e') {
      if (aristasLeidos == numAristas) {
        // ERROR: estamos leyendo un arista y ya no deberian haber mas
        for(u32 i=0; i<aristasLeidos; ++i) {
          free(tuplas[i]);
        }
        free(tuplas);
        return NULL;
      }
      scanf("e %u %u", &vertice, &vecino);

      // Agrego la tupla
      u32 *tupla = malloc(2 * sizeof(u32));
      tupla[0] = vertice;
      tupla[1] = vecino;
      tuplas[aristasLeidos] = tupla;

      // Agrego la tupla rotada
      u32 *tuplarotada = malloc(2 * sizeof(u32));
      tupla[0] = vertice;
      tupla[1] = vecino;
      tuplas[aristasLeidos+1] = tupla;
      ++aristasLeidos;
    }

  }

  struct ParsedEdges *ret = malloc(sizeof(struct ParsedEdges));
  ret->n = numVertices;
  ret->m = numAristas;
  ret->tuplas = tuplas;
  return ret;
}

void DestruirGrafo(Grafo G) {
  if (G->vertices != NULL) {
    for (u32 i = 0; i < G->num_vertices; ++i) {
      if (G->vertices[i] != NULL) {
        G->vertices[i] = vertice_destroy(G->vertices[i]);
      }
    };
  }
  free(G->vertices);
  G->vertices = NULL;
  free(G);
  G = NULL;
};

u32 NumeroDeVertices(Grafo G) { return G->num_vertices; };
u32 NumeroDeLados(Grafo G) { return G->num_aristas; };
u32 Delta(Grafo G) { return G->deltaMax; };

u32 Nombre(u32 i, Grafo G) { return G->vertices[i]->nombre; };
u32 Grado(u32 i, Grafo G) { return G->vertices[i]->grado; };
u32 IndiceVecino(u32 j, u32 i, Grafo G) {
  // Todo
  return NULL;
};
