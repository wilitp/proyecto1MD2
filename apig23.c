//#include <stdlib.h>
//#include <stdio.h>


#include "apig23.h"

int ordenador(void * x, void * y){
    return (((u32 * )x)[0] - ((u32 * )y)[0]);
}

static void ordenarTuplas(u32 * array_tuplas, u32 size){
    qsort(array_tuplas, size, 2 * sizeof(u32), (void *)&ordenador);
}


static void * * parseEdges(u32 * n, u32 * m){
    *n = 3;
    *m = 4;
    return NULL;
}



static vertice * createPositionalArrayWithVecinos(u32 n, u32 array[n][2], Grafo grafo){
    u32 grado = 0;
    int index = -1;
    vertice * nodos = calloc(grafo->n, sizeof(vertice));
    u32 lastValue = (array[0][0]) + 1;  //caso inicial
    for(int i=0; i<(grafo->m); ++i){
        if(lastValue != array[i][0]){
            index++;
            nodos[index] = vertice_empty(array[i][0]);
        }
        nodos[index] = vertice_add_vecino(nodos[index], array[i][1]);
        //printf("se agrego el vecino nombre: %i\n", array[i][0]);
        if(grado < vertice_grado(nodos[index])){
            grado = vertice_grado(nodos[index]);
        }
        lastValue = array[i][0]; 
    }
    grafo->deltaMax = grado;
    return nodos;
}

static u32 binarySearch(vertice * vertices, u32 n, u32 name){   //no se si anda
    unsigned int index = n/2;
    unsigned int iterations = 2;
    while(vertice_nombre(vertices[index]) != name){
        if(vertice_nombre(vertices[index]) > name){
            index = index - n / iterations; 
        }else{
            index = index + n / iterations; //tengo la sensa de que se deberia redondear paarribanomas 
        }
        iterations++;
    }
    return index;
}

static vertice * changeFromNameToPos(vertice * vertices, int n){
    for(int i = 0; i<n; ++i){
        for(int vecino = 0; vecino < vertice_grado(vertices[i]); ++vecino){
            vertice_set_vecino_name(vertices[i], vecino, binarySearch(vertices, n, vertice_get_vecino(vertices[i], vecino)));
        }
    }
    return vertices;
}

Grafo ConstruirGrafo(){
    Grafo grafoNuevo  =  malloc(sizeof(struct GrafoSt));
    parseEdges(&(grafoNuevo->n), &grafoNuevo->m);  //agrega los pares rotados
    u32 arrayEdges[4][2] = {{2,1},{1,2},{1,3},{3,1}};
    ordenarTuplas(arrayEdges, grafoNuevo->n);
    vertice * vertices = createPositionalArrayWithVecinos(grafoNuevo->n, arrayEdges, grafoNuevo); 
    //ahora solo falta transformarlos de nombres a posicion
    vertices = changeFromNameToPos(vertices, grafoNuevo->n);
    printf("\n");
    for(int i=0; i<grafoNuevo->n; ++i){
        printf("posicion: %i, nombre: %i, vecinos: ", i, vertice_nombre(vertices[i]));
        for(int j=0; j<vertice_grado(vertices[i]); ++j){
            printf("%i ",(int)vertice_get_vecino(vertices[i], j));
        }
        printf("\n");
    }
    //grafoNuevo->vertices = vertices;
    return NULL;
};

void DestruirGrafo(Grafo G){
    if (G->vertices != NULL){
        for (u32 i=0; i<G->n; ++i) {
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
    return G->n;
};
u32 NumeroDeLados(Grafo G){
    return G->m;
};
u32 Delta(Grafo G){
    return G->deltaMax;
};


u32 Nombre(u32 i,Grafo G){
    return G->vertices[i]->nombre;
};
u32 Grado(u32 i,Grafo G){
    //return G->vertices[i];
    return 0;
};
u32 IndiceVecino(u32 j,u32 i,Grafo G){
    //Todo
    return NULL;
};


