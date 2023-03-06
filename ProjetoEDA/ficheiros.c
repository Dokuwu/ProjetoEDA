#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiroslistas.h"


 /*
 ---------------------------------------------------------------------------------------------------------------------------
 pegar e guardar meios
 */
Meio* pegarregistomeios(Meio* inicio, FILE* bin) {
	char linha[300];
	while (fgets(linha, 300, bin) != NULL) {
		Meio* novo = malloc(sizeof(struct registomeio));
		sscanf(linha, "%d;%[^;];%f;%f;%f;%s", &novo->codigo, novo->tipo, &novo->bateria, &novo->autonomia,&novo->custo, novo->geocodigo);
		novo->seguinte = inicio;
		inicio = novo;
	}
	return inicio;
}

void escreverbinmeios(Meio* inicio, FILE* bin) {

	if (bin != NULL) {
		while (inicio != NULL) {
			fprintf(bin, "%d;%s;%.2f;%.2f;%.2f;%s\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo, inicio->geocodigo);
			inicio = inicio->seguinte;
		}
	}
	else
		printf("Erro na execucao do ficheiro");
}

/*
---------------------------------------------------------------------------------------------------------------------------
pegar e guardar utilizadores
*/
Utilizadores* pegarregistoutil(Utilizadores* inicio, FILE* bin) {
	char linha[300];
	while (fgets(linha, 300, bin) != NULL) {
		Utilizadores* novo = malloc(sizeof(struct registoutil));
		sscanf(linha, "%[^;];%[^;];%d;%f", novo->nome, novo->morada, &novo->NIF, &novo->saldo);
		novo->seguinte = inicio;
		inicio = novo;
	}
	return inicio;
}

void escreverbinutil(Utilizadores* inicio, FILE* bin) {

	if (bin != NULL) {
		while (inicio != NULL) {
			fprintf(bin, "%s;%s;%d;%.2f\n", inicio->nome, inicio->morada, inicio->NIF, inicio->saldo);
			inicio = inicio->seguinte;
		}
	}
	else
		printf("Erro na execucao do ficheiro");
}
/*
---------------------------------------------------------------------------------------------------------------------------
pegar e guardar admins
*/

Administradores* pegarregistoadmin(Administradores* inicio, FILE* bin) {
	char linha[150];
	while (fgets(linha, 150, bin) != NULL) {
		Administradores* novo = malloc(sizeof(struct registoadmin));
		sscanf(linha, "%[^;];%s", novo->nome, novo->senha);
		novo->seguinte = inicio;
		inicio = novo;
	}
	return inicio;
}

void escreverbinadmin(Administradores* inicio, FILE* bin) {
	if (bin != NULL)
		while (inicio != NULL) {
			fprintf(bin, "%s;%s\n", inicio->nome, inicio->senha);
			inicio = inicio->seguinte;
		}
	else
		printf("Erro na execucao do ficheiro");
}