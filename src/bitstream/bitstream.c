#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bitstream.h"

/* Atributos */
struct FileB {
    FILE* fp;               //Ponteiro para o arquivo
    const char *mode;       //(r)ead; (w)rite
    unsigned char buffer;   //Buffer em bytes
    int posBuffer;          //Posição do bit lido/escrrto atual.
    char lastPos;           //Pos no buffer do ultimo buffer (Apenas para leitura)
    int lastByte;           //Booleano para verificar se é o ultimo byte do arquivo
};

/* Funções Estaticas da Classe. Códigos no fim do arquivo. */
static void _load_buffer(struct FileB* stream);

/* 
 * fbopen: String String -> File 
 * Abre o arquivo. mode deve ser ("r")ead ou ("w")rite.
 * Retorna Null se arquivo não for encontrado. 
 */
struct FileB* fbopen(const char *filename, const char *mode)
{
    FILE* fp = fopen(filename, mode);
    struct FileB* stream = NULL;
    if(*mode == 'r' && fp != NULL) {
        stream = malloc(sizeof(struct FileB));
        stream->fp = fp;
        stream->mode = mode;
        stream->lastPos = fgetc(stream->fp);
        _load_buffer(stream);
    } else if(*mode == 'w' && fp != NULL) {
        stream = malloc(sizeof(struct FileB));
        stream->fp = fp;
        stream->mode = mode;
        stream->posBuffer = -1;
        fputc(0, stream->fp);  //Sera substituido por posBuffer do ultimo byte
    }
    return stream;
}

/* 
 * fbclose: File -> - 
 * Fecha o arquivo. Importante usar para atualizar os metadados.
 */
void fbclose(struct FileB* stream)
{
    if(*stream->mode == 'w') {
        if(stream->posBuffer != -1)
            fputc(stream->buffer, stream->fp);
        fseek(stream->fp, 0, SEEK_SET);
        putc(stream->posBuffer, stream->fp);
    }
    fclose(stream->fp);
    free(stream); 
}

/* 
 * fgetb: File -> Int 
 * Le um bit do arquivo e rotorna-o.
 * Caso esteja no fim do arquivo, retorna EOF.  
 */
int fgetb(struct FileB* stream)
{
    int bit;
    if(stream->lastByte && stream->lastPos == stream->lastPos)
        return EOF;
    if(stream->posBuffer == -1)
        _load_buffer(stream);
    bit = (stream->buffer >> stream->posBuffer) & 1;
    stream->posBuffer--;
    return bit;
}

/* 
 * fputb: File -> - 
 * Insere um bit no fim do arquivo.
 */
void fputb(struct FileB* stream, int bit)
{   
    if(stream->posBuffer == -1) {
        stream->buffer = 0;
        stream->posBuffer = 7;
    }
    if(bit == 1)
        stream->buffer |= (1 << stream->posBuffer);
    stream->posBuffer--;
    if(stream->posBuffer == -1)
        fputc(stream->buffer, stream->fp);
}

/* 
 * fbread: File Pointer Size -> - 
 * Le dado do arquivo, valor é colocado em ptr.
 */
void fbread(struct FileB* stream, void *ptr, size_t size)
{   
    int bit;
    for(int i = (size - 1); i >= 0; i--) {
        ((char*)ptr)[i] = 0;
        for(int j = 7; j >= 0; j--) {
            bit = fgetb(stream);
            if (bit == 1 && bit != EOF)
                ((char*)ptr)[i] |= (1 << j);
        }
    }
}

/* 
 * fbwrite: File Pointer Size -> - 
 * Insere dado no arquivo, valor deve estar em ptr.
 */
void fbwrite(struct FileB* stream, void *ptr, size_t size)
{
    for(int i = (size - 1); i >= 0; i--)
        for(int j = 7; j >= 0; j--)
            fputb(stream, (((char*)ptr)[i] >> j) & 1);
}

/* 
 * _load_buffer: File -> - 
 * Carrega um novo buffer em memória.
 */
static void _load_buffer(struct FileB* stream)
{
    stream->buffer = fgetc(stream->fp);
    stream->lastByte = fgetc(stream->fp) == EOF;
    fseek(stream->fp, -1, SEEK_CUR);
    stream->posBuffer = 7;
}