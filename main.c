#include "apig23.h"
int main(int argc, char const *argv[])
{
    Grafo g = ConstruirGrafo();
    // DestruirGrafo(g);
    return 0;
    for (int i = 0; i < g->n; ++i) {
        printf("posicion: %u, nombre: %u, vecinos: ", i,
            vertice_nombre(g->vertices[i]));
        for (int j = 0; j < vertice_grado(g->vertices[i]); ++j) {
        printf(" %u ", vertice_get_vecino(g->vertices[i], j));
        }
        printf("\n");
    }
    return 0;
}
