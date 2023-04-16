#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "ficheiroslistas.h"

void listarmeios(Meio* inicio) {//funcao para mostrar os meios
	while (inicio != NULL) {
		printf("Codigo:%d Tipo:%s Bateria:%.2f", inicio->codigo, inicio->tipo, inicio->bateria);
		if (inicio->alugado == 1)//se estiver alugado mostra que sim senão mostra que nao
			printf(" Alugado: Sim");
		else
			printf(" Alugado: Nao");
		printf("\nAutonomia: %.2f Custo : %.2f$ geocodigo : %s\n", inicio->autonomia, inicio->custo, inicio->geocodigo);
		printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n");
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listarmeiosgeocod(Meio* inicio, char geocod[]) {//lista os meios pelo geocodigo
	while (inicio != NULL) {
		if (!(strcmp(inicio->geocodigo, geocod))) {//Verifica se o geocodigo é o mesmo
			printf("Codigo:%d | Tipo:%s | Bateria:%.2f |", inicio->codigo, inicio->tipo, inicio->bateria);
			if (inicio->alugado == 1)//se estiver alugado mostra que sim senão mostra que nao
				printf(" Alugado: Sim");
			else
				printf(" Alugado: Nao");
			printf("\nAutonomia: %.2f | Custo : %.2f$ | geocodigo : %s\n", inicio->autonomia, inicio->custo, inicio->geocodigo);
			printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n");
		}
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}


void listaradmins(Administradores* inicio) {
	while (inicio != NULL) {
		printf("Codigo: %d | Nome: %s | Senha: %s\n", inicio->codigo, inicio->nome, inicio->senha);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listarutil(Utilizadores* inicio) {
	while (inicio != NULL) {
		printf("Nome: %s | Morada: %s | NIF: %d | Saldo: %.2f| geocodigo: %s\n", inicio->nome, inicio->morada, inicio->NIF, inicio->saldo, inicio->geocodigo);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listargrafo(Grafo* inicio) {
	Meio* auxmeio;
	Adjacentes* auxadj;
	printf("Os dados do grafo:\n\n");

	while (inicio != NULL) {
		printf("\n~~~~~~~~~~~~Vertice: %s~~~~~~~~~~~~\n", inicio->geocodigo);

		if (inicio->adjacente == NULL) {
			printf("Este vertice nao tem adjacentes.\n");
		}

		else{
			auxadj = inicio->adjacente;
			while (inicio->adjacente != NULL) {
				printf("\nadjacente: %s peso: %.2f", inicio->adjacente->geocodigo, inicio->adjacente->peso);
				inicio->adjacente = inicio->adjacente->seguinte;
			}
			inicio->adjacente = auxadj;

		}

		if (inicio->meios == NULL) {

		}
		else {
			auxmeio = inicio->meios;
			while(inicio->meios != NULL){
				printf("\nCodigo meio no vertice: %d", inicio->meios->codigo);
				inicio->meios = inicio->meios->seguinte;
			}
			inicio->meios = auxmeio;
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		inicio = inicio->seguinte;
	}
}