#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/* 
 * HuffNode_new: Char Int HuffNode HuffNode -> HuffNode 
 * Inicializa um nodo com os paramentros passados.
 */
struct HuffNode *huffnode_new(char c, unsigned int count, struct HuffNode *left, struct HuffNode *right)
{
    struct HuffNode *new = malloc(sizeof(struct HuffNode));
    new->c = c;
    new->count = count;
    new->left = left;
    new->right = right;
    return new;
}

/* 
 * HuffNode_is_leaf: HuffNode -> Boolean 
 * Verifica se o nodo é um folha checando o ponteiro de seus filhos.
 */
int huffnode_is_leaf(struct HuffNode *node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 
 * HuffNode_compare: Pointer Pointer -> Int 
 * Dados dois ponteiros genéricos, faça o cast de ambos e 
 * subtrai o valor de count do primeiro com o valor de count do 
 * segundo.
 */
int huffnode_compare(void *x, void *y)
{
    return ((struct HuffNode*)x)->count - ((struct HuffNode*)y)->count;
}

/* 
 * huffmanTree_destroy: HuffNode
 * Libera da memória o nodo e todos os seus filhos.
 */
struct HuffNode *huffnode_destroy(struct HuffNode *node)
{
    if(node == NULL) 
        return NULL;
    huffnode_destroy(node->left);
    huffnode_destroy(node->right);
    free(node);
    return NULL;
}