#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "ficheiroslistas.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Parte de adição, remoção e alteração de meios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int existeMeio(Meio* inicio, int cod){//verifica se existe um meio com o codigo digitado
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

void mudarMeios(Meio* meio, int cod) {
	int i = 0, bool;
	float bat, aut, cust;
	char tipo[20], geocod[100];
	int escolha = 1, choice;
	Utilizadores* inicio;
	inicio = meio;
	for (; (i == 1 || i == 2) != 1;) {
		if (meio == NULL)
			i = 2;
		else {
			if (meio->codigo == cod)
				i = 1;
			else
				meio = meio->seguinte;
		}
	}
	if (i == 2) {
		printf("\nNao foi possivel encontrar correspondencia a esse NIF.\n");
		return;
	}
	else {
		while (escolha) {
			printf("O que deseja mudar?\n1- Codigo\n2- Tipo\n3- Bateria\n4- Autonomia\n5- Custo\n6- Geocodigo\n0- Nada\n");
			scanf("%d", &choice);
			if (choice >= 0 && choice < 7) {
				
				if(choice == 1){
					printf("Codigo\n");
					scanf("%d", &cod);
					if (!(existeMeio(inicio, cod))) {
						meio->codigo = cod;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Existe um meio com esse codigo!");

				}

				else if(choice == 2){
					printf("\nTipo: (trotinete/bicicleta)\n");
					bool = 1;
					while (bool) {
						scanf("%s", tipo);
						if ( (!(strcmp(tipo, "trotinete")) || (!(strcmp(tipo, "bicicleta")))))
							bool = 0;
						else
							printf("Digitou errado, escreva de novo:\n");
					}
					strcpy(meio->tipo, tipo);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}
				
				else if (choice == 3) {
					printf("\nBateria\n");
					scanf("%f", &bat);
					if (bat >= 0) {
						meio->bateria = bat;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Valor digitado errado!");
				}
			
				else if(choice == 4){
					printf("\nAutonomia\n");
					scanf("%f", &aut);
					if (aut >= 0) {
						meio->autonomia = aut;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Valor digitado errado!");
				}
				
				else if(choice == 5){
					printf("\nCusto\n");
					scanf("%f", &cust);
					if (cust > 0) {
						meio->custo = cust;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Valor digitado errado!");
				}

				else if (choice == 6){
					printf("\nGeocodigo\n");
					scanf("%s", geocod);
					system("cls");
					strcpy(meio->geocodigo, geocod);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}
				else if (choice == 0)
					return;
				printf("Deseja mudar mais alguma coisa? (1/0)\n");
				scanf("%d", &escolha);
				system("cls");
			}
		}
	}
}

void BubbleSortMeios(Meio* inicio) {
	int b = 1;
	Meio* atual, * seguinte;

	while (b) {
		b = 0;
		atual = inicio;
		while (atual->seguinte != NULL) {
			seguinte = atual->seguinte;

			if (atual->autonomia < seguinte->autonomia) { // <-- Comparação modificada
				int auxcodigo = atual->codigo;
				float auxbateria = atual->bateria;
				float auxautonomia = atual->autonomia;
				float auxcusto = atual->custo;
				char auxtipo[50],auxgeocod[50];
				strcpy(auxtipo, atual->tipo);
				strcpy(auxgeocod, atual->geocodigo);

				atual->custo = seguinte->custo;
				atual->codigo = seguinte->codigo;
				atual->bateria = seguinte->bateria;
				atual->autonomia = seguinte->autonomia;
				strcpy(atual->tipo, seguinte->tipo);
				strcpy(atual->geocodigo, seguinte->geocodigo);

				seguinte->custo = auxcusto;
				seguinte->codigo = auxcodigo;
				seguinte->bateria = auxbateria;
				seguinte->autonomia = auxautonomia;
				strcpy(seguinte->tipo, auxtipo);
				strcpy(seguinte->geocodigo, auxgeocod);

				b = 1;
			}
			atual = seguinte;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Parte de adição, remoção e alteração de utilizadores
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int existeUtil(Utilizadores* inicio, int NIF) {
	while (inicio != NULL)
	{
		if (inicio->NIF == NIF) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}


Utilizadores* inserirUtils(Utilizadores* inicio, char nome[], int NIF, char morada[], float saldo) {
	if (!existeUtil(inicio, NIF))
	{
		Utilizadores* novo = malloc(sizeof(struct registoutil));
		if (novo != NULL)
		{
			novo->NIF = NIF;
			novo->saldo = saldo;
			strcpy(novo->nome, nome);
			strcpy(novo->morada, morada);
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}


Utilizadores* removerUtil(Utilizadores* inicio, int NIF) {
	Utilizadores* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia
	else if (atual->NIF == NIF) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (atual->NIF != NIF))
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

void mudarUtils(Utilizadores* util, int NIF) {
	int i = 0;
	char nome[100], morada[150];
	int escolha = 1,choice;
	Utilizadores* inicio;
	inicio = util;
	for (; (i == 1 || i == 2) != 1;) {
		if (util == NULL)
			i = 2;
		else{
			if (util->NIF == NIF)
				i = 1;
			else
				util = util->seguinte;
		}	
	}
	if (i == 2) {
		printf("\nNao foi possivel encontrar correspondencia a esse NIF.\n");
		return;
	}
	else {
		while (escolha) {
			printf("O que deseja mudar?\n1- Nome\n2- NIF\n3- Morada\n0- Nada\n");
			scanf("%d", &choice);
			if (choice >= 0 && choice < 4) {
				if (choice == 1) {//Nome
					printf("Nome\n");
					getchar();
					gets(nome);
					strcpy(util->nome, nome);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}

				else if (choice == 2) {//NIF
					printf("\nNIF:\n");
					scanf("%d", &NIF);
					system("cls");
					if (!(existeUtil(inicio, NIF))){
						util->NIF = NIF;
					printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Ja existe um utilizador com esse NIF!\n");
				}
				else if (choice == 3) {//Morada
					printf("\nMorada:\n");
					getchar();
					gets(morada);
					strcpy(util->morada, morada);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}
				else if (choice == 0)
					return;
				printf("Deseja mudar mais alguma coisa? (1/0)\n");
				scanf("%d", &escolha);
				system("cls");
			}
		}	
	}	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Parte de adição, remoção e alteração de administradores
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int existeAdmin(Administradores* inicio,int cod){
	while (inicio != NULL)
	{
		if (inicio->codigo == cod) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Administradores* inserirAdmins(Administradores* inicio, int cod, char nome[], char senha[]) {
	if (!existeAdmin(inicio, cod))
	{
		Administradores* novo = malloc(sizeof(struct registoadmin));
		if (novo != NULL)
		{
			novo->codigo = cod;
			strcpy(novo->nome, nome);
			strcpy(novo->senha, senha);
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}


Administradores* removerAdmins(Administradores* inicio, int cod){
	Administradores* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia
	else if (atual->codigo == cod) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && atual->codigo != cod)
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

void mudarAdmins(Administradores* admin, int cod) {
	int i = 0, escolha = 1, choice;
	char senha[20], nome[100];
	Administradores* inicio;
	inicio = admin;
	for (; (i == 1 || i == 2) != 1;) {
		if (admin == NULL)
			i = 2;
		else {
			if (admin->codigo == cod)
				i = 1;
			else
				admin = admin->seguinte;
		}
	}

	if (i == 2) {
		printf("\nNao foi possivel encontrar correspondencia a esse nome.\n");
		return;
	}
	else {
		while (escolha) {
			printf("O que deseja mudar?\n1- Codigo\n2- Nome\n3- Senha\n0- Nada\n");
			scanf("%d", &choice);
			if (choice >= 0 && choice < 4) {
				if (choice == 1) {
					printf("Digite o codigo: \n");
					scanf("%d", &cod);
					if (!(existeAdmin(inicio, cod))) {
						admin->codigo = cod;
						system("cls");
						printf("Mudanca bem sucedida\n");
					}
					else {
						printf("Ja existe alguem com esse codigo!");
					}
				}
				else if (choice == 2) {//Nome
					printf("Digite o nome de usuario: \n");
					getchar();
					gets(nome);
					system("cls");
					strcpy(admin->nome, nome);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}

				else if (choice == 3) {//Senha
					printf("\nDigite a senha: ");
					scanf("%s", senha);
					strcpy(admin->senha, senha);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}

				else if (choice == 0) return;

				printf("Deseja mudar mais alguma coisa? (1/0)\n");
				scanf("%d", &escolha);
				system("cls");
			}
		}
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Manipulação de saldo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void verificarsaldo(Utilizadores* inicioutil, int utilNIF, Meio* iniciomeio, int cod, int valoradd, float carregarvalor, int verificarsemaior) {
	if (verificarsemaior == 0) {//Parte na qual o utilizador vê seu saldo e decide se quer adicionar dinheiro
		while (inicioutil != NULL) {
			if (valoradd == 0) {//Só ver o saldo
				if (inicioutil->NIF == utilNIF) {
					printf("Seu saldo: %.2f$\n", inicioutil->saldo);
					return;
				}
				inicioutil = inicioutil->seguinte;
			}
			else {
				if (inicioutil->NIF == utilNIF) { // adicionar saldo
					mexersaldo(inicioutil, NULL, valoradd, carregarvalor);
					return;
				}
				inicioutil = inicioutil->seguinte;
			}
		}
	}

	else {//Parte do aluguel do meio
		while (inicioutil != NULL) {
			if (inicioutil->NIF == utilNIF) {
				while (iniciomeio != NULL) {
					if (iniciomeio->codigo == cod)
						if (inicioutil->saldo > iniciomeio->custo) {// verifica se tem saldo para pagar
							mexersaldo(inicioutil, iniciomeio, 0, 0);
							guardarhistorico(inicioutil, iniciomeio);
							printf("Compra bem sucedida!\n");
							return;
						}
						else {
							printf("Seu saldo é menor que o custo do meio\n");
							return;
						}
					iniciomeio = iniciomeio->seguinte;
				}
				printf("Nao foi achado um meio com esse codigo.\n");//ao percorrer o while, se não encontrar o meio retorna isto
				return;
			}
			inicioutil = inicioutil->seguinte;
		}
	}
}


void mexersaldo(Utilizadores* util, Meio* meio, int sinal, float valorcarregado) {
	if (sinal) {//adicionar o que o utilizador carregou de saldo
		util->saldo += valorcarregado;
		printf("\nSeu novo saldo é %.2f$\n", util->saldo);
	}
	else {//tirar o custo do meio do saldo
		util->saldo -= meio->custo;
	}
}
