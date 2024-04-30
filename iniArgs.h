#ifndef _INIARGS
#define _INIARGS

#include <string.h>

// Define o nome do arquivo a ser lido
#define ARQ "postProcessing/forceCoef/0/forceCoeffs.dat"

// Cria uma estrutura que é usada para guardar as opções de entrada por argumentos de linha de comando
typedef struct entrada{
	
	// O número da coluna cuja a média será calculada
	int col;
	
	// Os índices na matriz de pontos flutuantes que definem o intervalo de tempo cuja a média será calculada
	int tmin, tmax;

}entrada;

// Caso o usuário peça ajuda, essa função será chamada
void help();

// Trata os argumentos de linha de comando
void verificaArgs(int, char **, entrada *, int, int, double**);

// Compara a parte inteira de variáveis tipo double
bool intCmp(double, double);

#endif

