#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ficheiroslistas.h"


 /*
 ---------------------------------------------------------------------------------------------------------------------------
 pegar e guardar meios
 ---------------------------------------------------------------------------------------------------------------------------
 */
Meio* pegarregistomeios(Meio* inicio, FILE* bin) {
	char linha[300];
	while (fgets(linha, 300, bin) != NULL) {//enquanto a variavel linha, for diferente a NULL, sendo a linha uma linha do ficheiro.
		Meio* novo = malloc(sizeof(struct registomeio));
		sscanf(linha, "%d;%[^;];%d;%f;%f;%f;%s", &novo->codigo, novo->tipo, &novo->alugado, &novo->bateria, &novo->autonomia,&novo->custo, novo->geocodigo);
		novo->alugado = 0;//para realiza��o de teste e espera de uma solu��o
		novo->seguinte = inicio;
		inicio = novo;
	}
	return inicio;
}

void escreverbinmeios(Meio* inicio, FILE* bin) {

	if (bin != NULL) {
		while (inicio != NULL) {//guarda a cada linha as informa��es de cada meio at� acabar a lista
			fprintf(bin, "%d;%s;&d;%.2f;%.2f;%.2f;%s\n", inicio->codigo, inicio->tipo,inicio->alugado, inicio->bateria, inicio->autonomia, inicio->custo, inicio->geocodigo);
			inicio = inicio->seguinte;
		}
	}
	else
		printf("Erro na execucao do ficheiro");
}

/*
---------------------------------------------------------------------------------------------------------------------------
pegar e guardar utilizadores
---------------------------------------------------------------------------------------------------------------------------
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
---------------------------------------------------------------------------------------------------------------------------
*/

Administradores* pegarregistoadmin(Administradores* inicio, FILE* bin) {
	char linha[150];
	while (fgets(linha, 150, bin) != NULL) {
		Administradores* novo = malloc(sizeof(struct registoadmin));
		sscanf(linha, "%d;%[^;];%s", &novo->codigo, novo->nome, novo->senha);
		novo->seguinte = inicio;
		inicio = novo;
	}
	return inicio;
}

void escreverbinadmin(Administradores* inicio, FILE* bin) {
	if (bin != NULL)
		while (inicio != NULL) {
			fprintf(bin, "%d;%s;%s\n",inicio->codigo, inicio->nome, inicio->senha);
			inicio = inicio->seguinte;
		}
	else
		printf("Erro na execucao do ficheiro");
}

/*
---------------------------------------------------------------------------------------------------------------------------
guardar um alugamento num historico
---------------------------------------------------------------------------------------------------------------------------
*/

void guardarhistorico(Utilizadores* util, Meio* meio) {
	FILE* historico;
	historico = fopen("historico.bin", "ab");
	if (historico != NULL) {
		time_t t;
		time(&t);//fun��o que pega a data atual e guarda na variavel
		fprintf(historico, "Nome: %s NIF: %d Codigo do meio: %d Geocodigo: %s Data: %s", util->nome, util->NIF, meio->codigo, meio->geocodigo, ctime(&t));
	}
	else
		printf("Erro ao abrir ficheiro para guardar historico!\n");
	fclose(historico);
}