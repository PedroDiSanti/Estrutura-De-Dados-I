typedef struct caracter_{
	int x;
	int y;
	char valor;
} caracter;

#include <stdlib.h>
#include <stdio.h>

#ifndef FUNCOES_H
#define FUNCOES_H

	void olaMundo();
	void leDados(FILE * entradas, int * linhas, int * colunas, char *** keyboard, char * word);
	void escreveTecladoSemRepeticoes(char vetor[], int tam);
	int existe(char elemento, char vetor[], int tam);
	int vetSemRepetidos(int l, int c, char **keyboard, char vetor[]);
	int indexElementoVetTecla(char vetTecla[],char elemento,int tamanho);
	void detectarVizinhos(char tecla, int tamanho, int matriz[][tamanho], int l, int c, char **keyboard, char vetTecla[]);
	int possuiValoresInfinitos(int tamanho,int matriz[][tamanho]);
	void atualizarTabela(int tamanho, int matriz[][tamanho]);
	int tamanhoPalavra(char palavra[]);
#endif
