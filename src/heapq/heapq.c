#include <stdio.h>
#include <stdlib.h>
#include "heapq.h"

/* Atributos */
struct Heapq {
       unsigned int capacity;
       unsigned int size;
       void **array;
       int(*compare)(void *x, void *y);
};

/* Funções Estaticas da Classe. Códigos no fim do arquivo. */
static int parent(int pos);
static int left(int pos);
static int right(int pos);
static void swap(void **a, void **b);
static void heapify(struct Heapq *self, int i);

/* 
 * heapq_new: Int Function(x,y) -> Heapq 
 * Aloca na memória a estrutura. Inicializa os atributos.
 */
struct Heapq *heapq_new(unsigned int capacity, int(*compare)(void*, void*))
{
    struct Heapq* new = malloc(sizeof(struct Heapq));
    new->capacity = capacity;
    new->size = 0;
    new->array = malloc(sizeof(void*) * capacity);
    new->compare = compare;
    return new;
}

/* 
 * heapq_get_size: Heapq -> Int 
 * Retorna o atributo size. 
 */
unsigned int heapq_get_size(struct Heapq *self)
{
    return self->size;
}

/* 
 * heapq_push: Heapq Pointer -> --
 * Insere o elemento no fim do da heap. Caso tenha ocorrido corretamente,
 * Reconstroi a Heap subindo o objeto até que esteja na posição correta.
 */
int heapq_push(struct Heapq *self, void *ptr)
{ 
    if (self->size == self->capacity)
        return 0; 
    self->size++; 
    int i = self->size - 1; 
    self->array[i] = ptr; 
    while (i != 0 && self->compare(self->array[parent(i)], self->array[i]) > 0) { 
        swap(&self->array[i], &self->array[parent(i)]);
        i = parent(i); 
    } 
    return 1;
} 

/* 
 * heapq_pop: Heapq -> --
 * Remove e retorna o primeiro elemento da estrutura.
 * Heapify a Heap para manter a propriedade. 
 */
void* heapq_pop(struct Heapq *self)
{ 
    if (self->size == 0)
        return NULL;
    if (self->size == 1) { 
        self->size--; 
        return self->array[0]; 
    } 
    void* root = self->array[0]; 
    self->array[0] = self->array[self->size - 1]; 
    self->size--; 
    heapify(self, 0); 
    return root; 
} 

/* 
 * fheapq_peak: Heapq -> --
 * Retorna o primeiro elemento da estrutura.
 */
void* heapq_peak(struct Heapq *self)
{
    return (self->size > 0) ? self->array[0] : NULL;
}

/* 
 * heapq_destroy: Heapq -> -- 
 * Libera a estrutura da memória e todas as instancias presentes.
 */
void heapq_destroy(struct Heapq *self)
{
    for (int i = 0; i < self->size; i++)
        free(self->array[i]);
    free(self->array);
    free(self);
}

/* 
 * parent: Int -> Int 
 * Dado um valor, retorna a posição do pai.
 */
static int parent(int pos)
{
    return (pos - 1) / 2; 
} 

/* 
 * left: Int -> Int 
 * Dado um valor, retorna a posição do filho a esquerda.
 */
static int left(int pos)
{ 
    return (2 * pos) + 1; 
} 

/* 
 * right: Int -> Int 
 * Dado um valor, retorna a posição do filho a direita.
 */
static int right(int pos)
{ 
    return (2 * pos) + 2; 
} 

/* 
 * swap: Pointer Pointer -> -- 
 * Troca dois objetos de posição na heap.
 */
static void swap(void **a, void **b)
{   
    void *temp = *a;
    *a = *b;
    *b = temp;
}

/* 
 * heapify: Heapq Int -> -- 
 * top_down
 */
static void heapify(struct Heapq *self, int i)
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < self->size && self->compare(self->array[l], self->array[i]) < 0) 
        smallest = l; 
    if (r < self->size && self->compare(self->array[r], self->array[smallest]) < 0) 
        smallest = r; 
    if (smallest != i) { 
        swap(&self->array[i], &self->array[smallest]);
        heapify(self, smallest); 
    } 
}