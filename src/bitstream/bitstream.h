#ifndef BITSTREAM_H_INCLUDED
#define BITSTREAM_H_INCLUDED

/* 
 * Estrutura para arquivos que necessitam de leituras e escritas bit a bit.
 */
struct FileB;
typedef struct FileB FILEB;


/* 
 * fbopen: String String -> File 
 * Abre o arquivo. mode deve ser ("r")ead ou ("w")rite.
 * Retorna Null se arquivo não for encontrado. 
 */
struct FileB* fbopen(const char *filename, const char *mode);

/* 
 * fbclose: File -> - 
 * Fecha o arquivo e libera metadados da memória.
 */
void fbclose(struct FileB *stream);

/* 
 * fgetb: File -> Int 
 * Le um bit do arquivo e rotorna-o.
 * Caso seja o fim do arquivo, retorna EOF.  
 */
int fgetb(struct FileB *stream);

/* 
 * fputb: File -> - 
 * Insere um bit no fim do arquivo.
 */
void fputb(struct FileB *stream, int bit);

/* 
 * fbread: File Pointer Size -> - 
 * Le um dado do arquivo, valor é colocado em ptr.
 * Retorna a quantidade de bits lido corretamente.
 */
void fbread(struct FileB *stream, void *ptr, size_t size);

/* 
 * fbwrite: File Pointer Size -> - 
 * Insere um dado no arquivo, valor deve estar em ptr.
 * Retorna a quantidade de bits escrito corretamente.
 */
void fbwrite(struct FileB *stream, void *ptr, size_t size);

#endif 