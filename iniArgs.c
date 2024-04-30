#include "iniArgs.h"
#include <string.h>

// Caso o usuário peça ajuda, essa função será chamada
void help()
{
	printf("\n\t\t\t\t\t****** forceCoeffsAverage ******\n\n");

	printf("  Esse programa tem como objetivo, calcular a média de um dos coeficientes de força presentes no\n");
	printf("arquivo forceCoeffs.dat. Tem um uso bem simples:\n\n");
	printf("\tforceCoeffsAverage [opções]\n\n");

	printf("  As opções são as seguintes:\n\n");

	printf("\t-c ou --col\t:\tIndica a coluna (começando em 1) do arquivo forceCoeffs.dat em que calculada a média.\n");
	printf("\t\t\t\tSua inserção é obrigatória.\n\n");
 		
	printf("\t-t ou --tmin\t:\tIndica o instante de tempo inicial, onde a média começará a ser calculada.\n");
	printf("\t\t\t\tPor padrão é 0.\n\n");
					
	printf("\t-T ou -tmax\t:\tIndica o instante de tempo final, onde a média será calculada.\n"); 
	printf("\t\t\t\tPor padrão é o último instante de tempo.\n\n");
	
	printf("\t-h ou --help\t:\tMostra este menu de ajuda.\n\n");

	printf("  Obs.:\tEle funcionará para quantas colunas e quantas linhas forem inseridas no arquivo, desde que não haja\n"); 
	printf("\tnenhum caractere após o último número de cada linha.\n\n");

	return;
}

// Trata os argumentos de linha de comando
void verificaArgs(int argc, char **argv, entrada *opcoes, int linhas, int colunas, double** arq)
{
	double var;

	opcoes->tmin = 0;
	opcoes->tmax = -1;
	opcoes->col = -1;	

	// Itera sobre os argumentos de linha de comando
	for(int i = 1 ; i < argc ; i++)
	{
		// Se --tmin ou -t foi specificado
		if( ( strcmp(argv[i], "-t" ) == 0 ||  strcmp(argv[i], "--tmin" ) == 0 ) && i + 1 < argc)
		{
			// Salva o tempo inserido em uma variável
			var = strtod(argv[i + 1], NULL);
			
			// Atribui a opcoes->tmin o índice da linha que ele referencia
			for(int j = 0 ; j < linhas ; j++)	
				if(intCmp(var, arq[j][0]) == true)
				{	
					opcoes->tmin = j;
					break;
				}
		}
		
		// Se --tmax ou -T foi especificado
		if( ( strcmp(argv[i], "-T" ) == 0 ||  strcmp(argv[i], "--tmax" ) == 0 ) && i + 1 < argc)
		{	
			// Salva o tempo inserido numa variável
			var = strtod(argv[i + 1], NULL);
			
			// Atribui a opcoes->tmax o índice da linha que ele referencia
			for(int j = 0 ; j < linhas ; j++)
				if(intCmp(var, arq[j][0]) == true)
				{	
					opcoes->tmax = j;
					break;
				}
		}
		
		// Se -c ou --col foi especificada
		if( ( strcmp(argv[i], "-c" ) == 0 ||  strcmp(argv[i], "--col" ) == 0 ) && i + 1 < argc)
			opcoes->col = strtod(argv[i + 1], NULL);
		
	}

	// Se tmax não foi especificado, ele é o último instante de tempo
	if(opcoes->tmax == -1)
		opcoes->tmax = linhas - 1;

	// Se a coluna não foi especificada, o programa não inicia
	if(opcoes->col == -1)
	{
		fprintf(stderr, "Erro: Nenhuma coluna dada para calcular a média no arquivo \"%s\"\n", ARQ);

		fechaArquivo(arq, linhas);

		exit(1);
	}
	
	// Verifica por irregularidades nos argumentos de linha de comando e não inicia caso haja aalguma	
	if( ((opcoes->tmin >= opcoes->tmax) || (opcoes->tmin < 0 || opcoes->tmax < 0 )) || (opcoes->col > colunas || opcoes->col < 1) )
	{
		fprintf(stderr, "Erro: Valores de argumentos inválidos\n");

		fechaArquivo(arq, linhas);

		exit(1);		
	}
	
	return;
}

// Compara a parte inteira de variáveis tipo double
bool intCmp(double n1, double n2)
{
	if((int) n1 == (int) n2)
		return true;
		
	return false;
}
