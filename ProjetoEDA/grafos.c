#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiroslistas.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//						Criação e guardar o grafo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Grafo* pegarregistografo(Grafo* inicio, FILE* bin) {
	char linha[200];
	char* token;
	int i = 0;
	Grafo* vertices = NULL;

	while ((fgets(linha, 200, bin) != NULL)) {
		if (i == 0) {

			int len = strlen(linha); // para remover o \n no final da linha
			if (linha[len - 1] == '\n') {
				linha[len - 1] = '\0';
				if(linha[len - 2] == '\r')
					linha[len - 2] = '\0';
			}

			token = strtok(linha, ";");
			while (token != NULL) {
				Grafo* novo = malloc(sizeof(struct registovertices));
				strcpy(novo->geocodigo, token);
				novo->adjacente = NULL;
				novo->meios = NULL;
				novo->utils = NULL;
				token = strtok(NULL, ";");
				novo->seguinte = inicio;
				inicio = novo;
			}

			vertices = inicio;
			i = 1;
		}
		else {

			int len = strlen(linha); // para remover o \n no final da linha
			if (linha[len - 1] == '\n') {
				linha[len - 1] = '\0';
			}

			token = strtok(linha, ";");
			while (!(strcmp(vertices->geocodigo, token)) != 1) {
				vertices = vertices->seguinte;
			}

			token = strtok(NULL, ";");
			while (token != NULL) {
				Adjacentes* novo = malloc(sizeof(struct registoadjacentes));
				strcpy(novo->geocodigo, token);
				token = strtok(NULL, ";");
				novo->peso = atof(token); //atoi serve para converter string para inteiro
				novo->seguinte = vertices->adjacente;
				vertices->adjacente = novo;
				token = strtok(NULL, ";");
			}

			vertices = inicio;
		}
	}

	return inicio;
}

void fixarmeiosvertices(Meio* iniciomeio, Grafo* iniciografo) {
	Grafo* vertices = iniciografo;
	Meio* meioanterior;
	while (iniciomeio != NULL) {
			while (strcmp(vertices->geocodigo,iniciomeio->geocodigo)) {
				vertices = vertices->seguinte;
			}
			if(vertices != NULL){
				Meio* novomeio = malloc(sizeof(struct registomeio));
				novomeio->custo = iniciomeio->custo;
				novomeio->codigo = iniciomeio->codigo;
				novomeio->bateria = iniciomeio->bateria;
				novomeio->autonomia = iniciomeio->autonomia;
				novomeio->alugado = iniciomeio->alugado;
				strcpy(novomeio->tipo, iniciomeio->tipo);
				strcpy(novomeio->geocodigo, iniciomeio->geocodigo);
				novomeio->seguinte = vertices->meios;
				vertices->meios = novomeio;
			}
			vertices = iniciografo;
			iniciomeio = iniciomeio->seguinte;
	}
	
}

void fixarutilsvertices(Utilizadores* inicioutils, Grafo* iniciografo) {

}