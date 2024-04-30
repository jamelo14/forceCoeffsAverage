#ifndef _INIARQ
#define _INIARQ

#include <stdio.h>
#include <stdlib.h>

// Número máximo de caracteres que uma linha pode ter.
#define CHARS_LINHA 150

// "Cria" o tipo bool em C
typedef int bool;
#define true 1
#define false 0

// Inicializa o arquivo dado e retorna uma matriz de pontos flutuantes com os dados
double **inicializaArq(char *, int *, int *);

// Verifica se um caractere representa um número
bool isNum(char );

// Retorna o ponto flutuante presente na string dada, da coluna dada. Ex.: O terceiro ponto flutuante da string "1.2    2.3    3.4    4.5" é 3.4
double numQuery(char *, int );

// Desaloca a memória da matriz de pontos flutuantes
void fechaArquivo(double **, int);

#endif
