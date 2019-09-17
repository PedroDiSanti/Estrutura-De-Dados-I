#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//FILE * entradas = fopen("entradas.txt", "r");
	/*printf("L: %d ", l);
	printf("C: %d\n", c);

	escreveTeclado(teclado, l,c);

	printf("\nPalavra: %s ", palavra); */

void main(){
	int l, c;

	char palavra[10000];
	FILE *arq = fopen("entradasFlavio.txt","r");
	char **teclado;
	
	while(!feof(arq)){
		l = 0;
		c = 0;

		leDados(arq, &l, &c, &teclado, palavra);	

		if(l == 0 && c == 0)
			return;

		char vetTeclas[l*c]; //o máximo de posições caso n tenha repetidos
		char primeiraLetra;
		int tamanho;
		tamanho = vetSemRepetidos(l, c, teclado, vetTeclas);
	 
		//escreveTecladoSemRepeticoes(vetTeclas, tamanho);

		int i, j;
		int matriz[tamanho][tamanho];

		//printf("[%d][%d]\n", l,c);

		//Iniciando a matriz com valores mto grandes para o cálculo do menor caminho
			for(i = 0; i < tamanho; i++){
				for(j = 0; j < tamanho; j++){
					matriz[i][j] = 1000000000;
					if(i == j)
						matriz[i][j] = 0;
				}
			}

	    for (i = 0; i < tamanho; i++)
	    {
	    	detectarVizinhos(vetTeclas[i], tamanho, matriz, l, c, teclado, vetTeclas);
	    }


		while(possuiValoresInfinitos(tamanho,matriz)){
			atualizarTabela(tamanho,matriz);
		}

	    /*for(i = 0; i < tamanho; i++){
			for(j = 0; j < tamanho; j++){
				//if(matriz[i][j] == 1000000000)
					//printf("0 ");
				//else
					printf("%d ", matriz[i][j]);
			}
			printf("\n");
		}*/

		primeiraLetra = vetTeclas[0];
		int sum = 0;

		//printf("\n");
		//printf("Tamanho palavra = %d\n", strlen(palavra));
		//printf("Palavra = %s\n", palavra);
		for (i = 0; i < strlen(palavra) - 1; i++){
			int proxLetra = indexElementoVetTecla(vetTeclas,palavra[i],tamanho);
			int letraAnterior = indexElementoVetTecla(vetTeclas,primeiraLetra,tamanho);
			sum += matriz[letraAnterior][proxLetra];
			//printf("%d\n", matriz[letraAnterior][proxLetra]);
			primeiraLetra = palavra[i];
		}

		int proxLetra = indexElementoVetTecla(vetTeclas,'*',tamanho);
		int letraAnterior = indexElementoVetTecla(vetTeclas,palavra[tamanhoPalavra(palavra) - 2],tamanho);
		
		//printf("%c\n", palavra[tamanhoPalavra(palavra) - 2]);

		sum += matriz[letraAnterior][proxLetra];
		sum += tamanhoPalavra(palavra);

		printf("Num de moves = %d\n", sum);
		printf("\n");
	}
	fclose(arq);
}


