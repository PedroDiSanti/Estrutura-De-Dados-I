#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Ola mundo
	void olaMundo(){
		printf("Olá mundo!\n");
	}

//void leDados(FILE *entradas, int * l, int * c, caracter teclado, int tam){
	void leDados(FILE * entradas, int * linhas, int * colunas, char *** keyboard, char *word){
		//FILE * entradas = fopen(arquivo, "r");
		int i = 0, j = 0;
		char letra;

		//Lendo as dimensões do teclado
		fscanf(entradas, "%d %d \n", linhas, colunas); 
		
		(*keyboard) = malloc ((*linhas) * sizeof(char*));
		
		for(i= 0;i < *linhas;i++){
			*((*keyboard) + i)  = malloc ((*colunas) * sizeof(char));
		}
		
		//Lendo o teclado em si
		for(i = 0; i < *linhas; i++){
			for(j = 0; j < *colunas; j++){
				letra = fgetc(entradas);
				(*keyboard)[i][j] = letra;
			}
			//lendo \n
			fgetc(entradas);
		}
		//Lendo a palavra
		fgets(word, 10000, entradas);

		//fclose(entradas);
	}

//Escreve o teclado
	void escreveTeclado(char **keyboard, int l,int c){
		int i, j;

		for(i = 0; i < l; i++){
			for(j = 0; j < c; j++){
				printf("letra => [%d][%d] = %c\n", i, j, keyboard[i][j]);
			}
		}
	}

//Dado um teclado, retorna um vetor com as teclas do mesmo sem repetições
	int vetSemRepetidos(int l, int c, char **keyboard, char vetor[]){
		int i, j, vez = 0;

		for(i = 0; i < l; i++){
			for(j = 0; j < c; j++){
				if(!existe(keyboard[i][j], vetor, vez)){
					vetor[vez] = keyboard[i][j];
					vez++;
				}
				//printf("%c\n", keyboard[i][j]);
			}
		}

		return vez;
	}

//verifica se existe akele elemento no vetor
	int existe(char elemento, char vetor[], int tam){
		int i;

		for(i = 0; i < tam; i++){
			if(elemento == vetor[i]){
				return 1;
			}
		}

		return 0;
	}

//Escreve o teclado sem repetidos
	void escreveTecladoSemRepeticoes(char vetor[], int tam){
		int i;

		for(i = 0; i < tam; i++){
			printf("[%d]: %c\n", i, vetor[i]);
		}
	}

//Detecta os vizinhos
	void detectarVizinhos(char tecla, int tamanho, int matriz[][tamanho], int l, int c, char **keyboard, char vetTecla[]){
		int i, j, indiceTecla, auxI, auxJ, flag = 0, largura = 0, altura = 0,vizinhosLaterais, vizinhosHorizontais;
		char vizinhoSuperior = ' ',vizinhoDireito = ' ', vizinhoEsquerdo = ' ', vizinhoInferior = ' ';
		int indiceSuperior, indiceInferior, indiceDireito, indiceEsquerdo;

		indiceTecla = indexElementoVetTecla(vetTecla,tecla,tamanho);

		for (i = 0; i < l; i++){
			for (j = 0; j < c; j++){
				if(keyboard[i][j] == tecla){
					flag = 1;
					break;
				}
			}
			if(flag)
				break;
		}

		auxI = i;
		auxJ = j;
		
		while(auxI < l && keyboard[auxI][j] == tecla){
			altura++;
			auxI++;
		}
		while(auxJ < c && keyboard[i][auxJ] == tecla){
			largura++;
			auxJ++;
		}

		if(largura % 2 == 0)
			vizinhosHorizontais = (largura / 2) -1;
		else
			vizinhosHorizontais = (largura / 2);

		if(altura % 2 == 0)
			vizinhosLaterais = (altura / 2) -1;
		else
			vizinhosLaterais = (altura / 2);

		if(i > 0){
			vizinhoSuperior = keyboard[i-1][j + vizinhosHorizontais];
			indiceSuperior = indexElementoVetTecla(vetTecla, vizinhoSuperior, tamanho);
			matriz[indiceTecla][indiceSuperior] = 1;
		}
		if((i + altura) < l){
			vizinhoInferior = keyboard[i+altura][j + vizinhosHorizontais];
			indiceInferior = indexElementoVetTecla(vetTecla, vizinhoInferior, tamanho);
			matriz[indiceTecla][indiceInferior] = 1;
		}
		if(j > 0){
			vizinhoEsquerdo = keyboard[i + vizinhosLaterais][j-1];
			indiceEsquerdo = indexElementoVetTecla(vetTecla, vizinhoEsquerdo, tamanho);
			matriz[indiceTecla][indiceEsquerdo] = 1;
		}
		if((j + largura) < c){
			vizinhoDireito = keyboard[i + vizinhosLaterais][j + largura];
			indiceDireito = indexElementoVetTecla(vetTecla, vizinhoDireito, tamanho);
			matriz[indiceTecla][indiceDireito] = 1;
		}

		//printf("Tecla : %c  -->: cima= %c, baixo = %c, direito = %c, esquerdo = %c\n", tecla,vizinhoSuperior, vizinhoInferior,vizinhoDireito, vizinhoEsquerdo);

	}

	void atualizarTabela(int tamanho, int matriz[][tamanho]){

		int i,j,sum,indexFileira;
		for (i = 0; i < tamanho; i++){
			for (j = 0; j < tamanho; j++){
				if(matriz[i][j] == 0 || matriz[i][j] == 1000000000)
					continue;
				else{
					sum = matriz[i][j];
					for (indexFileira = 0; indexFileira < tamanho; indexFileira++){
						if(matriz[j][indexFileira] + sum < matriz[i][indexFileira]){
							matriz[i][indexFileira] = matriz[j][indexFileira] + sum;
						}						
					}
				}
			}
		}
	}

	int possuiValoresInfinitos(int tamanho,int matriz[][tamanho]){
		int i,j;
		for (i = 0; i < tamanho; i++){
			for (j = 0; j < tamanho; j++){
				if(matriz[i][j] == 1000000000)
					return 1;
			}
		}
		return 0;
	}

	int indexElementoVetTecla(char vetTecla[],char elemento,int tamanho){
		int i;
		for (i = 0; i < tamanho; i++){
			if (vetTecla[i] == elemento)
				return i;
		}
	}

	int tamanhoPalavra(char palavra[]){
		return strlen(palavra);
	}
