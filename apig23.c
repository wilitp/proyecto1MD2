#include <stdlib.h>
#include <stdio.h>

#include "apig23.h"
#include "EstructuraGrafo23.h"
#include "vertice/vertice.h"



Grafo ConstruirGrafo(){
    //Todo
    return NULL;
};

void DestruirGrafo(Grafo G){
    if (G->vertices != NULL){
        for (u32 i=0; i<G->num_vertices; ++i) {
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



u32 NumeroDeVertices(Grafo G){
    return G->num_vertices;
};
u32 NumeroDeLados(Grafo G){
    return G->num_aristas;
};
u32 Delta(Grafo G){
    return G->deltaMax;
};


u32 Nombre(u32 i,Grafo G){
    return G->vertices[i]->nombre;
};
u32 Grado(u32 i,Grafo G){
    return G->vertices[i]->grado;
};
u32 IndiceVecino(u32 j,u32 i,Grafo G){
    //Todo
    return NULL;
};


