#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiros.h"


//Parte de adição, remoção e alteração de meios

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio* inicio, int cod)
{
	while (inicio != NULL)
	{
		if (inicio->codigo == cod) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut,float cust, char geocod[])
{
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
			novo->geocodigo;
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}

Meio* removerMeio(Meio* inicio, int cod)
{
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
		while ((atual != NULL) && (atual->codigo != cod))
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

//Parte de adição, remoção e alteração de utilizadores



//Parte de adição, remoção e alteração de administradores
