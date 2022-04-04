#ifndef HEAPQ_H_INCLUDED
#define HEAPQ_H_INCLUDED

/*
 * Estrutura heapq é uma arvore binaria no qual:
 * 1) cada pai de um nodo é menor ou igual ao seus filhos (MinHeap)
 * ou
 * 2) cada pai de um nodo é maior ou igual ao seus filhos (MaxHeap)
 * A fim de manter esta propriedade e manter o código generalizado,
 * a estrutura necessita da função de comparação entre dois objetos
 * que estão inseridos. A função deve seguir uma das duas regras:
 *   a) Function(x,y) -> < 0 caso x seja menor que y;
 *                       = 0 caso x e y sejam iguais;
 *                       > 0 caso x seja maior que y;
 *      Para MinHeaps.
 *   b) Function(x,y) -> > 0 caso x seja menor que y; 
 *                       = 0 caso x e y sejam iguais;
 *                       < 0 caso x seja maior que y;
 *      Para MaxHeaps. 
 */

struct Heapq;
typedef struct Heapq Heapq;

/* 
 * heapq_new: Int Function(x,y) -> Heapq 
 * Inicializa uma nova heap de tamanho dado por capacity. É necessario 
 * também a função de comparação entre os objetos guardados na estrura.
 * Retorna Null se houver falha. 
 */
struct Heapq* heapq_new(unsigned int capacity, int(*compare)(void*, void*));

/* 
 * heapq_get_size: Heapq -> Int 
 * Retorna a quantidade de elementos presentes na estrutura. 
 */
unsigned int heapq_get_size(struct Heapq *self);

/* 
 * heapq_push: Heapq Pointer -> --
 * Insere um elemento na estrutura; ptr deve ser o ponteiro para o objeto.
 * Retorna 1 se foi inserido corretamente; 0 caso contrario.
 */
int heapq_push(struct Heapq *self, void *ptr);

/* 
 * heapq_pop: Heapq -> --
 * Remove e retorna o primeiro elemento da estrutura.
 * Retorna Null caso a estrutura esteja vazia. 
 */
void *heapq_pop(struct Heapq *self);

/* 
 * heapq_peak: Heapq -> --
 * Retorna o primeiro elemento da estrutura.
 * Retorna Null caso a estrutura esteja vazia.  
 * WARNING: Caso o conteúdo do objeto seja modificado,
 *          a heapq pode perder sua propriedade.
 */
void *heapq_peak(struct Heapq *self);

/* 
 * heapq_destroy: Heapq -> -- 
 * Libera a estrutura da memória. 
 * WARNING: Caso a heapq não esteja vazia, todas as instancias 
 *          inseridas também serão liberadas da memória.
 */
void heapq_destroy(struct Heapq *self);


#endif 