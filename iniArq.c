#include "iniArq.h"

// Inicializa o arquivo dado e retorna uma matriz de pontos flutuantes com os dados
double **inicializaArq(char *arq, int *linhas, int *colunas)
{
	FILE *fp = NULL;
	char linha[CHARS_LINHA];

	*colunas = 0;
	*linhas = 0;	

	fp = fopen(arq, "r");

	if(fp == NULL)
	{
		fprintf(stderr, "Erro: Arquivo não pode ser aberto!\n");
		exit(1);	
	}

	// Pulando os comentários do arquivo
	do{
		fscanf(fp, " %[^\n]", linha);
	}while(linha[0] == '#' && feof(fp) != EOF);
	
	// Variáveis para se usar temporariamente
	char **proximo = malloc(sizeof(char*)), **var = malloc(sizeof(char*));
	
	*var = linha;
	
	// Contando colunas
	do{	
		strtod(*var, proximo);
		
		*var = *proximo;
		
		(*colunas)++;
		
	} while( *proximo[0] != 0 );
	
	// Liberando memória alocad das variáveis
	free(var);
	free(proximo);

	// Contando linhas
	(*linhas)++;
	
	while(fscanf(fp, " %*[^\n]") != EOF)
		(*linhas)++;
	
	// Reposiciona o ponteiro para o início do arquivo
	rewind(fp);
	
	// Pulando os comentários
	do{
		fscanf(fp, " %[^\n]", linha);
	}while(linha[0] == '#' && feof(fp) != EOF);
	
	// Alocando memódia dinamicamente - preparando a matriz de pontos flutuantes
	double **arquivo = (double**) calloc(*linhas, sizeof(double *));

	for(int i = 0 ; i < (*linhas) ; i++)
		arquivo[i] = (double*) calloc(*colunas, sizeof(double));
		
	// Carregando arquivo em uma matriz de pontos flutuantes
	int i = 0, j = 0;
	do{
		// Carregando a coluna do tempo
		arquivo[i][0] = strtod(linha, NULL);		

		// Carrengando outras colunas
		for(j = 1 ; j < *colunas ; j++)
			arquivo[i][j] = numQuery(linha, j);;

		i++;
	}while(fscanf(fp, " %[^\n]", linha) != EOF);	

	// Fecha o arquivo
	fclose(fp);

	// Retorna a matriz de pontos flutuantes com todos os dados do arquivo
	return arquivo;
}

// Verifica se um caractere representa um número
bool isNum(char car)
{
	if((car >= '0' && car <= '9') || car == '-')
		return true;

	return false;
}

// Desaloca a memória da matriz de pontos flutuantes
void fechaArquivo(double **arquivo, int linhas)
{

	// Liberando memória alocada dinamicamente
	for(int i = 0 ; i < linhas ; i++)
		free(arquivo[i]);

	free(arquivo);

	return;
}

// Retorna o ponto flutuante presente na string dada, da coluna dada. Ex.: O terceiro ponto flutuante da string "1.2    2.3    3.4    4.5" é 3.4
double numQuery(char *linha, int num)
{
	int coluna = -1;
	double var;
	char **proximo = malloc(sizeof(char*));
	
	// É por essa parte que não pode haver nenhum outro caractere no fim de nenhuma linha
	for(int i = 1 ; linha[i] != 0 ; i++)
	{
		var = strtod(linha, proximo);
		coluna ++;

		if(coluna == num)
		{
			free(proximo);
			return var;
		}
		
		linha = *proximo;

	}
	
	// Esse retorno foi posto para que o compilador não reclame.
	return 0.0;
}
