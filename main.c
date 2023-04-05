#include "apig23.h"
int main()
{
    Grafo g = ConstruirGrafo();
    return 0;
    // DestruirGrafo(g);
    for (u32 i = 0; i < g->n; ++i) {
        printf("posicion: %u, nombre: %u, vecinos: ", i,
            vertice_nombre(g->vertices[i]));
        for (u32 j = 0; j < vertice_grado(g->vertices[i]); ++j) {
        printf(" %u ", vertice_get_vecino(g->vertices[i], j));
        }
        printf("\n");
    }
    DestruirGrafo(g);
    return 0;
}
