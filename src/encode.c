#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitstream/bitstream.h"
#include "huffman/huffman.h"
#include "heapq/heapq.h"
#define ALPHABET_SIZE 256


/*
 * Para decodar um arquivo, a frequencia de um nodo é inutil entao cada
 * nodo da arvore huffman sera representada por 1 bit e 1 byte.
 * 1 bit -> Representa se o nodo é folha. (1-Folha; 0-Nao)
 * Se um nodo eh folha, entao eh necessario um byte que guarda o character 
 * daquele nodo.
 */

int* build_frequency_map(FILE* input)
{
    int* frequencyMap = malloc(sizeof(int) * ALPHABET_SIZE);
    char c;
    for(int i = 0; i < ALPHABET_SIZE; i++)
        frequencyMap[i] = 0;
    while ((c = fgetc(input)) != EOF)
        frequencyMap[(unsigned char)c]++;
    rewind(input);
    return frequencyMap;
}

HuffNode* build_encode_tree(int* frequencyMap)
{
    HuffNode* tree;
    HuffNode* s0; 
    HuffNode* s1;
    Heapq* queue = heapq_new(ALPHABET_SIZE, huffnode_compare);
    int sum;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (frequencyMap[i] > 0)
            heapq_push(queue, huffnode_new(i, frequencyMap[i], NULL, NULL));
    while (heapq_get_size(queue) > 1) {
        s0 = heapq_pop(queue);
        s1 = heapq_pop(queue);
        sum = (s0->count) + (s1->count);
        heapq_push(queue, huffnode_new(0, sum, s0, s1));
    }
    tree = heapq_pop(queue);
    heapq_destroy(queue);
    return tree;
}

void traversing_tree(HuffNode* huffmanTree, char** encodeMap, char* encodeStr)
{
    int nrBits = strlen(encodeStr);
    if(huffnode_is_leaf(huffmanTree)) {
        encodeMap[(unsigned char)huffmanTree->c] = malloc(sizeof(char) * (nrBits+1));
        strcpy(encodeMap[(unsigned char)huffmanTree->c], encodeStr);
    } else {
        traversing_tree(huffmanTree->left, encodeMap, strcat(encodeStr, "0"));
        encodeStr[nrBits] = '\0';
        traversing_tree(huffmanTree->right, encodeMap, strcat(encodeStr, "1"));
        encodeStr[nrBits] = '\0';
    }
}

char** build_encoding_map(HuffNode* huffmanTree)
{
    char** encodeMap = malloc(sizeof(char*) * ALPHABET_SIZE);
    char encodeStr[256] = "\0";
    for(int i = 0; i < ALPHABET_SIZE; i++)
        encodeMap[i] = NULL;
    traversing_tree(huffmanTree, encodeMap, encodeStr);
    //Show the encoding map
    for(int i = 0; i < ALPHABET_SIZE; i++)
        if(encodeMap[i] != NULL)
            printf("%d --> %s\n", i, encodeMap[i]);
    return encodeMap;
}

void encode_huffmantree(FILEB* output, HuffNode* huffmanTree)
{
    if(huffnode_is_leaf(huffmanTree)) {
        fputb(output, 1);
        fbwrite(output, &huffmanTree->c, sizeof(huffmanTree->c));
    } else {
        fputb(output, 0);
        encode_huffmantree(output, huffmanTree->left);
        encode_huffmantree(output, huffmanTree->right);
    }
}

void encode_character(FILEB* output, char* encodeStr)
{
    for(int i = 0; i < strlen(encodeStr); i++)
        (encodeStr[i] == '1') ? fputb(output, 1) : fputb(output, 0);
}

void encode(FILE* input, FILEB* output)
{
    int* frequencyMap = build_frequency_map(input);
    HuffNode* huffmanTree = build_encode_tree(frequencyMap);
    char** encodeMap = build_encoding_map(huffmanTree);
    encode_huffmantree(output, huffmanTree);
    char c;
    while((c = fgetc(input)) != EOF)
        encode_character(output, encodeMap[(unsigned char)c]);
    free(frequencyMap);    
    huffnode_destroy(huffmanTree);
    for(int i = 0; i < ALPHABET_SIZE; i++)
        free(encodeMap[i]);
    free(encodeMap);
    return;
}

int main(int argc, char *argv[])
{
    FILE* input;
    FILEB* output;
    if(argc != 3) {
       printf("[Error] Argumentos invalidos!\n");
       return 0;
    }
    input = fopen(argv[1],"r");
    output = fbopen(argv[2],"w");
    if(input == NULL) {
        printf("[Error] Arquivo original nao encontrado!\n");
    } else if(output == NULL) { 
        printf("[Error] Arquivo encodado não pode ser criado!\n");
    } else {
        encode(input, output);
        fclose(input);
        fbclose(output);
    }
    return 0;
}
