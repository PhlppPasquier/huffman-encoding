#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

struct HuffNode {
       char c;
       unsigned int count;
       struct HuffNode *left;
       struct HuffNode *right;
};

typedef struct HuffNode HuffNode;

/* 
 * huffmannode_new: Char Int HuffmanNode HuffmanNode -> HuffmanNode 
 * Cria um Novo nodo com os parametros passados.
 * Retorna Null se houver falha. 
 */
struct HuffNode *huffnode_new(char c, unsigned int count, struct HuffNode *left, struct HuffNode *right);

/* 
 * huffmannode_is_leaf: HuffmanNode -> Boolean 
 * Retorna 1 se o nodo for folha; Retorna 0 caso contrario.
 */
int huffnode_is_leaf(struct HuffNode *node);

/* 
 * huffmannode_compare: Pointer Pointer -> Int 
 * Retorna: < 0 caso x.count seja menor que y.count;
 *          = 0 caso x.count e y.count sejam iguais;
 *          > 0 caso x.count seja maior que y.count. 
 */
int huffnode_compare(void *x, void *y);

/* 
 * huffmantree_destroy: HuffmanNode
 * Libera da memória a arvore. 
 */
struct HuffNode *huffnode_destroy(struct HuffNode *root);

#endif 