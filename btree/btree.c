#include <assert.h>
#include <stdlib.h>

#include "../vertice/vertice.h"
#include "btree.h"
#include "../EstructuraGrafo23.h"

struct _node_t {
  struct _node_t *left;
  struct _node_t *right;
  vertice vertice;
};

struct btree_s {
  u32 length;
  struct _node_t *head;
};

static struct _node_t *leaf_node(vertice vertice) {
  struct _node_t *node = malloc(sizeof(struct _node_t));
  node->vertice = vertice;
  node->left = NULL;
  node->right = NULL;
  return node;
}

btree_t btree_empty(void) {
  btree_t btree = NULL;
  return btree;
}

btree_t btree_add(btree_t btree, u32 nodo, u32 vecino) {
  // if (btree == NULL) {
  //   btree = leaf_node(nodo, vecino);
  // } else if ()) {
  //   btree->left = btree_add(btree->left, nodo, vecino);
  // } else if (key_less(btree->key, word)) {
  //   btree->right = btree_add(btree->right, word, def);
  // } else {
  //   value_t tmp;
  //   tmp = btree->value;
  //   btree->value = value_clone(def);
  //   key_destroy(tmp);
  // }
  //
  return btree;
}

static struct _node_t *node_destroy(struct _node_t *node) {
  // TODO
  return node;
}

void *btree_dump(btree_t btree) {
  // TODO
  // mallocar array de vetices
  // Hacer dfs iterativo y agregar vertices al array
  // devolver el array
  void *arr = malloc(btree->length);
  while (false){

  }

  return arr;
}

btree_t btree_destroy(btree_t btree) { 
  // TODO: destroy
  return NULL;
}
