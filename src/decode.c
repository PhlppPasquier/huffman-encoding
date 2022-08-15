#include <stdio.h>
#include <string.h>
#include "bitstream/bitstream.h"
#include "huffman/huffman.h"

HuffNode* decode_tree(FILEB* input)
{
    char c;
    int bit = fgetb(input);
    if (bit == 1) {
        fbread(input, &c, sizeof(c));
        return huffnode_new(c, 0, NULL, NULL);
    } else {
        HuffNode* left = decode_tree(input);
        HuffNode* right = decode_tree(input);
        return huffnode_new(0, 0, left, right);
    }
}

void decode(FILEB* input, FILE* output)
{
    HuffNode* tree = decode_tree(input);
    HuffNode* current = tree;
    int bit;
    while((bit = fgetb(input)) != EOF) {
        current = (bit == 0) ? current->left : current->right;
        if(huffnode_is_leaf(current)) {
            fputc(current->c, output);
            current = tree;
        }
    }
    huffnode_destroy(tree);
}

int main(int argc, char const *argv[])
{
    BitFILE* input;
    FILE* output;
    if(argc != 3) {
       printf("[Erro] Argumentos invalidos!\n");
       return 0;
    }
    input = fbopen(argv[1],"r");
    output = fopen(argv[2],"w");
    if(input == NULL) {
        printf("[Error] Arquivo encodado nao encontrado!\n");
    } else if(output == NULL) { 
        printf("[Error] Arquivo novo não pode ser criado!\n");
    } else {
        decode(input, output);
        fbclose(input);
        fclose(output);
    }
    return 0;
}