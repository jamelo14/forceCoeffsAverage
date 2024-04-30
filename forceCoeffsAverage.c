/***************************************************************************************************************************\
													forceCoeffsAverage
										
	  Esse programa tem como objetivo, calcular a média de um dos coeficientes de força presentes no
	arquivo forceCoeffs.dat. Tem um uso bem simples:
		
		forceCoeffsAverage [opções]
		
	  As opções são as seguintes:
	
		-c ou --col		:	Indica a coluna (começando em 1) do arquivo forceCoeffs.dat em que calculada a média.
							Sua inserção é obrigatória.
		 		
		-t ou --tmin	:	Indica o instante de tempo inicial, onde a média começará a ser calculada.
							Por padrão é 0.
							
		-T ou -tmax		:	Indica o instante de tempo final, onde a média será calculada. 
							Por padrão é o último instante de tempo.
	
		-h ou --help	:	Mostra o menu de ajuda.

	  Obs.:	Ele funcionará para quantas colunas e quantas linhas forem inseridas no arquivo, desde que não haja 
			nenhum caractere após o último número de cada linha.
	  		
	  Programador: João Augusto Costa Melo
	  Data da última modificação: 23/10/2023 - 10:55

\***************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "include/iniArq.c"
#include "include/iniArgs.c"

#define ARQ "postProcessing/forceCoef/0/forceCoeffs.dat"

int main(int argc, char **argv)
{
	// variáveis que serão usadas
	entrada opcoes;
	double somaDeAreas, passoDeTempo, **arquivo, media;
	int tmin, tmax, colunas = 0, linhas = 0;

	// Definindo localidade para os caracteres
	setlocale(LC_ALL, "Portuguese");

	// Verifica se o usuário pediu ajuda
	for(int i = 0 ; i < argc ; i++)
		if( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 )
		{
			help();
			
			return 0;
		}

	// Verifica a quantidade mínima de argumentos de linha de comando
	if(argc < 3)
	{
		fprintf(stderr, "%s: Poucos argumentos\n", argv[0]);
		
		return 0;
	}

	// Conferindo a quantidade de linhas e colunas do arquivo	
	arquivo = inicializaArq(ARQ, &linhas, &colunas);

	// Lê os argumentos
	verificaArgs(argc, argv, &opcoes, linhas, colunas, arquivo);
	
	// Calcula a média
	somaDeAreas = 0.0;
	tmin = opcoes.tmin;
	tmax = opcoes.tmax;

	// Calcula a soma da coluna especificada no intervalo especificado
	for(int i = tmin ; i <= tmax - 1 ; i++)
	{
		// Calcula o Delta T
		passoDeTempo = arquivo[i + 1][0] - arquivo[i][0];
	
		printf("arquivo[%d][%d] = %lf\n", i, opcoes.col - 1, arquivo[i][opcoes.col - 1]);		

		// Soma a média
		somaDeAreas += ( passoDeTempo * ( arquivo[i][opcoes.col - 1] ) ) ;	
	}

	// Faz a soma da última área do gráfico
	somaDeAreas += ( passoDeTempo * ( arquivo[tmax][opcoes.col - 1]) );
	
	// Calcula a média entre os valores inseridos
	media = (somaDeAreas) /  ( arquivo[tmax][0] - arquivo[tmin][0]);

	// Printando resultados
	printf("A média da coluna %d no intervalo de tmin = %lf e tmax = %lf é %-.7lf\n", opcoes.col, arquivo[tmin][0], arquivo[tmax][0], media);

	// Desalocando memória	
	fechaArquivo(arquivo, linhas);

	return 0;
}

