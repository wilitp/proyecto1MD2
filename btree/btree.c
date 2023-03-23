#include <assert.h>
#include <stdlib.h>

#include "../EstructuraGrafo23.h"
#include "../vertice/vertice.h"
#include "btree.h"

struct _node_t {
  struct _node_t *left;
  struct _node_t *right;
  vertice vertice;
};

struct btree_s {
  u32 length;
  struct _node_t *head;
};

static struct _node_t *leaf_node(u32 nombre_v) {
  struct _node_t *node = malloc(sizeof(struct _node_t));
  vertice v = vertice_empty(nombre_v);
  node->vertice = v;
  node->left = NULL;
  node->right = NULL;
  return node;
}

btree_t btree_empty(void) {
  btree_t btree = NULL;
  return btree;
}

static struct _node_t *btree_add_in_subtree(struct _node_t *head, u32 nodo,
                                            u32 vecino) {
  if (head == NULL) {
    head = leaf_node(nodo);
  } else if (nodo < vertice_nombre(head->vertice)) {
    head->left = btree_add_in_subtree(head->left, nodo, vecino);
  } else if (nodo > vertice_nombre(head->vertice)) {
    head->right = btree_add_in_subtree(head->right, nodo, vecino);
  }
  return head;
}

// Alternativa recursiva (no pinta pq max recursion depth)
// btree_t btree_add(btree_t btree, u32 nodo, u32 vecino) {
//   assert(btree != NULL);
//   btree->head = btree_add_in_subtree(btree->head, nodo, vecino);
//   return btree;
// }

btree_t btree_add(btree_t btree, u32 nombre, u32 vecino) {
  assert(btree != NULL);
  struct _node_t *current = btree->head;

  while (true) {
    if(nombre == vertice_nombre(current->vertice)) {
      vertice_add_vecino(current->vertice, vecino);
      break;
    }
    else if (nombre < vertice_nombre(current->vertice)) {
      if(current->left == NULL) {
        // ponerlo en su lugar y salir del bucle
        current->left = leaf_node(nombre);
        vertice_add_vecino(current->left->vertice, vecino);
        ++btree->length;
        break;
      }
      // Seguir bajando por el arbol
      current = current->left;
    } else if (nombre > vertice_nombre(current->vertice)) {
      if(current->right == NULL) {
        // ponerlo en su lugar y salir del bucle
        current->right = leaf_node(nombre);
        vertice_add_vecino(current->right->vertice, vecino);
        ++btree->length;
        break;
      }
      // Seguir bajando por el arbol
      current = current->right;
    }
  }
  return btree;
}

static struct _node_t *node_destroy(struct _node_t *node) {
  // TODO
  return node;
}

void *btree_dump(btree_t btree) {
  // TODO
  void *arr = malloc(btree->length);
  while (false) {
  }

  return arr;
}

btree_t btree_destroy(btree_t btree) {
  // TODO: destroy
  return NULL;
}
