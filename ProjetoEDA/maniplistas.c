#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "ficheiroslistas.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Parte de adi��o, remo��o e altera��o de meios
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
		Meio* novo = malloc(sizeof(struct registomeio));//aloca��o de memoria para um novo meio
		if (novo != NULL)
		{
			novo->codigo = cod;
			strcpy(novo->tipo, tipo);
			novo->bateria = bat;
			novo->autonomia = aut;
			novo->custo = cust;
			strcpy(novo->geocodigo,geocod);
			novo->seguinte = inicio;
			novo->alugado = 0;
			return(novo);
		}
	}
	else return(inicio);
}

Meio* removerMeio(Meio* inicio, int cod){
	Meio* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia

	else if (atual->codigo == cod) // remo��o do 1� registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		
		while ((atual != NULL) && (atual->codigo != cod))//ir avan�ando na lista, at� ser igual.
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

void mudarMeios(Meio* meio, int cod, Grafo* grafo) {
	int i = 0, bool;
	float bat, aut, cust;
	char tipo[20], geocod[100];
	int escolha = 1, choice;
	Meio* inicio;
	inicio = meio;
	for (; (i == 1 || i == 2) != 1;) {//loop for para chegar ao meio que queremos, para quando i for 1 ou 2
		if (meio == NULL)//se chegou ao fim da lista, i � 2, mostra uma mensagem de erro e acaba a fun��o
			i = 2;
		else {
			if (meio->codigo == cod)//se encontrar i � 1, realizando as altera��es
				i = 1;
			else
				meio = meio->seguinte;
		}
	}
	if (i == 2) {
		printf("\nNao foi possivel encontrar correspondencia a esse codigo.\n");
		return;
	}
	else {
		while (escolha) {
			printf("O que deseja mudar?\n1- Codigo\n2- Tipo\n3- Bateria\n4- Autonomia\n5- Custo\n6- Geocodigo\n0- Nada\n");
			scanf("%d", &choice);//pergunta o que o utilizador quer fazaer
			if (choice >= 0 && choice < 7) {
				
				if(choice == 1){//para mudar o codigo, mas primeiramente verifica se j� existe esse codigo, sen�o, n�o altera
					printf("Codigo\n");
					scanf("%d", &cod);
					if (!(existeMeio(inicio, cod))) {
						mudarcodmeiovertice(grafo,meio,cod);
						meio->codigo = cod;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Existe um meio com esse codigo!");

				}

				else if(choice == 2){
					printf("\nTipo: (trotinete/bicicleta)\n");//pede o tipo, sendo que s� pode escrever trotinete ou bicicleta
					bool = 1;
					while (bool) {
						scanf("%s", tipo);
						if ( (!(strcmp(tipo, "trotinete")) || (!(strcmp(tipo, "bicicleta")))))
							bool = 0;//se escrever certo sai do loop
						else
							printf("Digitou errado, escreva de novo:\n");
					}
					mudartipomeiovertice(grafo,meio,tipo);
					strcpy(meio->tipo, tipo);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}
				
				else if (choice == 3) {//muda a bateria se for maior que 0
					printf("\nBateria\n");
					scanf("%f", &bat);
					if (bat >= 0) {
						mudarbatvertice(grafo, meio, bat);
						meio->bateria = bat;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Valor digitado errado!");
				}
			
				else if(choice == 4){//muda a autonimia se for maior que 0
					printf("\nAutonomia\n");
					scanf("%f", &aut);
					if (aut >= 0) {
						mudarautvertice(grafo, meio, aut);
						meio->autonomia = aut;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Valor digitado errado!");
				}
				
				else if(choice == 5){//muda o custo se for maior que 0
					printf("\nCusto\n");
					scanf("%f", &cust);
					if (cust > 0) {
						mudarcustvertice(grafo, meio, cust);
						meio->custo = cust;
						system("cls");
						printf("Mudanca bem sucedida!\n");
					}
					else
						printf("Valor digitado errado!");
				}

				else if (choice == 6){//muda o geocodigo
					printf("\nGeocodigo\n");
					scanf("%s", geocod);
					system("cls");
					strcpy(meio->geocodigo, geocod);
					fixarmeiosvertices(inicio, grafo);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}
				else if (choice == 0) {//se escolher 0, acaba a execu��o da fun��o
					BubbleSortMeios(inicio);
					return;
				}
				printf("Deseja mudar mais alguma coisa? (1/0)\n");
				scanf("%d", &escolha);
				system("cls");//pergunta se quer continuar se 0 acaba, se 1 pergunta de novo o que quer mudar
			}
		}
	}
	BubbleSortMeios(inicio);
}

void BubbleSortMeios(Meio* inicio) {
	int b = 1;
	Meio* atual, * seguinte;

	while (b) {
		b = 0;
		atual = inicio;
		while (atual->seguinte != NULL) {
			seguinte = atual->seguinte;

			if (atual->autonomia < seguinte->autonomia) { // compara a autonomia do atual da lista e o seguinte, se for maior, muda todos os parametros de um com o outro
				int auxcodigo = atual->codigo;
				float auxbateria = atual->bateria;
				float auxautonomia = atual->autonomia;
				float auxcusto = atual->custo;
				int auxalugado = atual->alugado;
				char auxtipo[50],auxgeocod[50];
				strcpy(auxtipo, atual->tipo);
				strcpy(auxgeocod, atual->geocodigo);

				atual->custo = seguinte->custo;
				atual->codigo = seguinte->codigo;
				atual->bateria = seguinte->bateria;
				atual->autonomia = seguinte->autonomia;
				atual->alugado = seguinte->alugado;
				strcpy(atual->tipo, seguinte->tipo);
				strcpy(atual->geocodigo, seguinte->geocodigo);

				seguinte->custo = auxcusto;
				seguinte->codigo = auxcodigo;
				seguinte->bateria = auxbateria;
				seguinte->autonomia = auxautonomia;
				seguinte->alugado = auxalugado;
				strcpy(seguinte->tipo, auxtipo);
				strcpy(seguinte->geocodigo, auxgeocod);

				b = 1;
			}
			atual = seguinte;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Parte de adi��o, remo��o e altera��o de utilizadores
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int existeUtil(Utilizadores* inicio, int NIF) {//verifica o NIF para ver se j� existe
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
	else if (atual->NIF == NIF) // remo��o do 1� registo
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

void mudarUtils(Utilizadores* util, int NIF, Grafo* grafo) {//mesmo pensamento da fun�o mudarMeios
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
					mudarnomeutilvertice( grafo, util, nome);
					system("cls");
					printf("Mudanca bem sucedida!\n");
				}

				else if (choice == 2) {//NIF
					printf("\nNIF:\n");
					scanf("%d", &NIF);
					system("cls");
					if (!(existeUtil(inicio, NIF))){//verifica se o NIF j� existe
						mudarNIFvertice(grafo,util,NIF);
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
					mudarmoradavertice(grafo,util,morada);
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
//Parte de adi��o, remo��o e altera��o de administradores
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
	else if (atual->codigo == cod) // remo��o do 1� registo
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

void mudarAdmins(Administradores* admin, int cod) {//mesmo pensamento da fun��o mudarMeios
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
					if (!(existeAdmin(inicio, cod))) {//verifica se j� existe esse codigo
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
//Manipula��o de saldo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void mostrarsaldo(Utilizadores* util, int utilNIF) {
	while (util != NULL) {
		if (util->NIF == utilNIF) {
			printf("Seu saldo: %.2f$\n", util->saldo);
			return;
		}
		util = util->seguinte;
	}
}

void adicionarsaldo(Utilizadores* util, int utilNIF, float valorcarregado) {
	while (util != NULL) {

		if (util->NIF == utilNIF) {
			util->saldo += valorcarregado;
			printf("\nSeu novo saldo e %.2f$\n", util->saldo);
		}
		util = util->seguinte;

	}
}

void aluguelmeio(Utilizadores* inicioutil, int utilNIF, Meio* iniciomeio, int cod) {

	while (inicioutil != NULL) {
		if (inicioutil->NIF == utilNIF) {//na lista vai at� o utilizador certo
			while (iniciomeio != NULL) {
				if (iniciomeio->codigo == cod)//na lista vai at� o meio com o mesmo codigo
					if (inicioutil->saldo > iniciomeio->custo) {// verifica se tem saldo para pagar
						if (iniciomeio->alugado == 0) {//verifica se j� est� alugado, se nao, pode alugar
							inicioutil->saldo -= iniciomeio->custo;
							iniciomeio->alugado = 1;//marca o meio como alugado
							guardarhistorico(inicioutil, iniciomeio);//guarda o alugamento num ficheiro bin
							printf("Compra bem sucedida!\n");
							return;
						}
						else {
							printf("O meio ja esta alugado!\n");
							return;
						}
					}
					else {
						printf("Seu saldo � menor que o custo do meio\n");
						return;
					}
				iniciomeio = iniciomeio->seguinte;
			}
			printf("Nao foi achado um meio com esse codigo.\n");//ao percorrer o while, se n�o encontrar o meio retorna isto
			return;
		}
		inicioutil = inicioutil->seguinte;
	}
}
