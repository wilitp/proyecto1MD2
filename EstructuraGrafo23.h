#ifndef ESTRUCTURA
#define ESTRUCTURA 

#include "./vertice/vertice.h"

typedef unsigned int u32;

struct GrafoSt {
  u32 deltaMin;
  u32 deltaMax;
  u32 num_vertices;
  u32 num_aristas;
  vertice *vertices;
};

#endif

