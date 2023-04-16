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
	while (vertices != NULL) { // para libertar as listas anteriormentes criadas, depois de alguma alteração do geocodigo de um meio
		while (vertices->meios != NULL) {
			meioanterior = vertices->meios;
			vertices->meios = vertices->meios->seguinte;
			free(meioanterior);
		}
		vertices = vertices->seguinte;
	}
	vertices = iniciografo;
	while (iniciomeio != NULL) {
		while (strcmp(vertices->geocodigo,iniciomeio->geocodigo)) {
			vertices = vertices->seguinte;
		}
		if (vertices != NULL) {
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

int verificargeocodigo(Grafo* grafo, char* geocodigo) {
	while (grafo != NULL) {
		if (!(strcmp(grafo->geocodigo, geocodigo))) return 1;
		grafo = grafo->seguinte;
	}
	return 0;
}

Grafo* criarvertice(Grafo* inicio, char* geocodigo) {
	Grafo* novo = malloc(sizeof(struct registovertices));
	strcpy(novo->geocodigo, geocodigo);
	novo->adjacente = NULL;
	novo->meios = NULL;
	novo->utils = NULL;
	novo->seguinte = inicio;
	inicio = novo;
	return inicio;
}

int adicionaradjacentes(Grafo* grafo, char* geocodigo, char* geocodigoadj, float peso) {
	int bool;
	bool = verificargeocodigo(grafo, geocodigoadj);
	if (!(bool)) return 1;

	while ((grafo != NULL) && strcmp(grafo->geocodigo, geocodigo)) {
		grafo = grafo->seguinte;
	}
	Adjacentes* verificador = grafo->adjacente;
	while (((verificador != NULL) && strcmp(verificador->geocodigo, geocodigoadj))){
		verificador = verificador->seguinte;
	}
	if (verificador != NULL) return 1;

	Adjacentes* novo = malloc(sizeof(struct registoadjacentes));
	strcpy(novo->geocodigo, geocodigoadj);
	novo->peso = peso;
	novo->seguinte = grafo->adjacente;
	grafo->adjacente = novo;
	return 0;

}

void removermeiovertice(Grafo* grafo,Meio* meio, int cod) {
	Meio* anterior, * atual, * aux;
	while ((meio != NULL) && (meio->codigo != cod))//ir até o codigo ser igual
	{
		meio = meio->seguinte;
	}
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) {//ir até o geocodigo corresponder
		grafo = grafo->seguinte;
	}
	//nao necessita verificação se grafo é null pois temos sempre a certeza que existe um vertice com esse geocodigo
	atual = grafo->meios;
	anterior = grafo->meios;
	aux = grafo->meios;
	if (atual->codigo == cod) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		grafo->meios = aux;
	}
	else
	{

		while ((atual != NULL) && (atual->codigo != cod))//ir avançando na lista, até ser igual.
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(grafo->meios);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			grafo->meios = aux;
		}
	}

}

void mudarcodmeiovertice(Grafo* grafo, Meio* meio, int codnovo) {
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	grafo->meios->codigo = codnovo;
	grafo->meios = aux;
}

void mudartipomeiovertice(Grafo* grafo, Meio* meio, char* tipo){
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	strcpy(grafo->meios->tipo, tipo);
	grafo->meios = aux;
}

//função contem switchcase, pois os valores da bateria autonomia e custo são do mesmo tipo
//Assim, para poupar tempo, realizei um switchcase para mudar perante o escolhido

void mudarbatautcustvertice(Grafo* grafo, Meio* meio, int escolha, float valor) {
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	switch (escolha) {
		case 3: 
			grafo->meios->bateria = valor;
			break;
		case 4:
			grafo->meios->autonomia = valor;
			break;
		case 5:
			grafo->meios->custo = valor;
			break;
	}
	grafo->meios = aux;
}