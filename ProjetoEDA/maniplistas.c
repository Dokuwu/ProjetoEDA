#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiroslistas.h"


//Parte de adição, remoção e alteração de meios

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio* inicio, int cod){
	while (inicio != NULL)
	{
		if (inicio->codigo == cod) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut,float cust, char geocod[]){
	if (!existeMeio(inicio, cod))
	{
		Meio* novo = malloc(sizeof(struct registomeio));
		if (novo != NULL)
		{
			novo->codigo = cod;
			strcpy(novo->tipo, tipo);
			novo->bateria = bat;
			novo->autonomia = aut;
			novo->custo = cust;
			strcpy(novo->geocodigo,geocod);
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}

Meio* removerMeio(Meio* inicio, int cod){
	Meio* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia
	else if (atual->codigo == cod) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (atual->codigo != cod))//ir avançando na lista, até ser igual.
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(inicio);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(inicio);
		}
	}
}

void BubbleSortMeios(Meio* inicio) {
	int b = 1;
	Meio* atual, * seguinte;
	//a variavel ultimo simboliza o fim da lista
	while (b) {
		b = 0;
		atual = inicio;
		//se o proximo do atual, for diferrente de ao ultimo ele vai realizar a verificação
		while (atual->seguinte != NULL) {
			seguinte = atual->seguinte;//pega o nó à frente do atual

			if (atual->codigo < seguinte->codigo) {
				// se o codigo da atual for menor que a do seguinte, troca os elementos
				int auxcodigo = atual->codigo;
				float auxbateria = atual->bateria;
				float auxautonomia = atual->autonomia;
				char auxtipo[50];
				strcpy(auxtipo, atual->tipo);

				atual->codigo = seguinte->codigo;
				atual->bateria = seguinte->bateria;
				atual->autonomia = seguinte->autonomia;
				strcpy(atual->tipo, seguinte->tipo);

				seguinte->codigo = auxcodigo;
				seguinte->bateria = auxbateria;
				seguinte->autonomia = auxautonomia;
				strcpy(seguinte->tipo, auxtipo);

				b = 1;
			}
			atual = seguinte;//depois de verificar, avança um nó para a frente
		}
	}
}
//Parte de adição, remoção e alteração de utilizadores



//Parte de adição, remoção e alteração de administradores

int existeAdmin(Administradores* inicio,char nome[]){
	while (inicio != NULL)
	{
		if (!(strcmp(inicio->nome,nome))) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Administradores* inserirAdmins(Administradores* inicio, char nome[], char senha[]){
	if (!existeAdmin(inicio, nome))
	{
		Administradores* novo = malloc(sizeof(struct registoadmin));
		if (novo != NULL)
		{
			strcpy(novo->nome, nome);
			strcpy(novo->senha, senha);
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}


Administradores* removerAdmins(Administradores* inicio, char nome[]){
	Administradores* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia
	else if (!(strcmp(atual->nome,nome))) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && strcmp(atual->nome, nome))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(inicio);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(inicio);
		}
	}
}