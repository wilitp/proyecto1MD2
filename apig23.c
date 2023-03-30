//#include <stdlib.h>
//#include <stdio.h>

#include "apig23.h"
#include <stdio.h>
#include <stdlib.h>

#include "EstructuraGrafo23.h"
//#include "apig23.h"
#include "vertice/vertice.h"

#define MAX_LINE_LENGTH 1024

int ordenador(void *x, void *y) {
  u32 xfirst = *((u32 **)x)[0];
  u32 yfirst = *((u32 **)y)[0];
  if (xfirst < yfirst) {
    return -1;
  } else if (xfirst == yfirst) {
    return 0;
  } else
    return 1;
}

static void ordenarTuplas(u32 **array_tuplas, u32 size) {
  qsort(array_tuplas, size, 2 * sizeof(u32), (void *)&ordenador);
}

static vertice *createPositionalArrayWithVecinos(u32 **array, Grafo grafo) {
  u32 grado = 0;
  int index = -1;
  printf("%u\n", array[0][0]);
  vertice *nodos = calloc(grafo->n * 2, sizeof(vertice));
  u32 lastValue = (array[0][0]) + 1; // caso inicial
  for (int i = 0; i < (grafo->m * 2); ++i) {
    if (lastValue != array[i][0]) {
      index++;
      printf("%d %u\n\n", index, array[i][0]);
      nodos[index] = vertice_empty(array[i][0]);
    }
    nodos[index] = vertice_add_vecino(nodos[index], array[i][1]);
    // printf("se agrego el vecino nombre: %u\n", array[i][0]);
    if (grado < vertice_grado(nodos[index])) {
      grado = vertice_grado(nodos[index]);
    }
    lastValue = array[i][0];
  }
  grafo->deltaMax = grado;
  // nodos[0] = vertice_empty(2);
  return nodos;
}

// static u32 binarySearch(vertice *vertices, u32 n, u32 name) { // no se si
// anda
//   unsigned int index = n / 2;
//   unsigned int iterations = 1;
//   while (vertice_nombre(vertices[index]) != name) {
//     if (vertice_nombre(vertices[index]) > name) {
//       index = index - round(n / iterations);
//     } else {
//       index = index + round(n / iterations); // tengo la sensa de que se
//       deberia
//                                       // redondear paarribanomas
//     }
//     iterations = iterations*2;
//   }
//   return index;
// }
static u32 binarySearch(vertice *vertices, u32 n, u32 name) { // no se si anda
  u32 lower = 0;
  u32 upper = n-1;
  u32 index;

  // Si no es ninguno de los extremos entonces si o si sera uno que este entre medio.
  if(vertice_nombre(vertices[upper]) == name) {
    return upper;
  }
  if(vertice_nombre(vertices[lower]) == name) {
    return lower;
  }
  while (upper - lower > 1) {
    index = lower + (upper - lower) / 2;
    if(vertice_nombre(vertices[index]) < name) {
      lower = index;
    } else if(vertice_nombre(vertices[index]) > name) {
      upper = index;
    } else {
      // Encontramos!!
      return index;
    }
  } 

  return 2^32 -1;
}

static vertice *changeFromNameToPos(vertice *vertices, int n) {
  for (int i = 0; i < n; ++i) {
    for (int vecino = 0; vecino < vertice_grado(vertices[i]); ++vecino) {
      vertice_set_vecino_name(
          vertices[i], vecino,
          binarySearch(vertices, n, vertice_get_vecino(vertices[i], vecino)));
          // 1);
    }
  }
  return vertices;
}

Grafo ConstruirGrafo() {
  Grafo grafoNuevo = malloc(sizeof(struct GrafoSt));
  u32 **arrayEdges =
      parseEdges(&(grafoNuevo->n), &grafoNuevo->m); // agrega los pares rotados
  printf("%u\n", arrayEdges[0][0]);
  printf("%i %i\n", grafoNuevo->n, grafoNuevo->m);
  ordenarTuplas(arrayEdges, 2 * grafoNuevo->m);
  vertice *vertices = createPositionalArrayWithVecinos(arrayEdges, grafoNuevo);
  // ahora solo falta transformarlos de nombres a posicion
  vertices = changeFromNameToPos(vertices, grafoNuevo->n);

  for (int i = 0; i < grafoNuevo->n; ++i) {
    printf("posicion: %u, nombre: %u, vecinos: ", i,
           vertice_nombre(vertices[i]));
    for (int j = 0; j < vertice_grado(vertices[i]); ++j) {
      printf(" %u ", vertice_get_vecino(vertices[i], j));
    }
    printf("\n");
  }
  grafoNuevo->vertices = vertices;
  return grafoNuevo;
};

void *parseEdges(u32 *n, u32 *m) {
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
  while (fgets(line, MAX_LINE_LENGTH, stdin)) {
    if (line[0] == 'p') {
      sscanf(line, "p edge %u %u\n", &numVertices, &numAristas);
      break;
    } else if (line[0] == 'e') {
      // Hay un arista antes que el encabezado del grafo
      return NULL;
    }
  }

  // Arreglo de tuplas en memoria dinamica
  // Duplicamos el tamanio pq las insertamos rotadas tambien
  u32 **tuplas = malloc(numAristas * 2 * sizeof(u32 *));

  while (fgets(line, MAX_LINE_LENGTH, stdin) && aristasLeidos <= numAristas) {
    if (line[0] == 'e') {
      if (aristasLeidos == numAristas) {
        // ERROR: estamos leyendo un arista y ya no deberian haber mas
        for (u32 i = 0; i < aristasLeidos; ++i) {
          free(tuplas[i]);
        }
        free(tuplas);
        return NULL;
      }
      sscanf(line, "e %u %u\n", &vertice, &vecino);

      // Agrego la tupla
      u32 *tupla = malloc(2 * sizeof(u32));
      tupla[0] = vertice;
      tupla[1] = vecino;
      tuplas[2 * aristasLeidos] = tupla;

      // Agrego la tupla rotada
      u32 *tuplarotada = malloc(2 * sizeof(u32));
      tuplarotada[1] = vertice;
      tuplarotada[0] = vecino;
      tuplas[2 * aristasLeidos + 1] = tuplarotada;
      ++aristasLeidos;
    }
  }
  *n = numVertices;
  *m = numAristas;
  printf("se llego\n");
  for (int i = 0; i < numAristas; ++i) {
    printf("par: %u %u\n", tuplas[i][0], tuplas[i][1]);
  }
  return tuplas;
}

void DestruirGrafo(Grafo G) {
  if (G->vertices != NULL) {
    for (u32 i = 0; i < G->n; ++i) {
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

u32 NumeroDeVertices(Grafo G) { return G->n; };
u32 NumeroDeLados(Grafo G) { return G->m; };
u32 Delta(Grafo G) { return G->deltaMax; };

u32 Nombre(u32 i, Grafo G) { return G->vertices[i]->nombre; };
u32 Grado(u32 i, Grafo G) { return vertice_grado(G->vertices[i]); };
